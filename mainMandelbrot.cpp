#include <GL/freeglut.h>
#include <vector>
#include <cmath>

const int W = 800;
const int H = 600;
const int MAX_ITER = 256;

std::vector<unsigned char> pixels(W * H * 4);

// Считаем цвет одной точки
void computePixel(int px, int py) {
    // Переводим координаты пикселя в координаты комплексной плоскости
    // Видимая область: x от -2 до 1, y от -1.5 до 1.5
    double cx = -2.0 + 3.0 * px / W;
    double cy = -1.5 + 3.0 * py / H;

    double zx = 0.0, zy = 0.0;
    int i = 0;

    // Итерации z = z^2 + c
    while (zx*zx + zy*zy <= 4.0 && i < MAX_ITER) {
        double tmp = zx*zx - zy*zy + cx;
        zy = 2.0 * zx * zy + cy;
        zx = tmp;
        i++;
    }

    unsigned char r, g, b;

    if (i == MAX_ITER) {
        // Точка внутри множества - чёрный
        r = g = b = 0;
    } else {
        // Чем дольше держалась точка - тем "светлее"
        // Простая синевато-зелёная палитра
        r = (unsigned char)(i * 5 % 256);
        g = (unsigned char)(i * 3 % 256);
        b = (unsigned char)(i * 7 % 256);
    }

    int idx = (py * W + px) * 4;
    pixels[idx + 0] = r;
    pixels[idx + 1] = g;
    pixels[idx + 2] = b;
    pixels[idx + 3] = 255;
}

// Считаем все пиксели
void renderMandelbrot() {
    for (int py = 0; py < H; py++) {
        for (int px = 0; px < W; px++) {
            computePixel(px, py);
        }
    }
}

// Рисуем
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(0, 0);
    glDrawPixels(W, H, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glutSwapBuffers();
}

// Клавиатура: только выход по ESC
void keyboard(unsigned char key, int, int) {
    if (key == 27) {          // ESC
        glutLeaveMainLoop();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(W, H);
    glutCreateWindow("Mandelbrot");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Считаем один раз при запуске
    renderMandelbrot();

    glutMainLoop();
    return 0;
}