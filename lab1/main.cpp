#include "GL/glut.h"
#include <math.h>

float radiusSun = 0.1;
float centerXSun = -1.0;
float centerYSun = 0.0;

float centerXMoon = 1.0;
float centerYMoon = 0.0;

float angle = 0.0;
float orbitRadius = 1.0;

bool isDay = true;

void drawCircle(float radius, float centerX, float centerY){
    int numSegments = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++){
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + centerX, y + centerY);//задает координату вершины
    }
    glEnd();
}
void drawSquare(float x1, float x2,float y1,float y2){
    glBegin(GL_QUADS);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glVertex2f(x1, y1);
    glEnd();
}
void drawPig(float centerXPig, float centerYPig){
    float earRadius = 0.03;
    float eyeRadius = 0.01;
    float noseRadius = 0.02;
    float nostrilRadius = 0.005;
    glColor3f(1.0, 0.61, 0.67);
    drawCircle(radiusSun, centerXPig, centerYPig);

    glColor3f(0.87, 0.27, 0.57);
    drawCircle(earRadius, centerXPig - 0.05, centerYPig + 0.05);
    drawCircle(earRadius, centerXPig + 0.05, centerYPig + 0.05);

    glColor3f(0.5, 0.5, 0.5);
    drawSquare(centerXPig - 0.04, centerXPig - 0.02,
               centerYPig - 0.07, centerYPig - 0.12);
    drawSquare(centerXPig + 0.02, centerXPig + 0.04,
               centerYPig - 0.07, centerYPig - 0.12);

    glColor3f(0, 0, 0);
    drawCircle(eyeRadius, centerXPig-0.02, centerYPig);
    drawCircle(eyeRadius, centerXPig+0.02, centerYPig);

    glColor3f(0.87, 0.27, 0.57);
    drawCircle(noseRadius, centerXPig, centerYPig - 0.03);

    glColor3f(0, 0, 0);
    drawCircle(nostrilRadius, centerXPig + 0.007, centerYPig - 0.03);
    drawCircle(nostrilRadius, centerXPig - 0.007, centerYPig - 0.03);
}

void displayMe(void)
{
    if (isDay){
        glClearColor(0.69, 0.93, 0.93, 1);//уст цвет, которым будет очищен экран
    }
    else{
        glClearColor(0.0, 0.13, 0.22, 1.0);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    //солнце
    glColor3f(0.98,0.9,0.08);
    drawCircle(radiusSun, centerXSun, centerYSun);

    //луна
    glColor3f(1.0, 1.0, 0.6);
    drawCircle(radiusSun, centerXMoon, centerYMoon);

    //луг
    float radiusField = 2.0;
    float centerXField = 0.0;
    float centerYField = -1.75;
    glColor3f(0.5,0.8,0.2);
    drawCircle(radiusField, centerXField, centerYField);

    //свинки
    drawPig(0.75, 0);
    drawPig(-0.1, 0.3);
    drawPig(-0.45, -0.4);

    glFlush();//очищение всех буферов
}

void update(int value)
{
    angle += 0.01;
    centerXSun = orbitRadius * cos(angle);
    centerYSun = orbitRadius * sin(angle);
    centerXMoon = orbitRadius * cos(angle + M_PI);
    centerYMoon = orbitRadius * sin(angle + M_PI);

    if (centerYSun < 0){
        isDay = false;
    }
    else if (centerYSun > 0){
        isDay = true;
    }
    glutPostRedisplay();//текущее окно требует повторного отображения
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);//иниц библиотеку
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab1");
    glutDisplayFunc(displayMe);//вызов отображения тек окна
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}