#include <math.h>
#include <time.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

// Ham khoi tao
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Thiet lap mau nen la mau trang
    glOrtho(0, 600, 0, 600, -1, 1);    // Thiet lap he toa do 2D voi kich thuoc 600x600
}

// Cau truc du lieu LIST de luu toa do diem va cai dat danh sach lien ket
struct LIST {
	int x, y;                // Toa do diem (x, y)
	struct LIST* next;       // Con tro toi phan tu tiep theo trong danh sach
};

struct LIST* head = NULL;    // Con tro dau danh sach
struct LIST* last = NULL;    // Con tro cuoi danh sach

// Ham day phan tu vao cuoi danh sach lien ket
void push(int x, int y) {
    struct LIST* point;
    point = (LIST *) calloc(1, sizeof(LIST)); // Cap phat bo nho cho mot diem moi
    point->x = x; point->y = y; point->next = NULL; // Khoi tao toa do va con tro next
    if (head == NULL) {
        head = point;   // Neu danh sach rong, diem nay la dau danh sach
        last = point;   // Va cung la cuoi danh sach
    } else {
        last->next = point;  // Neu khong, gan diem moi vao sau diem cuoi
        last = point;        // Cap nhat diem cuoi cua danh sach
    }
}

// Ham lay phan tu tu dau danh sach lien ket
void pop(int *x, int *y) {
    struct LIST* point;
    point = head;              // Gan point bang dau danh sach
    head = head->next;         // Cap nhat dau danh sach
    *x = point->x; *y = point->y; // Tra ve toa do cua diem lay ra
    delete(point);             // Giai phong bo nho cho diem da lay
}

// Ham Boundary Fill su dung de quy de di mau
void BoundaryFill(int x, int y, float* fillColor, float* bc) {
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);  // Doc mau tai toa do (x, y)
    
    // Kiem tra neu diem hien tai khong co mau ranh gioi va khong co mau dien
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) && 
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);  // Thiet lap mau ve la fillColor
        glBegin(GL_POINTS);
            glVertex2i(x, y);    // Ve diem tai (x, y)
        glEnd();
        glFlush();               // Thuc thi lenh ve ngay lap tuc
        
        push(x, y);              // Day diem hien tai vao danh sach lien ket
    }
}

// Ham Boundary Fill su dung danh sach lien ket de thay the de quy
void BoundaryFill_Stack(int x0, int y0, float* fillColor, float* bc) {
    int x, y;

    glColor3f(fillColor[0], fillColor[1], fillColor[2]);  // Thiet lap mau ve la fillColor
    glBegin(GL_POINTS);
        glVertex2i(x0, y0);  // Ve diem dau tien tai (x0, y0)
    glEnd();
    glFlush();

    push(x0, y0);             // Day diem ban dau vao danh sach
    while (head != NULL) {    // Lap lai cho den khi danh sach rong
        pop(&x, &y);          // Lay diem tu dau danh sach
        
        BoundaryFill(x - 1, y, fillColor, bc);  // Diem ben trai
        BoundaryFill(x + 1, y, fillColor, bc);  // Diem ben phai
        BoundaryFill(x, y + 1, fillColor, bc);  // Diem phia tren
        BoundaryFill(x, y - 1, fillColor, bc);  // Diem phia duoi
    }
}

// Ham xu ly su kien nhan chuot
void mouse(int btn, int state, int x, int y) {
    y = 600 - y;  // Chuyen doi toa do y tu he toa do cua so sang he toa do OpenGL
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float bCol[] = {1, 0, 0};  // Mau ranh gioi (do)
        float color[] = {0, 1, 1}; // Mau dien (cyan)
        BoundaryFill_Stack(x, y, color, bCol);  // Goi ham BoundaryFill_Stack tai vi tri nhan chuot
    }
}

// Ham ve hinh da giac co ranh gioi
void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);  // Xoa man hinh voi mau nen
    glColor3f(1, 0, 0);            // Thiet lap mau ve la mau do
    
    glBegin(GL_LINE_LOOP);         // Ve hinh da giac khong dong kin (mang dinh)
        glVertex2i(300, 400);      // Dinh thu nhat
        glVertex2i(500, 400);      // Dinh thu hai
        glVertex2i(600, 300);      // Dinh thu ba
        glVertex2i(205, 350);      // Dinh thu tu
        glVertex2i(200, 100);      // Dinh thu nam
    glEnd();

    glFlush();  // Dam bao lenh ve duoc thuc thi ngay lap tuc
}

// Ham main chinh cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv);                  // Khoi tao GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Thiet lap che do hien thi: bo dem don va RGB
    glutInitWindowSize(600, 600);           // Thiet lap kich thuoc cua so 600x600
    glutInitWindowPosition(0, 0);           // Vi tri cua so tai goc tren ben trai man hinh
    glutCreateWindow("Boundary Fill");      // Tao cua so voi ten "Boundary Fill"
    glutDisplayFunc(mydisplay);             // Dang ky ham ve mydisplay
    glutMouseFunc(mouse);                   // Dang ky ham xu ly su kien chuot
    init();                                 // Goi ham khoi tao
    glutMainLoop();                         // Vong lap chinh cua GLUT de xu ly su kien
    return 0;
}

