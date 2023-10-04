#include "GL/glut.h"
#include <math.h>

float radiusSun = 0.1;
float centerXSun = -1.0;
float centerYSun = 0.0;

float centerXMoon = 1.0;
float centerYMoon = 0.0;

float angle = 0.0;
float radius = 1.0;
int numSegments = 100;

bool isDay = true;

void displayMe(void)
{
    if (isDay){
        glClearColor(0.69, 0.93, 0.93, 1);
    }
    else{
        glClearColor(0.0, 0.13, 0.22, 1.0); // Черный цвет фона в ночное время
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.98,0.9,0.08);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++){
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radiusSun * cosf(theta);
        float y = radiusSun * sinf(theta);
        glVertex2f(x + centerXSun, y + centerYSun);
    }
    glEnd();

    glColor3f(1.0, 1.0, 0.6);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++){
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radiusSun * cosf(theta);
        float y = radiusSun * sinf(theta);
        glVertex2f(x + centerXMoon, y + centerYMoon);
    }
    glEnd();

    glColor3f(0.5,0.8,0.2);
    glBegin(GL_POLYGON);
    float radiusField = 2.0;
    float centerXField = 0.0;
    float centerYField = -1.75;
    for (int i = 0; i < numSegments; i++){
        float alpha = i * (M_PI / (numSegments - 1));
        float x = centerXField + radiusField * cos(alpha);
        float y = centerYField + radiusField * sin(alpha);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

void update(int value)
{
    angle += 0.01;
    centerXSun = radius * cos(angle);
    centerYSun = radius * sin(angle);
    centerXMoon = radius * cos(angle + M_PI);
    centerYMoon = radius * sin(angle + M_PI);

    if (centerYSun < 0){
        isDay = false;
    }
    else if (centerYSun > 0){
        isDay = true;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab1");
    glutDisplayFunc(displayMe);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}