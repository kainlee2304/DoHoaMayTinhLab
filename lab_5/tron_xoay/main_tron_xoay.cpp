#include <GL/glut.h> // Thu vien GLUT de tao cua so, quan ly su kien va do hoa
#include <cmath> // Thu vien cho cac ham toan hoc
#include <iostream> // Thu vien nhap xuat co ban
#include <iomanip> // Thu vien de can chinh hien thi

const float PI = 3.14159265358979323846; // Hang so PI

// Bien luu tru thong tin xoay, dich chuyen, va ti le cua vat the
float rotateX = 0.0f, rotateY = 0.0f;
float translateZ = -5.0f;
float scale = 1.0f;
float radius = 1.0f, height = 1.0f;
float delta_u = 0.1f, delta_v = 0.1f; // Do chi tiet cua mat tron xoay
int currentShape = 0; // 0: Sphere, 1: Ellipsoid, 2: Hyperboloid, 3: Toroid

// Ham ve hinh cau (Sphere) voi ban kinh R
void drawSphere(float R) {
    glBegin(GL_POINTS); // Ve bang cac diem
    for (float v = -PI / 2; v < PI / 2; v += delta_v) {
        for (float u = 0; u < 2 * PI; u += delta_u) {
            float x = R * cos(u) * cos(v); // Tinh toa do x
            float y = R * sin(u) * cos(v); // Tinh toa do y
            float z = R * sin(v); // Tinh toa do z
            glVertex3f(x, y, z); // Ve diem tai (x, y, z)
        }
    }
    glEnd();
}

// Ham ve hinh ellipsoid voi cac ban kinh a, b, c
void drawEllipsoid(float a, float b, float c) {
    glBegin(GL_POINTS);
    for (float v = -PI / 2; v < PI / 2; v += delta_v) {
        for (float u = 0; u < 2 * PI; u += delta_u) {
            float x = a * cos(u) * cos(v);
            float y = b * sin(u) * cos(v);
            float z = c * sin(v);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
}

// Ham ve hinh hyperboloid voi cac tham so a, b, c
void drawHyperboloid(float a, float b, float c) {
    glBegin(GL_POINTS);
    for (float v = -1; v <= 1; v += delta_v) {
        for (float u = 0; u < 2 * PI; u += delta_u) {
            float x = a * cosh(v) * cos(u);
            float y = b * cosh(v) * sin(u);
            float z = c * sinh(v);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
}

// Ham ve hinh toroid (hinh xuyen) voi ban kinh lon R va ban kinh nho r
void drawToroid(float R, float r) {
    glBegin(GL_POINTS);
    for (float v = 0; v < 2 * PI; v += delta_v) {
        for (float u = 0; u < 2 * PI; u += delta_u) {
            float x = (R + r * cos(v)) * cos(u);
            float y = (R + r * cos(v)) * sin(u);
            float z = r * sin(v);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
}

// Ham hien thi vat the len man hinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh

    // Thuc hien cac phep bien doi vat the (di chuyen, xoay, phong to/thu nho)
    glTranslatef(0.0f, 0.0f, translateZ);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Xoay quanh truc X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Xoay quanh truc Y
    glScalef(scale, scale, scale); // Phong to/thu nho vat the

    glColor3f(0.0f, 1.0f, 0.0f); // Mau xanh la

    // Ve hinh dang hien tai (Sphere, Ellipsoid, Hyperboloid, Toroid)
    switch (currentShape) {
        case 0: drawSphere(radius); break;
        case 1: drawEllipsoid(radius, radius * 0.75f, radius * 0.5f); break;
        case 2: drawHyperboloid(radius, radius, height); break;
        case 3: drawToroid(radius, radius * 0.3f); break;
    }

    glutSwapBuffers(); // Doi buffer de hien thi len man hinh
}

// Ham xu ly thay doi kich thuoc cua so
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
        case 'q': translateZ -= 0.5f; break; // Di chuyen gan lai
        case 'e': translateZ += 0.5f; break; // Di chuyen xa ra
        case '+': scale *= 1.1f; break; // Phong to vat the
        case '-': scale /= 1.1f; break; // Thu nho vat the
        case 'r': radius += 0.1f; break; // Tang ban kinh
        case 'f': radius -= 0.1f; break; // Giam ban kinh
        case 'h': height += 0.1f; break; // Tang chieu cao (chi anh huong Hyperboloid)
        case 'g': height -= 0.1f; break; // Giam chieu cao (chi anh huong Hyperboloid)
        case 'i': delta_u *= 1.1f; delta_v *= 1.1f; break; // Giam do chi tiet (tang khoang cach giua cac diem ve)
        case 'k': delta_u /= 1.1f; delta_v /= 1.1f; break; // Tang do chi tiet (giam khoang cach giua cac diem ve)
        case ' ': currentShape = (currentShape + 1) % 4; break; // Chuyen doi giua cac hinh dang 
        case 27: exit(0); break; // Phim Esc thoat chuong trinh
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thuc hien thay doi
}

// Ham hien thi huong dan chi tiet su dung chuong trinh
void printDetailedInstructions() {
    std::cout << "\n============= HUONG DAN SU DUNG CHI TIET =============\n";
    std::cout << "Chuyen doi giua cac hinh:\n";
    std::cout << "  Nhan phim SPACE de chuyen doi giua cac hinh theo thu tu:\n";
    std::cout << "  Sphere (hinh cau) -> Ellipsoid (hinh elip) ->\n";
    std::cout << "  Hyperboloid (hinh hyperbol) -> Toroid (hinh xuyen) -> quay lai Sphere\n\n";
    
    std::cout << "Dieu khien goc nhin:\n";
    std::cout << "  w/s: Xoay quanh truc X (len/xuong)\n";
    std::cout << "  a/d: Xoay quanh truc Y (trai/phai)\n";
    std::cout << "  q/e: Di chuyen gan/xa\n";
    std::cout << "  +/-: Phong to/thu nho\n\n";
    
    std::cout << "Dieu chinh hinh dang:\n";
    std::cout << "  r/f: Tang/giam ban kinh\n";
    std::cout << "  h/g: Tang/giam chieu cao (chi anh huong den Hyperboloid)\n";
    std::cout << "  i/k: Giam/tang do chi tiet (so luong diem ve)\n\n";
    
    
    std::cout << "  Esc: Thoat chuong trinh\n";
    std::cout << "=====================================================\n";
}

// Ham hien thi thong tin trang thai cua vat the
void printStatus() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Hinh dang: ";
    switch (currentShape) {
        case 0: std::cout << "Sphere     "; break;
        case 1: std::cout << "Ellipsoid  "; break;
        case 2: std::cout << "Hyperboloid"; break;
        case 3: std::cout << "Toroid     "; break;
    }
    std::cout << " | Ban kinh: " << radius << " | Chieu cao: " << height 
              << " | Do chi tiet: " << 1 / delta_u << "\r" << std::flush;
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
    glutCreateWindow("Chuong trinh ve cac mat tron xoay 3D"); // Tao cua so moi

    // Gan cac ham xu ly su kien
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau
    glPointSize(2.0f); // Dat kich thuoc diem ve

    printDetailedInstructions(); // In huong dan su dung chi tiet

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

