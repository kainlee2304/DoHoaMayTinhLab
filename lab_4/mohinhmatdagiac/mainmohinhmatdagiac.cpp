#include <GL/glut.h> 
#include <vector> 
#include <cmath> 
#include <iostream> 

const int MAX = 100; 


struct Point3D {
    float x, y, z;
};


struct FaceType {
    int p1, p2, p3; 
};


struct PolygonModel {
    std::vector<Point3D> vertices; // Danh sach dinh (toa do)
    std::vector<FaceType> faces; // Danh sach mat (tam giac)
};

PolygonModel object; // Vat the 3D
float rotateX = 0.0f, rotateY = 0.0f; // Goc xoay quanh truc X va Y
float translateX = 0.0f, translateY = 0.0f, translateZ = -5.0f; // Vi tri chuyen doi vat the
float scale = 1.0f; // Bien ti le phong to thu nho
bool perspectiveProjection = true; // Bien kiem tra phep chieu (pho canh hoac song song)

// Ham khoi tao cac dinh va mat cho vat the
void initObject() {
    // Khoi tao cac dinh cua vat the 3D
    Point3D p1 = {0, 1, 0}; // Dinh tren
    Point3D p2 = {-1, -1, 1}; // Dinh ben trai phia truoc
    Point3D p3 = {1, -1, 1}; // Dinh ben phai phia truoc
    Point3D p4 = {0, -1, -1}; // Dinh phia sau
    

    object.vertices.push_back(p1);
    object.vertices.push_back(p2);
    object.vertices.push_back(p3);
    object.vertices.push_back(p4);

    // Khoi tao cac mat cua vat the
    FaceType f1 = {0, 1, 2}; // Mat tam giac noi giua dinh p1, p2, p3
    FaceType f2 = {0, 1, 3}; // Mat tam giac noi giua dinh p1, p2, p4
    FaceType f3 = {0, 2, 3}; // Mat tam giac noi giua dinh p1, p3, p4
    FaceType f4 = {1, 2, 3}; // Mat tam giac noi giua dinh p2, p3, p4

    object.faces.push_back(f1);
    object.faces.push_back(f2);
    object.faces.push_back(f3);
    object.faces.push_back(f4);
}

// Ham hien thi vat the
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh
// camera dat cach goc toa do 5 don vi theo huong duong truc z,nhin ve huong goc toa do 0,0,0 huong len doc theo truc y
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); // Dat vi tri camera de quan sat vat the

    // Thuc hien cac phep bien doi vat the (di chuyen, xoay, phong to/thu nho)
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateX, 1, 0, 0); // Xoay quanh truc X
    glRotatef(rotateY, 0, 1, 0); // Xoay quanh truc Y
    glScalef(scale, scale, scale); // Phong to/thu nho vat the


    // Ve cac mat cua vat the
    glColor3f(0.2f, 0.7f, 1.0f); // Mau xanh
    glBegin(GL_TRIANGLES); // Bat dau ve tam giac
    for (size_t i = 0; i < object.faces.size(); ++i) {
        const FaceType& face = object.faces[i];
        const Point3D& v1 = object.vertices[face.p1];
        const Point3D& v2 = object.vertices[face.p2];
        const Point3D& v3 = object.vertices[face.p3];
        glVertex3f(v1.x, v1.y, v1.z); // Ve dinh thu nhat cua tam giac
        glVertex3f(v2.x, v2.y, v2.z); // Ve dinh thu hai cua tam giac
        glVertex3f(v3.x, v3.y, v3.z); // Ve dinh thu ba cua tam giac
    }
    glEnd(); // Ket thuc ve tam giac

    
    glutSwapBuffers(); // Doi buffer de hien thi len man hinh
}

// Ham xu ly thay doi kich thuoc cua so
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Cai dat khu vuc ve
    glMatrixMode(GL_PROJECTION); // Chuyen sang che do phep chieu
    glLoadIdentity(); // Dat lai ma tran don vi
    if (perspectiveProjection) {
        gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f); // Phep chieu pho canh
    } else {
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
            std::cout << "Chuyen doi chieu: " << (perspectiveProjection ? "Phoi` canh" : "Song song") << std::endl;
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

    initObject(); // Khoi tao cac dinh va mat cua vat the

    glutDisplayFunc(display); // Gan ham hien thi
    glutReshapeFunc(reshape); // Gan ham xu ly thay doi kich thuoc cua so
    glutKeyboardFunc(keyboard); // Gan ham xu ly su kien nhan phim

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau

    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

