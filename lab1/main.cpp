#include "GL/glut.h"
#include <math.h>

void displayMe(void)
{
    glClearColor(0.69, 0.93, 0.93, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5,0.8,0.2);
    glBegin(GL_POLYGON);
    float radius = 2.0;
    float centerX = 0.0;
    float centerY = -2.0;
    int numVertices = 100;
    for (int i = 0; i < numVertices; i++)
    {
        float angle = i * (M_PI / (numVertices - 1));
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab1");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}