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
        glVertex2f(x + centerX, y + centerY);
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
void drawPig(float centerXSheep, float centerYSheep){
    float earRadius = 0.03;
    float eyeRadius = 0.01;
    float noseRadius = 0.02;
    float nostrilRadius = 0.005;
    glColor3f(1.0, 0.61, 0.67);
    drawCircle(radiusSun, centerXSheep, centerYSheep);

    glColor3f(0.87, 0.27, 0.57);
    drawCircle(earRadius, centerXSheep - 0.05, centerYSheep + 0.05);
    drawCircle(earRadius, centerXSheep + 0.05, centerYSheep + 0.05);

    glColor3f(0.5, 0.5, 0.5);
    drawSquare(centerXSheep - 0.04, centerXSheep - 0.02,
               centerYSheep - 0.07, centerYSheep - 0.12);
    drawSquare(centerXSheep + 0.02, centerXSheep + 0.04,
               centerYSheep - 0.07, centerYSheep - 0.12);

    glColor3f(0, 0, 0);
    drawCircle(eyeRadius, centerXSheep-0.02, centerYSheep);
    drawCircle(eyeRadius, centerXSheep+0.02, centerYSheep);

    glColor3f(0.87, 0.27, 0.57);
    drawCircle(noseRadius, centerXSheep, centerYSheep - 0.03);

    glColor3f(0, 0, 0);
    drawCircle(nostrilRadius, centerXSheep + 0.007, centerYSheep - 0.03);
    drawCircle(nostrilRadius, centerXSheep - 0.007, centerYSheep - 0.03);
}
void drawFlower(float x, float y)
{
    glLineWidth(3.0);
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.2);
    glEnd();
    glLineWidth(1.0);

    float flowerRadius = 0.05;
    int numPetals = 6;

    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < numPetals; i++){
        float angle = 2.0f * M_PI * i / numPetals;
        float xOffset = flowerRadius * cos(angle);
        float yOffset = flowerRadius * sin(angle);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 5; j++){
            float petalAngle = 2.0f * M_PI * (j + i % 2 * 0.5) / 5;
            float xPetal = xOffset + 0.03 * cos(petalAngle);
            float yPetal = yOffset + 0.075 * sin(petalAngle);
            glVertex2f(xPetal + x, yPetal + y);
        }
        glEnd();
    }
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.03, y - 0.07);
    glVertex2f(x - 0.08, y - 0.15);
    glVertex2f(x, y - 0.11);
    glVertex2f(x + 0.08, y - 0.15);
    glVertex2f(x + 0.03, y - 0.07);
    glEnd();
}

void displayMe(void)
{
    if (isDay){
        glClearColor(0.69, 0.93, 0.93, 1);
    }
    else{
        glClearColor(0.0, 0.13, 0.22, 1.0);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    //Солнце
    glColor3f(0.98,0.9,0.08);
    drawCircle(radiusSun, centerXSun, centerYSun);

    //Луна
    glColor3f(1.0, 1.0, 0.6);
    drawCircle(radiusSun, centerXMoon, centerYMoon);

    //Луг
    float radiusField = 2.0;
    float centerXField = 0.0;
    float centerYField = -1.75;
    glColor3f(0.5,0.8,0.2);
    drawCircle(radiusField, centerXField, centerYField);

    //Свинки
    drawPig(0.75, 0);
    drawPig(-0.1, 0.3);
    drawPig(-0.45, -0.4);

    //Цветы
    drawFlower(-0.7, -0.5);
    drawFlower(0.0, -0.4);
    drawFlower(0.7, -0.6);
    glFlush();
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