#include <GL/glut.h>
#include <math.h>

float angle = 0.0;
float boxSize = 2.0;
bool wireframeMode = false;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);//обновление буфера глубины
    glEnable(GL_LIGHTING);//включение расчета освещения
    glEnable(GL_LIGHT0);//разбл ист света
    glEnable(GL_COLOR_MATERIAL);//влияет на расчет освещения с учетом граней
    glEnable(GL_TEXTURE_2D);//разрешение наложение текстуры
}

void drawTransparentCube(float size) {
    glEnable(GL_BLEND);//разр наложение цветов
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//алг смешивания

    glBegin(GL_QUADS);

    glColor4f(1.0, 0.0, 0.0, 0.5);//красный
    glNormal3f(0.0, 0.0, 1.0);//уст нормали для создания корректного освещения сцены
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);

    glColor4f(0.0, 1.0, 0.0, 0.5);//зеленый
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);

    glColor4f(0.0, 0.0, 1.0, 0.5);//синий
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);

    glColor4f(1.0, 1.0, 0.0, 0.5);//желтый
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);

    glColor4f(0.0, 1.0, 1.0, 0.5);//бирюзовый
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);

    glColor4f(1.0, 0.0, 1.0, 0.5);//фиолетовый
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, size / 2);

    glEnd();

    glDisable(GL_BLEND);
}

void drawBox() {
    if (wireframeMode) {
        glEnable(GL_ALPHA_TEST);//разр обработки 4 компонента цвета
        glDepthMask(GL_FALSE);
        drawTransparentCube(boxSize);
        glDepthMask(GL_TRUE);
        glDisable(GL_ALPHA_TEST);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//уст опции для отрисовки многоугольника
        glColor4f(1.0, 1.0, 1.0, 0.5);
        glutSolidCube(boxSize);
    }
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
        case 't':
            wireframeMode = !wireframeMode;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab4");
    init();
    glutDisplayFunc(display);//вызов отображения тек окна
    glutReshapeFunc(reshape);
    glutTimerFunc(25, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
