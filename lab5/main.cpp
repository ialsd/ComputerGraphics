#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "freeglut.h"
#include "freeglut_ext.h"
#include "freeglut_std.h"
#include "glut.h"
#include <QtWidgets/QApplication>

float angle = 0.0;
float boxSize = 2.0;
bool textureMode = false;
GLuint textures[1];

GLuint loadTexture(const QString &fileName) {
    QImage image(fileName);
    if (image.isNull()) {
        qDebug() << "Failed to load texture:" << fileName;
        return 0;
    }
    QImage texture = image.convertToFormat(QImage::Format_RGBA8888);
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}

void initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    textures[0] = loadTexture(":/img/1.bmp");
}

void drawTextureBox() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-boxSize / 2, -boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(boxSize / 2, -boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(boxSize / 2, boxSize / 2, boxSize / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-boxSize / 2, boxSize / 2, boxSize / 2);

    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-boxSize / 2, -boxSize / 2, -boxSize / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(boxSize / 2, -boxSize / 2, -boxSize / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(boxSize / 2, boxSize / 2, -boxSize / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-boxSize / 2, boxSize / 2, -boxSize / 2);

    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-boxSize / 2, boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(boxSize / 2, boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(boxSize / 2, boxSize / 2, -boxSize / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-boxSize / 2, boxSize / 2, -boxSize / 2);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-boxSize / 2, -boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(boxSize / 2, -boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(boxSize / 2, -boxSize / 2, -boxSize / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-boxSize / 2, -boxSize / 2, -boxSize / 2);

    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-boxSize / 2, -boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(-boxSize / 2, -boxSize / 2, -boxSize / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(-boxSize / 2, boxSize / 2, -boxSize / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-boxSize / 2, boxSize / 2, boxSize / 2);

    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(boxSize / 2, -boxSize / 2, boxSize / 2);
    glTexCoord2f(1.0, 0.0); glVertex3f(boxSize / 2, -boxSize / 2, -boxSize / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(boxSize / 2, boxSize / 2, -boxSize / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(boxSize / 2, boxSize / 2, boxSize / 2);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawBox() {
    if (textureMode) {
        drawTextureBox();
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glutSolidCube(boxSize);
    }
}

void drawLight() {
    GLfloat light_position[] = { static_cast<GLfloat>(5.0 * cos(angle)), 5.0f, static_cast<GLfloat>(5.0 * sin(angle)), 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawBox();
    drawLight();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    angle += 0.01;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            boxSize += 0.1;
            break;
        case '-':
            boxSize -= 0.1;
            break;
        case 's':
            textureMode = !textureMode;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab5");
    initializeGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
