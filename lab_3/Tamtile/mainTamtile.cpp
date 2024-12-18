#include <iostream> // Thu vien nhap xuat co ban
#include <bits/stdc++.h> // Thu vien tong hop (nen han che dung)
#include <GL/gl.h> // Thu vien OpenGL cho cac chuc nang do hoa co ban
#include <GL/glu.h> // Thu vien OpenGL Utility
#include <GL/glut.h> // Thu vien GLUT de quan ly cua so va su kien do hoa

#define M_PI 3.14159265358979323846 // Dinh nghia hang so pi
using namespace std;

// Kich thuoc cua so hien thi
int wScreen = 600, hScreen = 600;

// Cau truc luu thong tin diem
struct Point {
    double x, y; // Toa do x, y cua diem
    double z; // Toa do z cua diem (gia tri luon la 1)
    Point* next; // Con tro toi diem tiep theo trong danh sach lien ket
};

double tx = 0, ty = 0, Sx = 1, Sy = 1; // Bien chieu dai va ti le cua phep bien doi

struct Point* top = NULL; // Con tro top cua danh sach cac diem

// Ham push de them diem vao danh sach
void push(double x, double y) {
    struct Point* point;
    point = (Point*)calloc(1, sizeof(Point)); // Cap phat dong mot diem moi
    point->x = x; point->y = y; point->z = 1; point->next = NULL;

    // Neu danh sach rong, diem moi tro thanh top
    if (top == NULL) {
        top = point;
    } else {
        point->next = top; // Diem moi tro toi top hien tai
        top = point; // Diem moi tro thanh top moi
    }
}

// Ham pop de lay diem ra khoi danh sach
void pop(double* x, double* y, double* z) {
    if (top != NULL) {
        struct Point* point = top; // Luu diem top hien tai
        top = top->next; // Di chuyen top toi diem tiep theo
        *x = point->x; *y = point->y; *z = point->z; // Gan gia tri cho cac bien x, y, z

        delete(point); // Giai phong bo nho cua diem da pop ra
    }
}

// Ham khoi tao man hinh
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Mau nen trang
    glMatrixMode(GL_PROJECTION); // Chon che do phep chieu
    glLoadIdentity(); // Tai lai ma tran don vi
    glOrtho(-wScreen / 2, wScreen / 2, -hScreen / 2, hScreen / 2, -1, 1); // Thiet lap he toa do ortho
}

// Ham ve cac diem da duoc luu trong danh sach
void draw() {
    glColor3f(1.0f, 0.0f, 0.0f); // Mau do
    glBegin(GL_POLYGON); // Bat dau ve da giac
    Point* p = top;
    while (p != NULL) {
        glVertex3i(p->x, p->y, p->z); // Ve diem tai toa do (x, y, z)
        p = p->next;
    }
    delete(p); // Giai phong bo nho
    glEnd();
    glFlush(); // Cap nhat do hoa len man hinh
}

// Ham ve truc toa do
void drawTruc() {
    glColor3f(0.0, 1.0, 1.0); // Mau xanh duong nhat
    glBegin(GL_LINE_LOOP);
    glVertex2i(-wScreen / 2, 0); // Ve truc x
    glVertex2i(wScreen / 2, 0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(0, hScreen / 2); // Ve truc y
    glVertex2i(0, -hScreen / 2);
    glEnd();
}

// Ham hien thi man hinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Xoa man hinh
    glColor3f(0.0, 0.0, 0.0); // Mau den
    float size = 5.0; // Kich thuoc diem
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2i(tx, ty); // Ve diem tai vi tri tam (tx, ty)
    glEnd();
    glFlush();

    drawTruc(); // Ve truc toa do
    draw(); // Ve cac diem trong danh sach
}

// Ham ti le voi tam ti le (tx, ty)
void Tam_Ti_Le(double tx, double ty, double Sx, double Sy) {
    Point* p = top;
    double x, y, z;
    while (p != NULL) {
        x = p->x; y = p->y; z = p->z;
        p->x = x * Sx + (1 - Sx) * tx; // Tinh toa do x moi sau ti le
        p->y = y * Sy + (1 - Sy) * ty; // Tinh toa do y moi sau ti le
        p->z = 1;
        p = p->next;
    }
    delete(p); // Giai phong bo nho
}

// Ham xu ly su kien nhan chuot
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x = x - 300; // Chuyen toa do cua so sang toa do OpenGL
        y = 300 - y;
        push(x, y); // Them diem vao danh sach
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        x = x - 300;
        y = 300 - y;
        tx = x; // Cap nhat toa do tam ti le
        ty = y;
    }
    glutPostRedisplay(); // Cap nhat lai man hinh
}

// Ham xu ly su kien phim mui ten de thay doi ti le
void button(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: {
            Tam_Ti_Le(tx, ty, Sx, -Sy); // Ti le theo truc y
            glutPostRedisplay(); // Cap nhat lai man hinh
            break;
        }
        case GLUT_KEY_DOWN: {
            Tam_Ti_Le(tx, ty, Sx, -Sy); // Ti le theo truc y
            glutPostRedisplay(); // Cap nhat lai man hinh
            break;
        }
        case GLUT_KEY_LEFT: {
            Tam_Ti_Le(tx, ty, -Sx, Sy); // Ti le theo truc x
            glutPostRedisplay(); // Cap nhat lai man hinh
            break;
        }
        case GLUT_KEY_RIGHT: {
            Tam_Ti_Le(tx, ty, -Sx, Sy); // Ti le theo truc x
            glutPostRedisplay(); // Cap nhat lai man hinh
            break;
        }
    }
}

// Ham xu ly su kien phim nhan
void PhimNhan(unsigned char k, int x, int y) {
    printf("k= %d", k); // In ra ma phim nhan
    switch (k) {
        case 27: { // Phim ESC
            Sx = 1; Sy = 1; tx = 0; ty = 0; // Reset ti le va tam ve gia tri ban dau
            Tam_Ti_Le(tx, ty, Sx, Sy);
            glutPostRedisplay();
            break;
        }
        case 61: { // Phim '=' de tang ti le
            Sx += 0.01;
            Sy += 0.01;
            Tam_Ti_Le(tx, ty, Sx, Sy);
            glutPostRedisplay();
            break;
        }
        case 45: { // Phim '-' de giam ti le
            Sx -= 0.01;
            Sy -= 0.01;
            Tam_Ti_Le(tx, ty, Sx, Sy);
            glutPostRedisplay();
            break;
        }
        case 8: { // Phim xoa (backspace)
            double x, y, z;
            pop(&x, &y, &z); // Lay diem ra khoi danh sach
            Tam_Ti_Le(tx, ty, 1, 1); // Reset ti le ve gia tri ban dau
            cout << x << "-" << y << "-" << z << endl;
            glutPostRedisplay();
            break;
        }
        default:
            break;
    }
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Chon che do hien thi
    glutInitWindowSize(wScreen, hScreen); // Kich thuoc cua so
    glutInitWindowPosition(50, 50); // Vi tri cua so
    glutCreateWindow("Duong thang"); // Tao cua so moi
    init(); // Goi ham khoi tao

    glutDisplayFunc(display); // Gan ham hien thi
    glutMouseFunc(mouse); // Gan ham xu ly su kien chuot
    glutSpecialFunc(button); // Gan ham xu ly phim mui ten
    glutKeyboardFunc(PhimNhan); // Gan ham xu ly phim nhan
    glutMainLoop(); // Bat dau vong lap GLUT
}

