#include <GL/glut.h>
#include <math.h>

float angle = 0.0;
float boxSize = 2.0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);//обновление буфера глубины
    glEnable(GL_LIGHTING);//включение расчета освещения
    glEnable(GL_LIGHT0);//разбл ист света
    glEnable(GL_COLOR_MATERIAL);//влияет на расчет освещения
}

void drawBox() {
    glutSolidCube(boxSize);
}

void drawLight() {
    GLfloat light_position[] = { static_cast<GLfloat>(5.0 * cos(angle)), 5.0f, static_cast<GLfloat>(5.0 * sin(angle)), 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//сброс матрицы
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//создание матрицы просмотра
    drawBox();
    drawLight();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);//матрица проецирования 3д в 2д
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);//матрица перспективы
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
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab3");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}