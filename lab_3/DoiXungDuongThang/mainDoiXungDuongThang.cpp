#include <iostream> 
#include <bits/stdc++.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 

#define M_PI 3.14159265358979323846 
using namespace std; 
int wScreen = 600, hScreen = 600; 
float a = -5, b = -80; // He so cua duong thang y = ax + b
float rad = (atan(a)); // Tinh radian cua a 

// Cau truc du lieu Point de luu thong tin ve diem
struct Point {
    float x, y; 
    float z; // Toa do z cua diem (luon bang 1 trong bai toan nay)
    Point* next; // Con tro toi diem tiep theo trong danh sach lien ket
};
struct Point* top = NULL; // Khoi tao con tro top bang NULL de bat dau danh sach rong

// Ham push de them diem vao danh sach
void push(float x, float y) {
    struct Point* point;
    point = (Point*)calloc(1, sizeof(Point)); // Cap phat dong mot diem moi
    point->x = x; point->y = y; point->z = 1; point->next = NULL; // Gan gia tri cho diem
    
    // Neu danh sach rong, diem moi tro thanh top
    if (top == NULL) {
        top = point;
    } else {
        point->next = top; // Diem moi tro toi diem truoc do va tro thanh top
        top = point;
    }
}

// Ham pop de lay diem ra khoi danh sach
void pop(float* x, float* y, float* z) {
    if (top != NULL) {
        struct Point* point;
        point = top; // Luu diem top hien tai
        top = top->next; // Di chuyen top toi diem tiep theo
        *x = point->x; *y = point->y; *z = point->z; // Gan gia tri cho cac bien x, y, z
        
        delete(point); // Giai phong bo nho cua diem da pop ra
    }
}

// Ham doi xung diem qua duong thang y = ax + b
void doixung(float x, float y) {
    cout << rad << endl; // In ra gia tri rad de kiem tra
    float cos2x = cos(2 * rad), sin2x = sin(2 * rad);
    float xs = x * cos2x + y * sin2x + (b / a) * (cos2x - 1);
    float ys = x * sin2x - y * cos2x + (b / a) * sin2x;

    glVertex3d(xs, ys, 1); // Ve diem doi xung tren man hinh
}

// Ham khoi tao man hinh
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Mau nen trang
    glMatrixMode(GL_PROJECTION); // Chon che do phep chieu
    glLoadIdentity(); // Dat lai ma tran don vi
    glOrtho(-wScreen / 2, wScreen / 2, -hScreen / 2, hScreen / 2, -1, 1); // Thiet lap he toa do
}

// Ham ve duong thang y = ax + b
void createLine() {
    int x_max = (wScreen / 2) - 50, x_min = -(wScreen / 2) + 50;
    int y_x_max = a * x_max + b, y_x_min = a * x_min + b;

    glColor3f(1.0f, 0.0f, 0.0f); // Mau do
    glBegin(GL_LINE_LOOP); // Bat dau ve duong thang
        glVertex2i(x_max, y_x_max);
        glVertex2i(x_min, y_x_min);
    glEnd();
    glFlush(); // Hoan thanh ve
}

// Ham ve cac diem da duoc luu trong danh sach
void draw() {
    glColor3f(1.0f, 0.0f, 0.0f); // Mau do
    glBegin(GL_POLYGON); // Bat dau ve da giac
        Point* p = top;
        while (p != NULL) {
            glVertex3i(p->x, p->y, p->z);
            p = p->next;
        }
    glEnd();

    glBegin(GL_POLYGON); // Ve hinh doi xung cua da giac
        p = top;
        while (p != NULL) {
            doixung(p->x, p->y);
            p = p->next;
        }
        delete(p); // Giai phong bo nho
    glEnd();

    glFlush();
}

// Ham ve truc toa do
void drawTruc() {
    glColor3f(0.0, 1.0, 1.0); // Mau xanh duong nhat
    glBegin(GL_LINE_LOOP);
        glVertex2i(-wScreen / 2, 0);
        glVertex2i(wScreen / 2, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2i(0, hScreen / 2);
        glVertex2i(0, -hScreen / 2);
    glEnd();
    glFlush();
}

// Ham hien thi man hinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Xoa man hinh
    createLine(); // Ve duong thang
    drawTruc(); // Ve truc toa do
    draw(); // Ve da giac va doi xung
}

// Ham xu ly su kien nhan chuot
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x = x - 300; // Chuyen toa do cua so sang toa do he quy chieu
        y = 300 - y;
        push(x, y); // Them diem vao danh sach
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        x = x - 300;
        y = 300 - y;
    }
    glutPostRedisplay(); // Cap nhat lai man hinh
}

// Ham xu ly su kien ban phim mui ten
void button(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: {
            break;
        }
        case GLUT_KEY_DOWN: {
            break;
        }
        case GLUT_KEY_LEFT: {
            break;
        }
        case GLUT_KEY_RIGHT: {
            break;
        }
    }
}

// Ham xu ly su kien phim nhan
void PhimNhan(unsigned char k, int x, int y) {
    printf("k= %d", k); // In ra gia tri phim nhan
    switch (k) {
        case 8: { // Phim xoa (backspace)
            float x, y, z;
            pop(&x, &y, &z); // Lay diem ra khoi danh sach
            cout << x << "-" << y << "-" << z << endl;
            glutPostRedisplay(); // Cap nhat lai man hinh
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
    glutMainLoop(); // Bat dau vong lap chuong trinh
}

