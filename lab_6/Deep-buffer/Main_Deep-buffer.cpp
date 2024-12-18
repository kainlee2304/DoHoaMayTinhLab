#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

// Goc xoay theo truc X va Y
float rotateX = 0.0f, rotateY = 0.0f;
// Vi tri zoom theo truc Z
float translateZ = -10.0f;
// Bien kiem soat Z-buffer
bool enableZBuffer = true;

// Cau truc mau sac
struct Color {
    float r, g, b;
    Color(float r = 1.0f, float g = 1.0f, float b = 1.0f) : r(r), g(g), b(b) {}
};

// Ham ve hinh lap phuong voi kich thuoc va mau sac cho truoc
void drawCube(float size, const Color& color) {
    glColor3f(color.r, color.g, color.b); // Dat mau sac cho hinh lap phuong
    glutSolidCube(size); // Ve hinh lap phuong
}

// Ham ve toan bo canh
void drawScene() {
    // Ve hinh lap phuong o giua
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Dich chuyen hinh lap phuong toi vi tri 0,0,0
    drawCube(2.0f, Color(1.0f, 0.0f, 0.0f)); // Hinh lap phuong mau do
    glPopMatrix();
    

    // Ve hinh lap phuong phia truoc ben trai
    glPushMatrix();
    glTranslatef(-1.5f, -1.5f, 2.0f); // Dich chuyen hinh lap phuong
    drawCube(1.5f, Color(0.0f, 1.0f, 0.0f)); // Hinh lap phuong mau xanh la
    glPopMatrix();

    // Ve hinh lap phuong phia sau ben phai
    glPushMatrix();//luu trang thai hien tai
    glTranslatef(1.5f, 1.5f, -2.0f); // Dich chuyen hinh lap phuong
    drawCube(1.5f, Color(0.0f, 0.0f, 1.0f)); // Hinh lap phuong mau xanh duong
    glPopMatrix();//khoi phuc trang thai ban dau
}

// Ham hien thi
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa bo nho ve va buffer do sau
    glLoadIdentity(); // Tai lai ma tran don vi

    // Dich chuyen canh theo truc Z
    glTranslatef(0.0f, 0.0f, translateZ);
    // Xoay canh theo truc X va Y
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    // Ve canh
    drawScene();

    glutSwapBuffers(); // Doi khung hinh de hien thi
}

// Ham thay doi kich thuoc cua so
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Cai dat viewport
    glMatrixMode(GL_PROJECTION); // Chuyen sang ma tran phep chieu
    glLoadIdentity(); // Tai lai ma tran don vi
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f); // Cai dat phep chieu phoi canh
    glMatrixMode(GL_MODELVIEW); // Quay lai ma tran model-view
}

// Ham xu ly su kien ban phim
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotateX += 5.0f; break; // Xoay theo truc X len tren
        case 's': rotateX -= 5.0f; break; // Xoay theo truc X xuong duoi
        case 'a': rotateY -= 5.0f; break; // Xoay theo truc Y sang trai
        case 'd': rotateY += 5.0f; break; // Xoay theo truc Y sang phai
        case 'q': translateZ -= 0.5f; break; // Di chuyen canh ra xa
        case 'e': translateZ += 0.5f; break; // Di chuyen canh lai gan
        
        case 'z': // Bat/tat Z-buffer
            enableZBuffer = !enableZBuffer;
            if (enableZBuffer) {
                glEnable(GL_DEPTH_TEST); // Bat Z-buffer
                std::cout << "Z-buffer enabled" << std::endl;
            } else {
                glDisable(GL_DEPTH_TEST); // Tat Z-buffer
                std::cout << "Z-buffer disabled" << std::endl;
            }
            break;
        case 27: exit(0); break; // Thoat chuong trinh khi an phim ESC
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thay doi
}

// Ham hien thi huong dan su dung
void printInstructions() {
    std::cout << "\n===== HUONG DAN SU DUNG =====\n";
    std::cout << "- Phim w/s: Xoay canh theo truc X\n";
    std::cout << "- Phim a/d: Xoay canh theo truc Y\n";
    std::cout << "- Phim q/e: Di chuyen gan/xa\n";
    std::cout << "- Phim z: Bat/tat Z-buffer\n";
    std::cout << "- Phim ESC: Thoat chuong trinh\n";
    std::cout << "==============================\n";
}

// Ham main
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Che do hien thi doi buffer, RGB, depth test
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("Minh hoa thuat toan Z-buffer"); // Tao cua so voi ten

    glutDisplayFunc(display); // Ham hien thi
    glutReshapeFunc(reshape); // Ham thay doi kich thuoc cua so
    glutKeyboardFunc(keyboard); // Ham xu ly su kien ban phim

    glEnable(GL_DEPTH_TEST); // Kich hoat Z-buffer

    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Vong lap chinh cua GLUT
    return 0;
}

