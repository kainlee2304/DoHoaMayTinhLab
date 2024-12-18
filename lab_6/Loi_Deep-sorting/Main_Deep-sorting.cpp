#include <GL/glut.h> // Thu vien GLUT de quan ly cua so, su kien va ve do hoa
#include <vector> // Thu vien vector de luu tru danh sach cac doi tuong
#include <algorithm> // Thu vien algorithm de su dung ham sap xep
#include <cmath> // Thu vien toan hoc cho cac phep tinh

// Goc xoay cua camera
float angleX = 30.0f; // Goc xoay theo truc X
float angleY = -45.0f; // Goc xoay theo truc Y

// Cau truc de luu tru thong tin doi tuong voi do sau
struct Object {
    float depth; // Do sau tu camera
    void (*draw)(); // Con tro ham ve doi tuong
};

// Danh sach cac doi tuong se ve
std::vector<Object> objects;

// Ham khoi tao OpenGL
void initGL() {
    glEnable(GL_DEPTH_TEST); // Kich hoat Depth Testing de khu mat khuat
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Mau nen trang
}

// Ham ve hinh tam giac
void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.4f, 0.8f); // Mau xanh lam cho tam giac
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

// Ham ve hinh vuong
void drawSquare() {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.8f, 0.2f); // Mau vang cho hinh vuong
    glVertex3f(-0.8f, 0.8f, -0.5f);
    glVertex3f(0.8f, 0.8f, -0.5f);
    glVertex3f(0.8f, -0.8f, -0.5f);
    glVertex3f(-0.8f, -0.8f, -0.5f);
    glEnd();
}

// Ham tinh toan do sau cho cac doi tuong
float calculateDepth(float zPosition) {
    return fabs(zPosition); // Tra ve gia tri tuyet doi cua z de lam do sau
}

// Ham so sanh de sap xep cac doi tuong theo do sau
bool compareDepth(const Object& a, const Object& b) {
    return a.depth > b.depth; // Sap xep tu xa den gan
}

// Ham ve va hien thi
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va buffer do sau
    glLoadIdentity(); // Reset ma tran

    // Di chuyen ra xa camera
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Xoay theo goc camera
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Cap nhat do sau cho cac doi tuong
    objects[0].depth = calculateDepth(0.0f); // Tam giac o z = 0
    objects[1].depth = calculateDepth(-0.5f); // Hinh vuong o z = -0.5

    // Sap xep cac doi tuong dua tren do sau (Deep Sorting)
    std::sort(objects.begin(), objects.end(), compareDepth);

    // Ve cac doi tuong theo thu tu da sap xep
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i].draw(); // Su dung chi so de truy cap doi tuong va goi ham ve
    }

    glutSwapBuffers(); // Hien thi noi dung da ve
}

// Ham xu ly phim de xoay hinh vuong va tam giac
void keyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        angleX -= 5.0f; // Xoay nguoc theo truc X
        break;
    case GLUT_KEY_DOWN:
        angleX += 5.0f; // Xoay thuan theo truc X
        break;
    case GLUT_KEY_LEFT:
        angleY -= 5.0f; // Xoay nguoc theo truc Y
        break;
    case GLUT_KEY_RIGHT:
        angleY += 5.0f; // Xoay thuan theo truc Y
        break;
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thay doi goc xoay
}

// Ham thay doi kich thuoc cua so
void reshape(int width, int height) {
    if (height == 0) height = 1; // Tranh chia cho 0
    float aspect = (float)width / height; // Ty le man hinh

    glViewport(0, 0, width, height); // Thiet lap viewport

    glMatrixMode(GL_PROJECTION); // Chuyen sang che do thiet lap goc nhin
    glLoadIdentity(); // Reset ma tran
    gluPerspective(45.0, aspect, 1.0, 100.0); // Thiet lap goc nhin

    glMatrixMode(GL_MODELVIEW); // Tro lai che do Model-View
}

// Ham chinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Chon che do hien thi
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("3D Objects with Deep Sorting"); // Tao cua so

    initGL(); // Khoi tao OpenGL

    // Them cac doi tuong vao danh sach va chi dinh ham ve tuong ung
    objects.push_back({ 0.0f, drawTriangle });
    objects.push_back({ -0.5f, drawSquare });

    glutDisplayFunc(display); // Ham hien thi
    glutReshapeFunc(reshape); // Ham thay doi kich thuoc cua so
    glutSpecialFunc(keyboard); // Gan ham xu ly phim mui ten

    glutMainLoop(); // Vong lap chinh
    return 0;
}

