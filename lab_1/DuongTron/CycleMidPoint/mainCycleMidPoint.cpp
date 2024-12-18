#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

// Toa do cac diem ban dau va chi so de kiem tra lan nhap chuot
int x1s = 0, x2s = 0, y1s = 0, y2s = 50;
int index = 0;

// Ham khoi tao moi truong OpenGL
void init() {
    // Dat mau nen la mau trang
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // Thiet lap che do ma tran chieu
    glMatrixMode(GL_PROJECTION);
    // Xoa ma tran hien tai
    glLoadIdentity();
    // Thiet lap he toa do 2D tu -300 den 300 tren ca truc x va y
    glOrtho(-300, 300, -300, 300, -1, 1);
}

// Ham ve 8 diem doi xung cua duong tron
void draw8point(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

// Ham ve nua tren cua duong tron su dung thuat toan Midpoint
void CycleMidPoint1(int xc, int yc, int r) {
    double x, y, p, const1, const2;
    x = r; y = 0; p = 5 / 4 - r;

    while (y <= x) {
        draw8point(xc, yc, x, y);  // Ve 8 diem doi xung cua duong tron

        if (p < 0) {
            const1 = 2 * y + 3;
            p += const1;
        } else {
            const2 = 2 * (y - x) + 5;
            p += const2;
            x--;
        }
        y++;
    }
}

// Ham ve nua duoi cua duong tron su dung thuat toan Midpoint
void CycleMidPoint2(int xc, int yc, int r) {
    double x, y, p, const1, const2;
    x = 0; y = -r; p = 5 / 4 - r;

    while (x <= -y) {
        draw8point(xc, yc, x, y);  // Ve 8 diem doi xung cua duong tron

        if (p < 0) {
            const1 = 2 * x + 3;
            p += const1;
        } else {
            const2 = 2 * (y + x) + 5;
            p += const2;
            y++;
        }
        x++;
    }
}

// Ham hien thi (ve duong tron)
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Xoa bo dem mau
    glColor3f(1.0f, 0.0f, 0.0f);   // Thiet lap mau ve la do

    int r = sqrt(pow(x1s - x2s, 2) + pow(y1s - y2s, 2));  // Tinh ban kinh duong tron

    CycleMidPoint1(x1s, y1s, r);  // Ve nua tren cua duong tron

    glFlush();  // Hien thi noi dung da ve
}

// Ham xu ly su kien chuot
void mouse(int button, int state, int x, int y) {
    int xtest = 0, ytest = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // Kiem tra nhap chuot trai
        cout << "x=" << x << " y=" << y << endl;
        xtest = x - 300;   // Chuyen doi toa do x
        ytest = 300 - y;   // Chuyen doi toa do y

        if (index == 0) {
            x1s = xtest;
            y1s = ytest;
            index = 1;
        } else {
            x2s = xtest;
            y2s = ytest;
            index = 0;
        }

        glutPostRedisplay();  // Yeu cau ve lai man hinh
    }
}

// Ham chinh
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Khoi tao GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Thiet lap che do hien thi
    glutInitWindowSize(600, 600);  // Thiet lap kich thuoc cua so
    glutInitWindowPosition(50, 50);  // Thiet lap vi tri cua so
    glutCreateWindow("Duong tron");  // Tao cua so voi tieu de "Duong tron"
    init();  // Khoi tao OpenGL

    glutDisplayFunc(display);  // Dang ky ham hien thi
    glutMouseFunc(mouse);  // Dang ky ham xu ly chuot
    glutMainLoop();  // Vong lap su kien chinh cua GLUT

    return 0;
}

