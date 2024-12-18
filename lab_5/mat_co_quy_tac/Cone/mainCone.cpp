#include <GL/glut.h> 
#include <cmath>  
#include <iostream>  
#include <iomanip>  

const float PI = 3.14159265358979323846;  

 
float rotateX = 0.0f, rotateY = 0.0f; // Bien luu goc xoay quanh truc X va Y
float translateZ = -5.0f; // Bien luu vi tri dich chuyen theo truc Z
float scale = 1.0f; // Bien luu ti le phong to/thu nho
float radius = 1.0f, height = 2.0f; // Ban kinh day va chieu cao cua hinh non
int slices = 30, stacks = 30; // So lat ngang va lat doc cua hinh non

// Ham ve hinh non (cone) voi ban kinh day, chieu cao, so lat ngang va so lat doc
void drawCone(float radius, float height, int slices, int stacks) {
    float delta_u = 2 * PI / slices; // Khoang cach giua cac lat ngang
    float delta_v = 1.0f / stacks; // Khoang cach giua cac lat doc

    // Ve than hinh non:dai tam giac doc theo chieu cao, di quanh truc cua hinh non.
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        float u = i * delta_u; // Tinh goc u
        for (int j = 0; j <= stacks; ++j) {
            float v = j * delta_v; // Tinh v tuong ung
            float x = v * radius * cos(u); // Tinh toa do x cua diem
            float y = v * radius * sin(u); // Tinh toa do y cua diem
            float z = v * height; // Tinh toa do z cua diem
            //i[0-1]red,j[0-1]xanh la ,xanh duong
            glColor3f((float)i/slices, (float)j/stacks, 1.0f); // Mau gradient
            glVertex3f(x, y, z); // Ve diem tai (x, y, z)
            
            // Ve diem ke tiep tren than hinh non
            x = v * radius * cos(u + delta_u);
            y = v * radius * sin(u + delta_u);
            glVertex3f(x, y, z);
        }
    }
    glEnd();

    // Ve day hinh non
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f); // Mau xanh cho day hinh non
    glVertex3f(0.0f, 0.0f, 0.0f); // Diem o tam day
    for (int i = 0; i <= slices; ++i) {
        float u = i * delta_u; // Tinh goc u
        glVertex3f(radius * cos(u), radius * sin(u), 0.0f); // Ve diem tren day hinh non
    }
    glEnd();
}

// Ham hien thi hinh non len man hinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh

    // Thuc hien cac phep bien doi vat the (di chuyen, xoay, phong to/thu nho)
    glTranslatef(0.0f, 0.0f, translateZ);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Xoay quanh truc X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Xoay quanh truc Y
    glScalef(scale, scale, scale); // Phong to/thu nho vat the

    drawCone(radius, height, slices, stacks); // Ve hinh non

    glutSwapBuffers(); // Doi buffer de hien thi len man hinh
}

// Ham thay doi kich thuoc cua so
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Cai dat khu vuc ve
    glMatrixMode(GL_PROJECTION); // Chuyen sang che do phep chieu
    glLoadIdentity(); // Dat lai ma tran don vi
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f); // Phep chieu pho canh
    glMatrixMode(GL_MODELVIEW); // Quay lai che do model view
}

// Ham xu ly su kien nhan phim tu ban phim
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotateX -= 5.0f; break; // Xoay quanh truc X len tren
        case 's': rotateX += 5.0f; break; // Xoay quanh truc X xuong duoi
        case 'a': rotateY -= 5.0f; break; // Xoay quanh truc Y trai
        case 'd': rotateY += 5.0f; break; // Xoay quanh truc Y phai
        case 'q': translateZ -= 0.5f; break; // Di chuyen gan lai theo truc Z
        case 'e': translateZ += 0.5f; break; // Di chuyen xa ra theo truc Z
        case '+': scale *= 1.1f; break; // Phong to vat the
        case '-': scale /= 1.1f; break; // Thu nho vat the
        case 'r': radius += 0.1f; break; // Tang ban kinh day hinh non
        case 'f': radius -= 0.1f; break; // Giam ban kinh day hinh non
        case 'h': height += 0.1f; break; // Tang chieu cao hinh non
        case 'g': height -= 0.1f; break; // Giam chieu cao hinh non
        case 'i': slices = std::max(3, slices - 1); break; // Giam so lat ngang (toi thieu la 3)
        case 'k': slices++; break; // Tang so lat ngang
        
        case 27: exit(0); break; // Phim Esc thoat chuong trinh
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thuc hien thay doi
}

// Ham hien thi huong dan su dung chuong trinh
void printInstructions() {
    std::cout << "\n============= HUONG DAN SU DUNG =============\n";
    std::cout << "| Phim | Chuc nang                           |\n";
    std::cout << "|------|-------------------------------------|\n";
    std::cout << "| w/s  | Xoay quanh truc X                   |\n";
    std::cout << "| a/d  | Xoay quanh truc Y                   |\n";
    std::cout << "| q/e  | Di chuyen gan/xa                    |\n";
    std::cout << "| +/-  | Phong to/thu nho                    |\n";
    std::cout << "| r/f  | Tang/giam ban kinh day              |\n";
    std::cout << "| h/g  | Tang/giam chieu cao                 |\n";
    std::cout << "| i/k  | Giam/tang so luong lat ngang        |\n";
    std::cout << "| Esc  | Thoat chuong trinh                  |\n";                    
    std::cout << "=============================================\n";
}

// Ham hien thi thong tin trang thai cua vat the
void printStatus() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Ban kinh day: " << radius << " | Chieu cao: " << height 
              << " | Slices: " << slices << " | Stacks: " << stacks << "\r" << std::flush;
}

// Ham goi trong luc chuong trinh ranh de cap nhat thong tin trang thai
void idle() {
    printStatus();
    glutPostRedisplay();
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Chon che do hien thi
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("Chuong trinh ve hinh non 3D"); // Tao cua so moi

    // Gan cac ham xu ly su kien
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau
    glEnable(GL_CULL_FACE); // Bat che mat sau cua hinh de tang hieu nang
    glCullFace(GL_BACK); // Chi ve mat truoc cua hinh

    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

