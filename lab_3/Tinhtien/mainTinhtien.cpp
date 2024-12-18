#include <iostream> // Thu vien nhap xuat co ban
#include <bits/stdc++.h> // Thu vien tong hop (nen han che dung vi lam tang kich thuoc chuong trinh)
#include <GL/gl.h> // Thu vien OpenGL cho cac chuc nang do hoa co ban
#include <GL/glu.h> // Thu vien OpenGL Utility
#include <GL/glut.h> // Thu vien GLUT de quan ly cua so va do hoa
using namespace std;

// Cau truc Point de luu toa do cua diem
struct Point {
    int x, y; // Toa do x, y cua diem
    int z; // Toa do z cua diem (gia tri luon la 1)
    Point* next; // Con tro toi diem tiep theo trong danh sach lien ket
};

struct Point* top = NULL; // Khoi tao con tro top de quan ly danh sach cac diem

// Ham push de them diem vao danh sach
void push(int x, int y) {
    struct Point* point;
    point = (Point*)calloc(1, sizeof(Point)); // Cap phat dong mot diem moi
    point->x = x; point->y = y; point->z = 1; point->next = NULL;

    // Neu danh sach rong, diem moi tro thanh top
    if (top == NULL) {
        top = point;
    } else {
        point->next = top; // Diem moi tro toi top hien tai va tro thanh top moi
        top = point;
    }
}

// Ham pop de lay diem ra khoi danh sach
void pop(int* x, int* y, int* z) {
    if (top != NULL) {
        struct Point* point;
        point = top; // Luu diem top hien tai
        top = top->next; // Di chuyen top toi diem tiep theo
        *x = point->x; *y = point->y; *z = point->z; // Gan gia tri cho cac bien x, y, z

        delete(point); // Giai phong bo nho cua diem da pop ra
    }
}

// Ham khoi tao man hinh
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Mau nen trang
    glMatrixMode(GL_PROJECTION); // Chon che do phep chieu
    glLoadIdentity(); // Dat lai ma tran don vi
    glOrtho(-300, 300, -300, 300, -1, 1); // Thiet lap he toa do ortho
}

// Ham ve da giac tu cac diem trong danh sach
void draw() {
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

// Ham hien thi tren cua so
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Xoa bo dem do hoa
    glColor3f(1.0f, 0.0f, 0.0f); // Dat mau ve la mau do
    draw(); // Ve da giac
}

// Ham xu ly su kien nhan chuot
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x = x - 300; // Chuyen toa do cua so sang toa do OpenGL
        y = 300 - y;
        push(x, y); // Them diem vao danh sach
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        int x, y, z;
        pop(&x, &y, &z); // Lay diem ra khoi danh sach
        cout << x << "-" << y << "-" << z << endl; // In toa do diem da xoa
    }
    glutPostRedisplay(); // Cap nhat lai man hinh
}

// Ham tinh tien da giac theo vector (tx, ty)
void tinhtien(int tx, int ty) {
    Point* p = top;
    while (p != NULL) {
        p->x = p->x + tx; // Tinh lai toa do x sau khi tinh tien
        p->y = p->y + ty; // Tinh lai toa do y sau khi tinh tien
        p->z = 1;
        p = p->next;
    }
    delete(p); // Giai phong bo nho
}

// Ham xu ly su kien nhan phim mui ten
void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: {
            tinhtien(0, 5); // Tinh tien da giac len tren 5 don vi
            break;
        }
        case GLUT_KEY_DOWN: {
            tinhtien(0, -5); // Tinh tien da giac xuong duoi 5 don vi
            break;
        }
        case GLUT_KEY_LEFT: {
            tinhtien(-5, 0); // Tinh tien da giac sang trai 5 don vi
            break;
        }
        case GLUT_KEY_RIGHT: {
            tinhtien(5, 0); // Tinh tien da giac sang phai 5 don vi
            break;
        }
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi tinh tien
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Chon che do hien thi
    glutInitWindowSize(600, 600); // Kich thuoc cua so
    glutInitWindowPosition(50, 50); // Vi tri cua so
    glutCreateWindow("Duong thang"); // Tao cua so moi voi tieu de "Duong thang"
    init(); // Goi ham khoi tao

    glutDisplayFunc(display); // Gan ham hien thi
    glutMouseFunc(mouse); // Gan ham xu ly su kien chuot
    glutSpecialFunc(keyboard); // Gan ham xu ly phim mui ten
    glutMainLoop(); // Bat dau vong lap GLUT
}

