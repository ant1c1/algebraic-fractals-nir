#include <GL/freeglut.h>
#include <stdio.h>

float x1, y1_, x2, y2;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
        glColor3us(255,255,255);
        glVertex2f(x1, y1_);
        glColor3us(0,0,0);
        glVertex2f(x2, y2);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    printf("Координаты от -1.0 до 1.0\n");
    printf("X1: "); scanf("%f", &x1);
    printf("Y1: "); scanf("%f", &y1_);
    printf("X2: "); scanf("%f", &x2);
    printf("Y2: "); scanf("%f", &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Line");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}