#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>

// Сколько случайных точек рисуем
const int N = 5000;

// Максимальное число итераций
const int MAX_ITER = 256;

// Диапазон координат на комплексной плоскости
const float X_MIN = -2.0f;
const float X_MAX = 1.0f;
const float Y_MIN = -1.5f;
const float Y_MAX = 1.5f;

// Случайное число с плавающей точкой в диапазоне [min, max]
float randomInRange(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

// Вычисляем число итераций до "побега" точки c = cx + i*cy
// Возвращает MAX_ITER, если точка осталась ограниченной
int mandelbrotIterations(float cx, float cy) {
    float zx = 0.0f, zy = 0.0f;
    int i = 0;
    while (zx * zx + zy * zy <= 4.0f && i < MAX_ITER) {
        float tmp = zx * zx - zy * zy + cx;
        zy = 2.0f * zx * zy + cy;
        zx = tmp;
        i++;
    }
    return i;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(3.0f);

    glBegin(GL_POINTS);
    for (int k = 0; k < N; k++) {
        // Случайная точка на комплексной плоскости
        float cx = randomInRange(X_MIN, X_MAX);
        float cy = randomInRange(Y_MIN, Y_MAX);

        // Считаем, сколько итераций она выдержала
        int iter = mandelbrotIterations(cx, cy);

        // Определяем цвет
        float r, g, b;
        if (iter == MAX_ITER) {
            // Точка внутри множества — чёрная
            r = 0.0f; g = 0.0f; b = 0.0f;
        } else {
            // Точка сбежала. Чем больше итераций — тем "светлее".
            // Нормируем число итераций в диапазон [0, 1]
            float t = (float)iter / (float)MAX_ITER;

            // Палитра: тёмно-синий → голубой → белый
            r = t;
            g = t;
            b = 1.0f;
        }

        glColor3f(r, g, b);
        glVertex2f(cx, cy);
    }
    glEnd();

    glutSwapBuffers();
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Небольшой запас по краям, чтобы точки у границ были видны
    gluOrtho2D(X_MIN - 0.1, X_MAX + 0.1, Y_MIN - 0.1, Y_MAX + 0.1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    srand((unsigned int)time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bridge: Random Points + Mandelbrot");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}