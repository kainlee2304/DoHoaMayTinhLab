#include <GL/glut.h> // Thu vien GLUT de tao cua so, quan ly su kien va do hoa
#include <cmath> // Thu vien cho cac ham toan hoc
#include <iostream> // Thu vien nhap xuat co ban

// Cac bien luu tru thong tin ve xoay, vi tri nguon sang, va che do to bong
float rotateX = 0.0f, rotateY = 0.0f; // Goc xoay quanh truc X va Y
float lightX = 0.0f, lightY = 5.0f, lightZ = 5.0f; // Vi tri cua nguon sang
bool useGouraudShading = true; // Su dung to bong Gouraud (true: Gouraud, false: Flat)

// Ham cai dat thuoc tinh cua nguon sang
void setupLighting() {
    GLfloat light_position[] = { lightX, lightY, lightZ, 1.0f }; // Vi tri nguon sang
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Anh sang xung quanh
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Anh sang khuyet tan
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Anh sang phan chieu

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHT0); // Kich hoat nguon sang 0
}

// Ham cai dat thuoc tinh cua vat lieu
void setupMaterial() {
    GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Anh sang xung quanh cua vat lieu
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Anh sang khuyet tan cua vat lieu
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Anh sang phan chieu cua vat lieu
    GLfloat mat_shininess[] = { 50.0f }; // Do sang bong cua vat lieu

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Ham hien thi chuong trinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh

    // Cai dat vi tri nhin
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    // Xoay doi tuong theo goc xoay hien tai
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    // Cai dat thuoc tinh cua anh sang va vat lieu
    setupLighting();
    setupMaterial();

    // Lua chon che do to bong
    if (useGouraudShading) {
        glShadeModel(GL_SMOOTH); // To bong theo che do Gouraud
    } else {
        glShadeModel(GL_FLAT); // To bong theo che do Flat
    }

    // Ve hinh cau voi 50 slices va 50 stacks
    glutSolidSphere(1.0, 50, 50);

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

// Ham xu ly su kien ban phim
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotateX += 5.0f; break; // Xoay quanh truc X theo chieu duong
        case 's': rotateX -= 5.0f; break; // Xoay quanh truc X theo chieu am
        case 'a': rotateY -= 5.0f; break; // Xoay quanh truc Y theo chieu am
        case 'd': rotateY += 5.0f; break; // Xoay quanh truc Y theo chieu duong
        case 'i': lightY += 0.5f; break; // Di chuyen nguon sang len
        case 'k': lightY -= 0.5f; break; // Di chuyen nguon sang xuong
        case 'j': lightX -= 0.5f; break; // Di chuyen nguon sang trai
        case 'l': lightX += 0.5f; break; // Di chuyen nguon sang phai
        case 'u': lightZ -= 0.5f; break; // Di chuyen nguon sang gan hon
        case 'o': lightZ += 0.5f; break; // Di chuyen nguon sang xa hon
        case 'g':
            useGouraudShading = !useGouraudShading; // Chuyen doi giua to bong Gouraud va Flat
            std::cout << (useGouraudShading ? "Gouraud shading enabled" : "Flat shading enabled") << std::endl;
            break;
        case 27: exit(0); break; // Phim ESC thoat chuong trinh
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thuc hien thay doi
}

// Ham in huong dan su dung chuong trinh
void printInstructions() {
    std::cout << "\n===== HUONG DAN SU DUNG =====\n";
    std::cout << "- Phim w/s: Xoay hinh cau theo truc X\n";
    std::cout << "- Phim a/d: Xoay hinh cau theo truc Y\n";
    std::cout << "- Phim i/k: Di chuyen nguon sang len/xuong\n";
    std::cout << "- Phim j/l: Di chuyen nguon sang trai/phai\n";
    std::cout << "- Phim u/o: Di chuyen nguon sang gan/xa\n";
    std::cout << "- Phim g: Chuyen doi giua to bong Gouraud va to bong phang\n";
    std::cout << "- Phim ESC: Thoat chuong trinh\n";
    std::cout << "==============================\n";
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Chon che do hien thi
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("Minh hoa to bong noi suy Gouraud"); // Tao cua so moi

    // Gan cac ham xu ly su kien
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau
    glEnable(GL_LIGHTING); // Kich hoat he thong anh sang

    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

