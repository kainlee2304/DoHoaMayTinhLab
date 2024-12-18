#include <GL/glut.h> // Thu vien GLUT de tao cua so, quan ly su kien va do hoa
#include <vector> // Thu vien vector de lam viec voi danh sach dong
#include <cmath> // Thu vien cho cac ham toan hoc
#include <iostream> // Thu vien nhap xuat co ban

#ifndef M_PI
#define M_PI 3.14159265358979323846 // Dinh nghia hang so PI neu chua co
#endif

const int N = 4; // So diem kiem soat trong moi chieu
const int GRID_SIZE = 20; // So luoi de ve mat cong Bezier

// Cau truc de luu toa do 3D cua cac diem
struct Point3D {
    float x, y, z; // Toa do x, y, z
    Point3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {} // Ham khoi tao co gia tri mac dinh
};

// Danh sach diem kiem soat cho mat cong Bezier
std::vector<std::vector<Point3D>> controlPoints(N, std::vector<Point3D>(N));
float rotateX = 0.0f, rotateY = 0.0f; // Bien luu goc xoay theo truc X va Y
float translateZ = -5.0f; // Bien dich chuyen vat the theo truc Z
int selectedI = -1, selectedJ = -1; // Chi so cua diem kiem soat duoc chon

// Ham tinh giai thua
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Ham tinh to hop Bernstein
float bernstein(float t, int n, int i) {
    return std::pow(t, i) * std::pow(1 - t, n - i) * factorial(n) / (factorial(i) * factorial(n - i));
}

// Ham tinh toa do cua mot diem tren mat cong Bezier
Point3D bezierSurface(float u, float v) {
    Point3D result;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float b = bernstein(u, N - 1, i) * bernstein(v, N - 1, j); // Tinh gia tri Bernstein
            result.x += controlPoints[i][j].x * b; // Tinh toa do x cua diem tren mat cong
            result.y += controlPoints[i][j].y * b; // Tinh toa do y cua diem tren mat cong
            result.z += controlPoints[i][j].z * b; // Tinh toa do z cua diem tren mat cong
        }
    }
    return result;
}

// Ham ve mat cong Bezier
void drawBezierSurface() {
    glColor3f(0.0f, 0.7f, 0.7f); // Dat mau xanh nhat cho mat cong
    for (int i = 0; i < GRID_SIZE; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= GRID_SIZE; j++) {
            float u = (float)i / GRID_SIZE; // Tinh gia tri u tuong ung
            float v = (float)j / GRID_SIZE; // Tinh gia tri v tuong ung
            Point3D p1 = bezierSurface(u, v); // Diem dau tren mat cong
            Point3D p2 = bezierSurface(u + 1.0f / GRID_SIZE, v); // Diem ke tiep tren mat cong
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p2.x, p2.y, p2.z);
        }
        glEnd();
    }
}

// Ham ve cac diem kiem soat
void drawControlPoints() {
    glColor3f(1.0f, 0.0f, 0.0f); // Dat mau do cho cac diem kiem soat
    glPointSize(5.0f); // Kich thuoc diem kiem soat
    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            glVertex3f(controlPoints[i][j].x, controlPoints[i][j].y, controlPoints[i][j].z); // Ve cac diem kiem soat
        }
    }
    glEnd();
}

// Ham hien thi chuong trinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoa man hinh va bo dem do sau
    glLoadIdentity(); // Dat lai ma tran hien tai ve mac dinh

    glTranslatef(0.0f, 0.0f, translateZ); // Dich chuyen vat the theo truc Z
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Xoay vat the quanh truc X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Xoay vat the quanh truc Y

    drawBezierSurface(); // Ve mat cong Bezier
    drawControlPoints(); // Ve cac diem kiem soat

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

// Ham xu ly su kien nhan chuot
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        selectedI = -1; // Dat lai chi so diem kiem soat duoc chon
        selectedJ = -1;
        float minDist = 1000000.0f; // Khoang cach toi thieu mac dinh
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                GLdouble screenX, screenY, screenZ;
                GLint viewport[4];
                GLdouble modelview[16], projection[16];
                glGetIntegerv(GL_VIEWPORT, viewport);
                glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
                glGetDoublev(GL_PROJECTION_MATRIX, projection);
                gluProject(controlPoints[i][j].x, controlPoints[i][j].y, controlPoints[i][j].z,
                           modelview, projection, viewport,
                           &screenX, &screenY, &screenZ); // Tinh toa do tren man hinh cua diem kiem soat
                float dist = std::sqrt(std::pow(screenX - x, 2) + std::pow(screenY - (viewport[3] - y), 2)); // Tinh khoang cach den diem chuot
                if (dist < minDist) {
                    minDist = dist;
                    selectedI = i; // Cap nhat chi so diem duoc chon
                    selectedJ = j;
                }
            }
        }
    }
}

// Ham xu ly su kien keo chuot de thay doi diem kiem soat
void motion(int x, int y) {
    if (selectedI != -1 && selectedJ != -1) {
        GLint viewport[4];
        GLdouble modelview[16], projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        controlPoints[selectedI][selectedJ].x = posX;
        controlPoints[selectedI][selectedJ].y = posY;
        controlPoints[selectedI][selectedJ].z = posZ;

        glutPostRedisplay(); // Cap nhat lai man hinh sau khi di chuyen diem
    }
}

// Ham xu ly su kien nhan phim tu ban phim
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotateX += 5.0f; break; // Xoay quanh truc X len tren
        case 's': rotateX -= 5.0f; break; // Xoay quanh truc X xuong duoi
        case 'a': rotateY -= 5.0f; break; // Xoay quanh truc Y sang trai
        case 'd': rotateY += 5.0f; break; // Xoay quanh truc Y sang phai
        case 'q': translateZ -= 0.5f; break; // Di chuyen gan lai
        case 'e': translateZ += 0.5f; break; // Di chuyen xa ra
        case 27: exit(0); break; // ESC key: Thoat chuong trinh
    }
    glutPostRedisplay(); // Cap nhat lai man hinh sau khi thuc hien thay doi
}

// Ham khoi tao cac diem kiem soat ban dau cho mat cong Bezier
void initControlPoints() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            controlPoints[i][j] = Point3D((float)i / (N - 1) - 0.5f, (float)j / (N - 1) - 0.5f, 
                                          0.2f * std::sin(2 * M_PI * i / (N - 1)) * std::sin(2 * M_PI * j / (N - 1)));
        }
    }
}

// Ham in huong dan su dung chuong trinh
void printInstructions() {
    std::cout << "\n===== HUONG DAN SU DUNG =====\n";
    std::cout << "- Keo va tha diem kiem soat (mau do) de thay doi hinh dang mat\n";
    std::cout << "- Phim w/s: Xoay mat theo truc X\n";
    std::cout << "- Phim a/d: Xoay mat theo truc Y\n";
    std::cout << "- Phim q/e: Di chuyen gan/xa\n";
    std::cout << "- Phim ESC: Thoat chuong trinh\n";
    std::cout << "==============================\n";
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mat cong Bezier");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST); // Kich hoat kiem tra do sau

    initControlPoints(); // Khoi tao cac diem kiem soat ban dau
    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

