#include <GL/glut.h> 
#include <vector> 
#include <cmath> 
#include <iostream> 

const int MAX = 100; // Hang so, gia tri toi da

// Cau truc luu toa do diem 3D
struct Point3D {
    float x, y, z; // Toa do x, y, z
};

// Cau truc EdgeType de luu thong tin ve canh noi giua cac dinh
struct EdgeType {
    int beginP, endP; // Chi so cua hai dinh noi voi nhau
};

// Cau truc WireFrame de luu thong tin ve khung day cua vat the
struct WireFrame {
    std::vector<Point3D> vertices; // Danh sach dinh
    std::vector<EdgeType> edges; // Danh sach canh
};

WireFrame object; // Vat the 3D
float rotateX = 0.0f, rotateY = 0.0f; // Bien luu goc xoay quanh truc X va Y
float translateX = 0.0f, translateY = 0.0f, translateZ = -5.0f; // Bien luu vi tri di chuyen vat the
float scale = 1.0f; // Bien ti le phong to thu nho
bool perspectiveProjection = true; // Chon phep chieu phoi canh hoac song song


// Ham khoi tao cac dinh va canh cua vat the
void initObject() {
    // Khoi tao cac dinh cua hinh tam giac 3D
    Point3D p1 = {0, 1, 0}; // Dinh 1 o dinh tam giac
    Point3D p2 = {-1, -1, 1}; // Dinh 2 ben trai phia duoi
    Point3D p3 = {1, -1, 1}; // Dinh 3 ben phai phia duoi
    Point3D p4 = {0, -1, -1}; // Dinh 4 ben phia sau
    

    object.vertices.push_back(p1);
    object.vertices.push_back(p2);
    object.vertices.push_back(p3);
    object.vertices.push_back(p4);

    // Khoi tao cac canh
    EdgeType e1 = {0, 1}; // Canh noi dinh 1 va 2
    EdgeType e2 = {1, 2}; // Canh noi dinh 2 va 3
    EdgeType e3 = {2, 0}; // Canh noi dinh 3 va 1
    EdgeType e4 = {0, 3}; // Canh noi dinh 1 va 4
    EdgeType e5 = {1, 3}; // Canh noi dinh 2 va 4
    EdgeType e6 = {2, 3}; // Canh noi dinh 3 va 4

    object.edges.push_back(e1);
    object.edges.push_back(e2);
    object.edges.push_back(e3);
    object.edges.push_back(e4);
    object.edges.push_back(e5);
    object.edges.push_back(e6);
}

// Ham hien thi vat the tren man hinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa bo dem man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai

    gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0); // Dat camera quan sat tu vi tri (0, 0, 5) huong ve goc toa do

    // Thay doi vi tri, goc xoay va ti le vat the
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    glScalef(scale, scale, scale);

    // Ve cac canh cua vat the
    glBegin(GL_LINES);
    for (size_t i = 0; i < object.edges.size(); ++i) {
        const EdgeType& edge = object.edges[i];
        const Point3D& v1 = object.vertices[edge.beginP];
        const Point3D& v2 = object.vertices[edge.endP];
        glVertex3f(v1.x, v1.y, v1.z); // Diem bat dau cua canh
        glVertex3f(v2.x, v2.y, v2.z); // Diem ket thuc cua canh
    }
    glEnd();

    glutSwapBuffers(); // Doi buffer de hien thi len man hinh
}

// Ham xu ly thay doi kich thuoc cua so:w,h:dai,rong
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Cai dat khu vuc ve
    glMatrixMode(GL_PROJECTION); // Chuyen sang che do phep chieu
    glLoadIdentity(); // Dat lai ma tran don vi
    if (perspectiveProjection) {
    	//goc nhin,ty le khung hinh,khoang cach tam nhin gan nhat,khoang cach tam nhin xa nhat
        gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f); // Phep chieu phoi canh
    } else {
    	//gioi han trai, phai, tren,duoi, truoc,sau
        glOrtho(-3, 3, -3 * h / w, 3 * h / w, -100, 100); // Phep chieu song song
    }
    glMatrixMode(GL_MODELVIEW); // Quay lai che do model view
}

// Ham hien thi huong dan su dung
void printInstructions() {
    std::cout << "\n===== Huong dan su dung =====\n";
    std::cout << "Thay doi phep chieu:\n";
    std::cout << "  p: Chuyen doi giua phep chieu pho canh va song song\n";
    std::cout << "Thay doi goc quan sat (xoay vat the):\n";
    std::cout << "  r/f: Xoay quanh truc X\n";
    std::cout << "  t/g: Xoay quanh truc Y\n";
    std::cout << "Thay doi vi tri quan sat (diem nhin):\n";
    std::cout << "  w/s: Di chuyen len/xuong\n";
    std::cout << "  a/d: Di chuyen trai/phai\n";
    std::cout << "  q/e: Di chuyen gan/xa\n";
    std::cout << "Phong to, thu nho vat the:\n";
    std::cout << "  +: Phong to\n";
    std::cout << "  -: Thu nho\n";
    std::cout << "Khac:\n";
    std::cout << "  h: Hien thi lai huong dan nay\n";
    std::cout << "  Esc: Thoat chuong trinh\n";
    std::cout << "==============================\n";
}

// Ham xu ly su kien nhan phim tu ban phim
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': translateY += 0.1f; break; // Di chuyen len
        case 's': translateY -= 0.1f; break; // Di chuyen xuong
        case 'a': translateX -= 0.1f; break; // Di chuyen sang trai
        case 'd': translateX += 0.1f; break; // Di chuyen sang phai
        case 'q': translateZ -= 0.1f; break; // Di chuyen gan lai
        case 'e': translateZ += 0.1f; break; // Di chuyen xa ra
        case 'r': rotateX += 5.0f; break; // Xoay quanh truc X theo chieu kim dong ho
        case 'f': rotateX -= 5.0f; break; // Xoay quanh truc X nguoc chieu kim dong ho
        case 't': rotateY += 5.0f; break; // Xoay quanh truc Y theo chieu kim dong ho
        case 'g': rotateY -= 5.0f; break; // Xoay quanh truc Y nguoc chieu kim dong ho
        case '+': scale *= 1.1f; break; // Phong to vat the
        case '-': scale /= 1.1f; break; // Thu nho vat the
        
        case 'p':
            perspectiveProjection = !perspectiveProjection; // Chuyen giua phep chieu pho canh va song song
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            std::cout << "Chuyen doi chieu: " << (perspectiveProjection ? "Phoi canh" : "Song song") << std::endl;
            break;
        case 'h':
            printInstructions(); // In huong dan su dung
            break;
        case 27: // Phim Esc
            exit(0); // Thoat chuong trinh
            break;
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thuc hien thay doi
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Chon che do hien thi
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("Chuong trinh quan sat hinh tam giac 3D"); // Tao cua so moi

    initObject(); // Khoi tao cac dinh va canh cua vat the

    glutDisplayFunc(display); // Gan ham hien thi
    glutReshapeFunc(reshape); // Gan ham xu ly thay doi kich thuoc cua so
    glutKeyboardFunc(keyboard); // Gan ham xu ly su kien nhan phim

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau

    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

