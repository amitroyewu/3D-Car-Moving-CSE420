/***************

Jannatun Naym             2016-1-60-119         Section: 01
Nishat Tasnim Mim         2016-2-60-081         Section: 02
Sirajum Maria Muna        2017-3-60-020         Section: 02
Amit Roy                  2017-3-60-021         Section: 02
Fahmida Khalid            2017-1-60-050         Section: 02


****************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include<glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
    double x,y,z;
} Point;
int gridcount = 1, lightraycount = 1, roadcount = 0, mousecounter = 2, transitioncount = 0;
bool drawAxes = true;
bool drawgrid = true;
bool road = true;
bool transition = true;
bool flag;
bool ray = true;
float tyreAngle = 0;

float quadAngle = 0;
float quadAngle1 = 0;
float boxAngle = 0;
float boxScaleFactorX = 1;
float boxScaleFactorY = 1;
float boxScaleFactorZ = 1;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;
float movecar = 0;
float i=0.00012;


Point pos, u, r, l;

void gridX()
{
    if(drawgrid)
    {
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0, 0);

            glVertex3f( 500,0,0);
            glVertex3f(-500,0,0);

        }
        glEnd();
    }
}
void gridY()
{
    if(drawgrid)
    {
        glBegin(GL_LINES);
        {

            glColor3f(0, 1.0, 0);

            glVertex3f(0,-500,0);
            glVertex3f(0, 500,0);

        }
        glEnd();
    }
}
void displayAxes()
{
    if(drawAxes)
    {
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0, 0);

            glVertex3f( 500,0,0); // a point on pos x axis
            glVertex3f(-500,0,0); // a point on neg x axis

            glColor3f(0, 1.0, 0);

            glVertex3f(0,-500,0); // a point on pos y axis
            glVertex3f(0, 500,0); // a point on neg y axis

            glColor3f(0, 0, 1.0);

            glVertex3f(0,0, 500);  // a point on pos z axis
            glVertex3f(0,0,-500);   // a point on neg z axis
        }
        glEnd();
    }
}

void displaygrid()
{
    if(drawgrid)
    {

        glPushMatrix();
        for(int i=0; i<=50; i++)
        {
            gridX();
            glTranslatef(0, (i+20), 0);

        }
        glPopMatrix();

        glPushMatrix();
        for(int i=0; i<=50; i++)
        {
            gridX();
            glTranslatef(0, -(i+20), 0);

        }
        glPopMatrix();


        glPushMatrix();
        for(int i=0; i<=50; i++)
        {
            gridY();
            glTranslatef(i+20, 0, 0);
        }
        glPopMatrix();

        glPushMatrix();
        for(int i=0; i<=50; i++)
        {
            gridY();
            glTranslatef(-(i+20), 0, 0);
        }
        glPopMatrix();

    }

}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

Point Cameraposition(Point vect, Point perp, int dir)
{
    double s = dir * 3.0;

    Point point;
    point.x =  vect.x + s * perp.x;
    point.y =  vect.y + s * perp.y;
    point.z =  vect.z + s * perp.z;
    return point;
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
    {
        Point l1 = func(l, r, -1);
        r = func(r, l, 1);
        l = l1;
        break;
    }
    case '2':
    {
        Point l1 = func(l, r, 1);
        r = func(r, l, -1);
        l = l1;
        break;
    }

    case '3':
    {
        Point u1 = func(u, l, -1);
        l = func(l, u, 1);
        u = u1;
        break;
    }
    case '4':
    {
        Point u1 = func(u, l, 1);
        l = func(l, u, -1);
        u = u1;
        break;
    }
    case '5':
    {
        Point r1 = func(r, u, -1);
        u = func(u, r, 1);
        r = r1;
        break;
    }
    case '6':
    {
        Point r1 = func(r, u, 1);
        u = func(u, r, -1);
        r = r1;
        break;
    }
    case '7':
    {
        if(movecar == 250)
        {
            break;
        }
        else
        {
            tyreAngle -= 5;
            movecar += 5;
        }
        break;
    }
    case '8':
    {
        if(movecar == -250)
        {
            break;
        }
        else
        {
            tyreAngle += 5;
            movecar -= 5;
        }
        break;
    }
    case '9':
    {
        quadAngle += 5;
        printf("Quad Angle %f\n", quadAngle);
        break;
    }
    case '0':
    {
        quadAngle -= 5;
        printf("Quad Angle %f\n", quadAngle);
        break;
    }
    case 'a':
    {
        if(boxScaleFactorX<= 1.120000)
        {
            boxScaleFactorX +=0.015;
        }
        break;
    }
    case 'A':
    {
        if(boxScaleFactorX<= 1.120000)
        {
            boxScaleFactorX +=0.015;
        }
        break;

    }
    case 'b':
    {
        if(boxScaleFactorX>= 0.010001)
        {
            boxScaleFactorX -=0.015;
        }
        break;
    }
    case 'B':
    {
        if(boxScaleFactorX>= 0.010001)
        {
            boxScaleFactorX -=0.015;
        }
        break;
    }
    case 'c':
    {
        if(boxScaleFactorY<= 1.120000)
        {
            boxScaleFactorY +=0.015;
        }
        break;
    }
    case 'C':
    {
        if(boxScaleFactorY<= 1.120000)
        {
            boxScaleFactorY +=0.015;
        }
        break;
    }
    case 'd':
    {
        if(boxScaleFactorY>= 0.010001)
        {
            boxScaleFactorY -=0.015;
        }
        break;
    }
    case 'D':
    {
        if(boxScaleFactorY>= 0.010001)
        {
            boxScaleFactorY -=0.015;
        }
        break;
    }
    case 'e':
    {
        if(boxScaleFactorZ<= 1.120000)
        {
            boxScaleFactorZ +=0.015;
        }
        break;
    }
    case 'E':
    {
        if(boxScaleFactorZ<= 1.120000)
        {
            boxScaleFactorZ +=0.015;
        }
        break;
    }
    case 'f':
    {
        if(boxScaleFactorZ>= 0.010001)
        {
            boxScaleFactorZ -=0.015;
        }

        break;
    }
    case 'F':
    {
        if(boxScaleFactorZ>= 0.010001)
        {
            boxScaleFactorZ -=0.015;
        }
        break;
    }
    case 'Q':
    {
        quadAngle1 += 5;
        printf("Quad Angle %f\n", quadAngle1);
        break;
    }
    case 'q':
    {
        quadAngle1 -= 5;
        printf("Quad Angle %f\n", quadAngle1);
        break;
    }

    default:
        break;
    }
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
    {
        point pos1 = Cameraposition(pos, l, -1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_UP:
    {
        point pos1 = Cameraposition(pos, l, 1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_RIGHT:
    {
        point pos1 = Cameraposition(pos, r, 1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_LEFT:
    {
        point pos1 = Cameraposition(pos, r, -1);
        pos = pos1;
        break;
    }

    case GLUT_KEY_PAGE_UP:
    {
        point pos1 = Cameraposition(pos, u, 1);
        pos = pos1;
        break;
        break;
    }

    case GLUT_KEY_PAGE_DOWN:
    {
        point pos1 = Cameraposition(pos, u, -1);
        pos = pos1;
        break;
        break;
    }

    case GLUT_KEY_HOME:
    {
        if(boxScaleFactorX<= 1.120000 && boxScaleFactorY<= 1.120000 && boxScaleFactorZ<= 1.120000)
        {
            boxScaleFactorX +=0.015;
            boxScaleFactorY +=0.015;
            boxScaleFactorZ +=0.015;
        }
        break;

    }

    case GLUT_KEY_END:
    {
        if(boxScaleFactorX>= 0.010001 && boxScaleFactorY>= 0.010001 && boxScaleFactorZ>= 0.010001)
        {
            boxScaleFactorX -=0.015;
            boxScaleFactorY -=0.015;
            boxScaleFactorZ -=0.015;
        }

        break;
    }

    default:
        break;
    }
}


void mouseListener(int button, int state, int x, int y)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
        {
            if(mousecounter%2 == 0)
            {
                drawAxes = false;
            }
            else
            {
                drawAxes = true;
            }
            mousecounter++;
        }
        else if(state == GLUT_UP)
        {
            printf("Mouse Left Button Released\n");
        }
        break;
    default:
        break;
    }
}

void displayTyre(float tyreRadius, float tyreWidth, float tyrehalfWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2, halfsquareWidth = tyrehalfWidth/2;


    /*** Horizontal ***/
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(5, 0, 0);

    glBegin(GL_QUADS);
    {
        glVertex3f(halfsquareWidth, tyreRadius, 0);
        glVertex3f(-halfsquareWidth, tyreRadius, 0);
        glVertex3f(-halfsquareWidth, -tyreRadius, 0);
        glVertex3f(halfsquareWidth, -tyreRadius, 0);


    }
    glEnd();
    glPopMatrix();

    /*** Horizontal ***/
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(-5, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfsquareWidth, tyreRadius, 0);
        glVertex3f(-halfsquareWidth, tyreRadius, 0);
        glVertex3f(-halfsquareWidth, -tyreRadius, 0);
        glVertex3f(halfsquareWidth, -tyreRadius, 0);


    }
    glEnd();
    glPopMatrix();

    /**** Vertical ****/
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(5, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfsquareWidth, 0, tyreRadius);
        glVertex3f(halfsquareWidth, 0, -tyreRadius);
        glVertex3f(-halfsquareWidth, 0, -tyreRadius);
        glVertex3f(-halfsquareWidth, 0, tyreRadius);
    }
    glEnd();
    glPopMatrix();

    /*** Vertical ***/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-5, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfsquareWidth, 0, tyreRadius);
        glVertex3f(halfsquareWidth, 0, -tyreRadius);
        glVertex3f(-halfsquareWidth, 0, -tyreRadius);
        glVertex3f(-halfsquareWidth, 0, tyreRadius);
    }
    glEnd();
    glPopMatrix();


    for(int i=0; i<tyreSlices; i++)
    {
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);

        glBegin(GL_QUADS);
        {
            if(i%2==0)
            {
                glColor3f(0, 0, 0);
                glVertex3f(halfTyreWidth, 0, halfSliceWidth);
                glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }
            else
            {
                glColor3f(1, 1, 1);
                glVertex3f(halfTyreWidth, 0, halfSliceWidth);
                glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
                glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

        }
        glEnd();
        glPopMatrix();
    }
}

void displayHEADLIGHT(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 0);

        glVertex3f(halfBoxLength/7, halfBoxWidth*5, halfBoxHeight/2);
        glVertex3f(-halfBoxLength/7, halfBoxWidth*5, halfBoxHeight/2);
        glColor3f(0, 1, 0);
        glVertex3f(-halfBoxLength/7, halfBoxWidth*5, -halfBoxHeight/2);
        glVertex3f(halfBoxLength/7, halfBoxWidth*5, -halfBoxHeight/2);


        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength/7, halfBoxWidth*5, halfBoxHeight/2);
        glVertex3f(-halfBoxLength/7, halfBoxWidth*5, halfBoxHeight/2);
        glColor3f(0, 1, 1);
        glVertex3f(-halfBoxLength/7, halfBoxWidth*5, -halfBoxHeight/2);
        glVertex3f(halfBoxLength/7, halfBoxWidth*5, -halfBoxHeight/2);

    }
    glEnd();
}


void displayBIGBox(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glColor3f(0, 1, 0);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.46, 0.96, 0.26);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0.45, 0.26);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);

        glColor3f(1, 1, 0);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displaySMALLBox(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength /2, halfBoxWidth = boxWidth /2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);
        glVertex3f(halfBoxLength, halfBoxWidth*3, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth*3, halfBoxHeight);
        glColor3f(1, 1, 1);
        glVertex3f(-halfBoxLength, halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth*5, -halfBoxHeight); //Front Glass

        glColor3f(1, 0, 0);
        glVertex3f(halfBoxLength, -halfBoxWidth*3, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth*3, halfBoxHeight);
        glColor3f(1, 1, 1);
        glVertex3f(-halfBoxLength, -halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth*5, -halfBoxHeight); //Back Glass


        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth*3, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth*3, halfBoxHeight); //Small Box Left Body


        glColor3f(1, 1, 0);
        glVertex3f(-halfBoxLength, halfBoxWidth*3, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth*3, halfBoxHeight);  //Small Box Right Body

        glColor3f(1, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth*3, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth*3, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth*3, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth*3, halfBoxHeight);


        glVertex3f(halfBoxLength, halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth*5, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth*5, -halfBoxHeight);
    }
    glEnd();
}

void displayLIGHTBOX(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight); //Light Box Lower

        glColor3f(0, 0, 1);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight); //Light Box Back


        glColor3f(0,1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);//Light Box Right


        glColor3f(0,0.1, 0);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);//Light Box Left

        glColor3f(1, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayLIGHTSTAND(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 1.0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);


        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1.0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

    }
    glEnd();
}

void displayRAYPLANE(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

    }
    glEnd();
}
void displayLIGHTRAYHORIZONTAL(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 15;
    glBegin(GL_QUADS);
    {

        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength*5, halfBoxWidth*20, halfBoxHeight);
        glVertex3f(halfBoxLength*5, halfBoxWidth*20, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength*5, halfBoxWidth*20, halfBoxHeight);
        glVertex3f(-halfBoxLength*5, halfBoxWidth*20, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
    }
    glEnd();
}

void displayLIGHTRAYVERTICAL(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 10, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth*20, halfBoxHeight*5);
        glVertex3f(-halfBoxLength, halfBoxWidth*20, halfBoxHeight*5);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth*20, -halfBoxHeight*5);
        glVertex3f(-halfBoxLength, halfBoxWidth*20, -halfBoxHeight*5);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayROAD(float boxLength, float boxWidth, float boxHeight)
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight;

    glBegin(GL_QUADS);
    {
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

    }
    glEnd();
}

void displayScene()
{

    float quadLength = 100, quadWidth = 60;
    float largeBoxLength = 200, largeBoxWidth = 500, largeBoxHeight = 30;
    float smallBoxLength = 200, smallBoxWidth = 70, smallBoxHeight = 50;
    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float tyreRadius = 25, tyreWidth = 20, tyrehalfWidth = 10;
    float lightstandLength = 20, lightstandWidth = 20, lightstandHeight = 70;
    float lightboxLength = 40, lightboxWidth = 40, lightboxHeight = 40;
    float lightRAYLength = 40, lightRAYWidth = 40, lightRAYHeight = 40;
    float RoadUNLength = 350, RoadWidth = 1000, RoadHeight = 0.1;
    float RoadUPLength = 300, RoadUPHeight = 0;
    float headlightWidth = 100.1;

    /**** Principal Axes ****/
    displayAxes();

    /*** SHOW ROAD ***/
    if(roadcount >= 1)
    {
        glPushMatrix();
        glColor3f(0.65, 0.65, 0.65);
        displayROAD(RoadUPLength, RoadWidth, RoadUPHeight);
        glPopMatrix();
        glPushMatrix();
        glColor3f(1, 1, 1);
        displayROAD(RoadUNLength, RoadWidth, RoadHeight);
        glPopMatrix();
    }

    /*** SHOW GRID ***/
    if(gridcount >= 2)
    {
        displaygrid();
    }

    /*** Scaling CAR WITH LIGHT BOX***/
    glScalef(boxScaleFactorX,1.0, 1.0);
    glScalef(1.0, boxScaleFactorY, 1.0);
    glScalef(1.0, 1.0, boxScaleFactorZ);
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

    glTranslatef(0, 0, 25);

    glPushMatrix();
    glTranslatef(0, movecar, 0);


    glPushMatrix(); //rotate car
    glRotatef(quadAngle1, 0, 0, 1);


    /**** CAR TYRE ****/
    glPushMatrix();
    glTranslatef(90, 170, 0);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth, tyrehalfWidth);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(90, -170, 0);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth, tyrehalfWidth);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-90, 170, 0);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth, tyrehalfWidth);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-90, -170, 0);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth, tyrehalfWidth);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, (tyreRadius/1.2)+(largeBoxHeight));


    /**** HEAD LIGHT ****/
    glPushMatrix();
    glTranslatef(70, 0, 0);
    displayHEADLIGHT(largeBoxLength, headlightWidth, largeBoxHeight);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70, 0, 0);
    displayHEADLIGHT(largeBoxLength, headlightWidth, largeBoxHeight);
    glPopMatrix();


    /**** CAR BODY ****/
    displayBIGBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displaySMALLBox(smallBoxLength, smallBoxWidth, smallBoxHeight);
    glPopMatrix();


    /**** LIGHT BOX ****/
    glRotatef(quadAngle, 0, 0, 1);
    glPushMatrix();
    glTranslatef(0, 0, ((lightboxHeight/2) + (lightstandHeight/2) + (smallBoxHeight/2) + (largeBoxHeight/2)));
    displayLIGHTSTAND(lightstandLength, lightstandWidth, lightstandHeight);
    glPopMatrix();

    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glPushMatrix();
    glTranslatef(0, 0, (lightboxHeight/2) + (lightstandHeight/2) + (lightboxHeight/2) + (lightstandHeight/2) + (smallBoxHeight/2) + (largeBoxHeight/2));
    displayLIGHTBOX(lightboxLength, lightboxWidth, lightboxHeight);
    glPopMatrix();

    /*** TURN ON & TURN OFF LIGHT ***/
    if(lightraycount >= 1)
    {
        /*** LIGHT RAY PLATE ***/
        glPushMatrix();
        glTranslatef(0, 0.1, 0); //color of light plate
        glTranslatef(0, 0, (lightboxHeight/2) + (lightstandHeight/2) + (lightboxHeight/2) + (lightstandHeight/2) + (smallBoxHeight/2) + (largeBoxHeight/2));
        displayRAYPLANE(lightboxLength, lightboxWidth, lightboxHeight);

        /*** HORIZONTAL LIGHT RAY ***/
        glPushMatrix();
        glTranslatef(0,(lightboxWidth/2) + (lightRAYWidth/2), 0);
        glTranslatef(0,0,10);
        displayLIGHTRAYHORIZONTAL(lightRAYLength, lightRAYWidth, lightRAYHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,(lightboxWidth/2) + (lightRAYWidth/2), 0);
        glTranslatef(0,0,0);
        displayLIGHTRAYHORIZONTAL(lightRAYLength, lightRAYWidth, lightRAYHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,(lightboxWidth/2) + (lightRAYWidth/2), 0);
        glTranslatef(0,0,-10);
        displayLIGHTRAYHORIZONTAL(lightRAYLength, lightRAYWidth, lightRAYHeight);
        glPopMatrix();

        /*** VERTICAL LIGHT RAY ***/
        glPushMatrix();
        glTranslatef(0,(lightboxLength/2) + (lightRAYLength/2), 0);
        glTranslatef(15,0,0);
        displayLIGHTRAYVERTICAL(lightRAYLength, lightRAYWidth, lightRAYHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,(lightboxLength/2) + (lightRAYLength/2), 0);
        glTranslatef(0,0,0);
        displayLIGHTRAYVERTICAL(lightRAYLength, lightRAYWidth, lightRAYHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,(lightboxLength/2) + (lightRAYLength/2), 0);
        glTranslatef(-15,0,0);
        displayLIGHTRAYVERTICAL(lightRAYLength, lightRAYWidth, lightRAYHeight);
        glPopMatrix();
        glPopMatrix();
    }

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix(); //rotate car

    /*** Auto Transition ***/
    if(transitioncount >= 1)
    {
        if(transition)
        {
            if(background <= 0)
            {
                flag = true;
            }
            else if(background >= 1)
            {
                flag =  false;
            }
            if(flag == true)
            {
                background += i;
            }
            else if(flag == false)
            {
                background -= i;
            }
        }
    }
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background, background, background,0);	//sets background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

    glutSwapBuffers();
}

void animate()
{
    glutPostRedisplay();
}

void init()
{
    glClearColor(background, background, background,0); 	//sets background color

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

    // to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
    if(id == 3)
    {
        background = 1;
    }
    else if(id == 4)
    {
        background = 0;
    }
    else if(id == 9)
    {
        transitioncount++;
        transition = true;
    }
    else if(id == 10)
    {
        transition = false;
    }

}

void lightmenu(int id)
{
    if(id == 7)
    {
        lightraycount++;
        ray = true;
    }
    else if(id == 8)
    {
        lightraycount = 0;
        ray = false;
    }

}

void showroadmenu(int id)
{
    if(id == 11)
    {
        roadcount++;
        road = true;
    }
    else if(id == 12)
    {
        roadcount=0;
        road = false;
    }
}

void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
    else if(id == 5)
    {
        gridcount++;
        drawgrid = true;
    }
    else if(id == 6)
    {
        drawgrid = false;
    }
    else if(id == 13)
    {
        if( boxScaleFactorX >1 || boxScaleFactorX <1 || boxScaleFactorY >1 || boxScaleFactorY <1 || boxScaleFactorZ >1 || boxScaleFactorZ <1)
        {
            boxScaleFactorX = 1;
            boxScaleFactorY = 1;
            boxScaleFactorZ = 1;
        }
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    int subMenuNo = glutCreateMenu(subMenu);
    glutAddMenuEntry("White", 3);
    glutAddMenuEntry("Black", 4);
    glutAddMenuEntry("Auto Transition On", 9);
    glutAddMenuEntry("Auto Transition Off", 10);
    int lightmenuNo = glutCreateMenu(lightmenu);
    glutAddMenuEntry("Turn On", 7);
    glutAddMenuEntry("Turn Off", 8);
    int showroadmenuNo = glutCreateMenu(showroadmenu);
    glutAddMenuEntry("Show", 11);
    glutAddMenuEntry("Hide", 12);

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Axes On", 1);
    glutAddMenuEntry("Axes Off", 2);
    glutAddMenuEntry("Grid On", 5);
    glutAddMenuEntry("Grid Off", 6);
    glutAddMenuEntry("Standard Dimension", 13);
    glutAddSubMenu("Light", lightmenuNo);
    glutAddSubMenu("Road", showroadmenuNo);
    glutAddSubMenu("Background", subMenuNo);

    glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutMainLoop();		//The main loop of OpenGL, this function never returns

    return 0;
}
