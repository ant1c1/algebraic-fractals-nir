#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>

// Сколько точек рисуем
const int N = 500;

// Функция: случайное число с плавающей точкой в диапазоне [min, max]
float randomInRange(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Размер точки побольше, чтобы её было видно
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++) {
        // Случайные координаты в диапазоне [-1, 1]
        float x = randomInRange(-1.0f, 1.0f);
        float y = randomInRange(-1.0f, 1.0f);

        // Случайный цвет
        float r = randomInRange(0.0f, 1.0f);
        float g = randomInRange(0.0f, 1.0f);
        float b = randomInRange(0.0f, 1.0f);

        glColor3f(r, g, b);
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Ортографическая проекция от -1.1 до 1.1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.1, 1.1, -1.1, 1.1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Инициализация генератора случайных чисел
    // (если не вызвать srand, rand() будет всегда выдавать одну и ту же
    // последовательность при каждом запуске программы)
    srand((unsigned int)time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Random Points");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
