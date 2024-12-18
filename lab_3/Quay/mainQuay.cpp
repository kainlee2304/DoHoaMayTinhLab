#include <iostream> // Thu vien nhap xuat co ban
#include <bits/stdc++.h> // Thu vien tong hop (nen han che dung vi lam tang kich thuoc chuong trinh)
#include <GL/gl.h> // Thu vien OpenGL cho cac chuc nang do hoa
#include <GL/glu.h> // Thu vien OpenGL Utility
#include <GL/glut.h> // Thu vien GLUT de quan ly cua so va do hoa

#define M_PI 3.14159265358979323846 // Dinh nghia hang so pi
using namespace std;

// Cau truc Point de luu thong tin toa do diem trong khong gian
struct Point {
    int x, y; // Toa do x, y cua diem
    int z; // Toa do z cua diem (gia tri luon la 1)
    Point* next; // Con tro toi diem tiep theo trong danh sach
};
int size = 0; // So luong diem trong danh sach
int goc = 0; // Goc quay
int diemxoay = 1; // Diem de lam truc quay
struct Point* top = NULL; // Con tro top de luu diem dau danh sach

Point* point_rotate = NULL; // Con tro de luu diem dang xoay

// Ham push de them diem vao danh sach
void push(int x, int y) {
    struct Point* point;
    point = (Point*)calloc(1, sizeof(Point)); // Cap phat dong mot diem moi
    point->x = x; point->y = y; point->z = 1; point->next = NULL;

    if (top == NULL) {
        top = point; // Neu danh sach rong, diem moi tro thanh top
    } else {
        point->next = top; // Diem moi tro toi diem hien tai va tro thanh top
        top = point;
    }
    size++; // Tang kich thuoc danh sach
}

// Ham pop de xoa diem khoi danh sach
void pop(int* x, int* y, int* z) {
    if (top != NULL) {
        struct Point* point;
        point = top; // Lay diem top hien tai
        top = top->next; // Chuyen top toi diem tiep theo
        *x = point->x; *y = point->y; *z = point->z;

        delete(point); // Giai phong bo nho
        size--; // Giam kich thuoc danh sach
    }
}

// Ham khoi tao OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Dat mau nen trang
    glMatrixMode(GL_PROJECTION); // Chuyen sang che do phep chieu
    glLoadIdentity(); // Tai lai ma tran don vi
    glOrtho(-300, 300, -300, 300, -1, 1); // Thiet lap he toa do ortho
}

// Ham ve da giac tu danh sach cac diem
void draw() {
    glBegin(GL_POLYGON);
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
    glColor3f(1.0f, 0.0f, 0.0f); // Dat mau ve do
    draw(); // Ve da giac

    float size = 5.0f; // Kich thuoc diem quay
    glPointSize(size);
    if (point_rotate != NULL) {
        glBegin(GL_POINTS);
            glColor3f(0.0, 0.0, 0.0); // Dat mau ve den cho diem xoay
            glVertex3i(point_rotate->x, point_rotate->y, point_rotate->z);
        glEnd();
        glFlush();
    }
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
        cout << x << "-" << y << "-" << z << endl; // In thong tin diem
    }
    glutPostRedisplay(); // Cap nhat lai man hinh
}

// Ham chon diem xoay trong danh sach
Point* swapPointRotate(int index) {
    Point* point = top;
    if (index <= size) {
        index = size - index; // Tim diem tu dau danh sach
        while (index > 0) {
            point = point->next;
            index--;
        }
    }
    return point;
}

// Ham xoay da giac quanh diem chon
void xoay() {
    float rad = goc * M_PI / 180; // Chuyen goc tu do sang radian
    cout << "goc= " << goc << endl;
    cout << "rad= " << rad << endl << "========" << endl;

    if (point_rotate == NULL) {
        point_rotate = top; // Neu chua co diem xoay, chon diem top
    } else {
        point_rotate = swapPointRotate(diemxoay); // Chon diem xoay tu danh sach
    }

    int tx = point_rotate->x, ty = point_rotate->y; // Toa do diem quay
    int x, y;
    Point* p = top;

    while (p != NULL) {
        if (p->x != point_rotate->x || p->y != point_rotate->y) { // Neu khong phai diem quay
            x = p->x; y = p->y;
            p->x = x * cos(rad) - y * sin(rad) + (1 - cos(rad)) * tx + ty * sin(rad); // Cong thuc quay
            p->y = x * sin(rad) + y * cos(rad) + (1 - cos(rad)) * ty - tx * sin(rad);
            p->z = 1;
        }
        p = p->next;
    }
    delete(p); // Giai phong bo nho
}

// Ham xu ly su kien phim mui ten de thay doi goc quay
void buttonrotate(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: {
            goc += 1; // Tang goc len 1 do
            if (goc > 360) goc = 0; // Neu goc vuot qua 360 thi quay ve 0
            xoay(); // Goi ham xoay
            glutPostRedisplay(); // Cap nhat lai man hinh
            break;
        }
        case GLUT_KEY_RIGHT: {
            goc -= 1; // Giam goc xuong 1 do
            if (goc < 0) goc = 360; // Neu goc < 0 thi quay ve 360
            xoay(); // Goi ham xoay
            glutPostRedisplay(); // Cap nhat lai man hinh
            break;
        }
    }
}

// Ham xu ly su kien nhan phim de chon diem lam truc quay
void PhimNhanChonGocXoay(unsigned char k, int x, int y) {
    printf("k= %d", k); // In ra gia tri phim nhan
    switch (k) {
        case 49: diemxoay = 1; glutPostRedisplay(); break; // Phim '1' chon diem 1
        case 50: diemxoay = 2; glutPostRedisplay(); break; // Phim '2' chon diem 2
        case 51: diemxoay = 3; glutPostRedisplay(); break; // Phim '3' chon diem 3
        case 52: diemxoay = 4; glutPostRedisplay(); break; // Phim '4' chon diem 4
        case 53: diemxoay = 5; glutPostRedisplay(); break; // Phim '5' chon diem 5
        case 54: diemxoay = 6; glutPostRedisplay(); break; // Phim '6' chon diem 6
        case 55: diemxoay = 7; glutPostRedisplay(); break; // Phim '7' chon diem 7
        case 56: diemxoay = 8; glutPostRedisplay(); break; // Phim '8' chon diem 8
        case 57: diemxoay = 9; glutPostRedisplay(); break; // Phim '9' chon diem 9
        default: break;
    }
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Chon che do hien thi
    glutInitWindowSize(600, 600); // Kich thuoc cua so
    glutInitWindowPosition(50, 50); // Vi tri cua so
    glutCreateWindow("Phep xoay"); // Tao cua so moi voi ten "Phep xoay"
    init(); // Khoi tao OpenGL

    glutDisplayFunc(display); // Gan ham hien thi
    glutMouseFunc(mouse); // Gan ham xu ly su kien chuot
    glutSpecialFunc(buttonrotate); // Gan ham xu ly phim mui ten
    glutKeyboardFunc(PhimNhanChonGocXoay); // Gan ham xu ly phim nhan
    glutMainLoop(); // Bat dau vong lap GLUT
}

