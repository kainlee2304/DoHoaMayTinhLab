#include <GL/glut.h> // Thu vien GLUT de tao cua so, quan ly su kien va do hoa
#include <vector> // Thu vien vector de lam viec voi danh sach dong
#include <cmath> // Thu vien cho cac ham toan hoc
#include <iostream> // Thu vien nhap xuat co ban

// Cac bien luu tru thong tin ve xoay, dich chuyen va che do Back-face culling
float rotateX = 0.0f, rotateY = 0.0f; // Goc xoay quanh truc X va Y
float translateZ = -5.0f; // Vi tri dich chuyen theo truc Z
bool enableBackfaceCulling = true; // Bien kiem tra che do Back-face culling

// Cau truc dinh nghia mot dinh (Vertex) voi toa do x, y, z
struct Vertex {
    float x, y, z;
    Vertex(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

// Cau truc dinh nghia mot mat (Face) voi ba dinh
struct Face {
    int v1, v2, v3;
    Face(int v1 = 0, int v2 = 0, int v3 = 0) : v1(v1), v2(v2), v3(v3) {}
};

std::vector<Vertex> vertices; // Danh sach cac dinh cua lap phuong
std::vector<Face> faces; // Danh sach cac mat cua lap phuong

// Ham khoi tao cac dinh va mat cua hinh lap phuong
void initVerticesAndFaces() {
    // Khoi tao cac dinh
    vertices.push_back(Vertex(-1, -1, -1));
    vertices.push_back(Vertex(1, -1, -1));
    vertices.push_back(Vertex(1, 1, -1));
    vertices.push_back(Vertex(-1, 1, -1));
    vertices.push_back(Vertex(-1, -1, 1));
    vertices.push_back(Vertex(1, -1, 1));
    vertices.push_back(Vertex(1, 1, 1));
    vertices.push_back(Vertex(-1, 1, 1));
    

    // Khoi tao cac mat
    faces.push_back(Face(0, 1, 2));
    faces.push_back(Face(0, 2, 3));
    faces.push_back(Face(4, 5, 6));
    faces.push_back(Face(4, 6, 7));
    faces.push_back(Face(0, 4, 7));
    faces.push_back(Face(0, 7, 3));
    faces.push_back(Face(1, 5, 6));
    faces.push_back(Face(1, 6, 2));
    faces.push_back(Face(3, 2, 6));
    faces.push_back(Face(3, 6, 7));
    faces.push_back(Face(0, 1, 5));
    faces.push_back(Face(0, 5, 4));
}

// Ham kiem tra xem mat co la Back-face (mat sau) khong
bool isBackFace(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
    // Tinh vector phap tuyen cua mat= tich cheo hai vecto tren mat
    float nx = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
    float ny = (v2.z - v1.z) * (v3.x - v1.x) - (v2.x - v1.x) * (v3.z - v1.z);
    float nz = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    
    // Don gian hoa: gia su camera o vi tri (0, 0, 1) nhin theo huong -z
    return nz < 0; // Mat se la Back-face neu vector phap tuyen co huong am theo truc z
}

// Ham ve hinh lap phuong
void drawCube() {
    for (size_t i = 0; i < faces.size(); ++i) {
        const Face& face = faces[i];
        const Vertex& v1 = vertices[face.v1];
        const Vertex& v2 = vertices[face.v2];
        const Vertex& v3 = vertices[face.v3];
        
        // Chi ve mat neu Back-face culling tat hoac mat khong la Back-face
        if (!enableBackfaceCulling || !isBackFace(v1, v2, v3)) {
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); // Mau do cho dinh thu nhat
            glVertex3f(v1.x, v1.y, v1.z);
            glColor3f(0.0f, 1.0f, 0.0f); // Mau xanh la cho dinh thu hai
            glVertex3f(v2.x, v2.y, v2.z);
            glColor3f(0.0f, 0.0f, 1.0f); // Mau xanh duong cho dinh thu ba
            glVertex3f(v3.x, v3.y, v3.z);
            glEnd();
        }
    }
}

// Ham hien thi chuong trinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh

    // Thuc hien cac phep bien doi vat the (di chuyen, xoay)
    glTranslatef(0.0f, 0.0f, translateZ);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Xoay quanh truc X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Xoay quanh truc Y

    drawCube(); // Ve hinh lap phuong

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
        case 'q': translateZ -= 0.5f; break; // Di chuyen gan lai theo truc Z
        case 'e': translateZ += 0.5f; break; // Di chuyen xa ra theo truc Z
        case 'b': 
            enableBackfaceCulling = !enableBackfaceCulling; // Bat/tat che do Back-face culling
            std::cout << (enableBackfaceCulling ? "Back-face culling enabled" : "Back-face culling disabled") << std::endl;
            break;
        case 27: exit(0); break; // Phim ESC thoat chuong trinh
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thuc hien thay doi
}

// Ham in huong dan su dung chuong trinh
void printInstructions() {
    std::cout << "\n===== HUONG DAN SU DUNG =====\n";
    std::cout << "- Phim w/s: Xoay hinh lap phuong theo truc X\n";
    std::cout << "- Phim a/d: Xoay hinh lap phuong theo truc Y\n";
    std::cout << "- Phim q/e: Di chuyen gan/xa\n";
    std::cout << "- Phim b: Bat/tat thuat toan Back-face culling\n";
    std::cout << "- Phim ESC: Thoat chuong trinh\n";
    std::cout << "==============================\n";
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Chon che do hien thi
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("Minh hoa thuat toan Back-face"); // Tao cua so moi

    // Gan cac ham xu ly su kien
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau

    initVerticesAndFaces(); // Khoi tao cac dinh va mat cho hinh lap phuong
    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

