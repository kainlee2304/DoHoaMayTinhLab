#include <math.h>
#include <time.h>
#include <GL/glut.h>
 
// Ham khoi tao
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Thiet lap mau nen la mau trang
    glOrtho(0, 600, 0, 600, -1, 1);    // Thiet lap he toa do 2D tu (0,0) den (600,600)
}

// Ham de thuc hien thuat toan Boundary Fill
void bound_it(int x, int y, float* fillColor, float* bc) {
    float color[3];//dai dien 3 mau RGB(red,green,blue)
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);  // Doc mau cua diem (x, y) tren man hinh va luu vao mang color

    // Kiem tra neu mau cua diem (x, y) khac mau ranh gioi (bc) va khac mau can dien (fillColor)
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) && 
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);  // Thiet lap mau ve hien tai la mau fillColor
        glBegin(GL_POINTS);   // Bat dau ve diem
            glVertex2i(x, y); // Ve diem tai toa do (x, y)
        glEnd();
        glFlush();  // Thuc thi lenh ve ngay lap tuc
        
        // Goi de quy cho 4 diem lan can
        bound_it(x - 1, y, fillColor, bc); // Di qua trai
        bound_it(x, y + 1, fillColor, bc); // Di len tren
        bound_it(x + 1, y, fillColor, bc); // Di qua phai
        bound_it(x, y - 1, fillColor, bc); // Di xuong duoi
    }
}

// Ham xu ly su kien nhan chuot
void mouse(int btn, int state, int x, int y) {
    y = 600 - y; // Chuyen doi toa do y tu he toa do cua so sang he toa do OpenGL

    // Kiem tra neu nut chuot trai duoc nhan xuong
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float bCol[] = {1, 0, 0};  // Mau ranh gioi (mau do)
        float color[] = {0, 1, 1}; // Mau dien (xanh cyan)
        bound_it(x, y, color, bCol); // Goi ham boundary fill tai vi tri (x, y)
    }
}

// Ham ve hinh da giac
void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);   // Xoa man hinh voi mau nen
    glColor3f(1, 0, 0);  // Thiet lap mau ve la mau do
    
    glBegin(GL_LINE_LOOP);  // Bat dau ve mot hinh da giac dong
        glVertex2i(250, 400); // Dinh thu nhat
        glVertex2i(350, 400); // Dinh thu hai
        glVertex2i(275, 300); // Dinh thu ba
        glVertex2i(205, 350); // Dinh thu tu
        glVertex2i(200, 100); // Dinh thu nam
    glEnd();

    glFlush();  // Dam bao lenh ve duoc thuc thi ngay lap tuc
}

// Ham main chinh cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Khoi tao GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Thiet lap che do hien thi: bo dem don va RGB
    glutInitWindowSize(600, 600);  // Thiet lap kich thuoc cua so 600x600
    glutInitWindowPosition(0, 0);  // Vi tri cua so tai goc tren ben trai man hinh
    glutCreateWindow("Boundary Fill");  // Tao cua so voi ten "Boundary Fill"
    glutDisplayFunc(mydisplay); // Dang ky ham ve mydisplay
    glutMouseFunc(mouse); // Dang ky ham xu ly chuot
    init();  // Goi ham khoi tao
    glutMainLoop();  // Vong lap chinh cua GLUT de xu ly su kien
    return 0;
}

