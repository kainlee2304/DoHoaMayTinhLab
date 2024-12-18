#include <GL/glut.h> // Thu vien GLUT de tao cua so, quan ly su kien va do hoa
#include <cmath> // Thu vien cho cac ham toan hoc
#include <iostream> // Thu vien nhap xuat co ban
#include <iomanip> // Thu vien can chinh hien thi

const float PI = 3.14159265358979323846; // Hang so PI

// Bien luu tru thong tin ve xoay, dich chuyen, ti le phong to/thu nho
float rotateX = 0.0f, rotateY = 0.0f; // Bien luu goc xoay quanh truc X va Y
float translateZ = -5.0f; // Bien luu vi tri dich chuyen theo truc Z
float scale = 1.0f; // Bien luu ti le phong to/thu nho
float radius = 1.0f, height = 2.0f; // Ban kinh va chieu cao cua hinh tru
float delta_u = 0.06f, delta_v = 0.03f; // Do chi tiet cua hinh tru theo cac truc u va v

// Ham ve hinh tru (cylinder) voi ban kinh R va chieu cao h
void drawCylinder(float R, float h) {
    glBegin(GL_POINTS); // Ve bang cac diem
    for (float u = 0; u < 2 * PI; u += delta_u) {
        for (float v = 0; v < 1; v += delta_v) {
            float x = R * cos(u); // Tinh toa do x cua diem
            float y = R * sin(u); // Tinh toa do y cua diem
            float z = v * h; // Tinh toa do z cua diem
            glColor3f(1.0f, 1.0f, 1.0f); // Mau trang cho hinh tru
            glVertex3f(x, y, z); // Ve diem tai (x, y, z)
        }
    }
    glEnd();
}

// Ham hien thi hinh tru len man hinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh

    // Thuc hien cac phep bien doi vat the (di chuyen, xoay, phong to/thu nho)
    glTranslatef(0.0f, 0.0f, translateZ);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Xoay quanh truc X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Xoay quanh truc Y
    glScalef(scale, scale, scale); // Phong to/thu nho vat the

    
    drawCylinder(radius, height); // Ve hinh tru

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
        case 'a': rotateY -= 5.0f; break; // Xoay quanh truc Y sang trai
        case 'd': rotateY += 5.0f; break; // Xoay quanh truc Y sang phai
        case 'q': translateZ -= 0.5f; break; // Di chuyen gan lai theo truc Z
        case 'e': translateZ += 0.5f; break; // Di chuyen xa ra theo truc Z
        case '+': scale *= 1.1f; break; // Phong to vat the
        case '-': scale /= 1.1f; break; // Thu nho vat the
        case 'r': radius += 0.1f; break; // Tang ban kinh cua hinh tru
        case 'f': radius -= 0.1f; break; // Giam ban kinh cua hinh tru
        case 'h': height += 0.1f; break; // Tang chieu cao cua hinh tru
        case 'g': height -= 0.1f; break; // Giam chieu cao cua hinh tru
        case '[': delta_u *= 1.1f; break; // Giam do chi tiet theo chieu u (tang khoang cach giua cac diem ve)
        case ']': delta_u /= 1.1f; break; // Tang do chi tiet theo chieu u (giam khoang cach giua cac diem ve)
        case '{': delta_v *= 1.1f; break; // Giam do chi tiet theo chieu v
        case '}': delta_v /= 1.1f; break; // Tang do chi tiet theo chieu v
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
    std::cout << "| r/f  | Tang/giam ban kinh                  |\n";
    std::cout << "| h/g  | Tang/giam chieu cao                 |\n";
    std::cout << "| [/]  | Giam/tang do chi tiet theo chieu u  |\n";
    std::cout << "| {/}  | Giam/tang do chi tiet theo chieu v  |\n";
    std::cout << "| Esc  | Thoat chuong trinh                  |\n";
    std::cout << "=============================================\n";
}

// Ham hien thi thong tin trang thai cua vat the
void printStatus() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Ban kinh: " << radius << " | Chieu cao: " << height 
              << " | Delta U: " << delta_u << " | Delta V: " << delta_v << "\r" << std::flush;
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
    glutCreateWindow("Chuong trinh ve hinh tru 3D"); // Tao cua so moi

    // Gan cac ham xu ly su kien
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau
    glPointSize(2.0f); // Dat kich thuoc diem ve

    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

