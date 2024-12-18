#include <GL/glut.h> // Thu vien GLUT de tao cua so, quan ly su kien va do hoa
#include <vector> // Thu vien vector de lam viec voi danh sach dong
#include <cmath> // Thu vien cho cac ham toan hoc
#include <iostream> // Thu vien nhap xuat co ban
#include <algorithm> // Thu vien chua cac ham tien ich

// Cau truc Point luu toa do cua cac diem
struct Point {
    float x, y;
    Point(float x = 0, float y = 0) : x(x), y(y) {}
};

std::vector<Point> controlPoints; // Danh sach cac diem kiem soat cua duong cong
int selectedPoint = -1; // Chi so diem kiem soat duoc chon
int n = 3; // Bac cua duong cong Bezier

// Ham tinh giai thua
float factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Ham tinh to hop Bernstein
float bernstein(float t, int n, int k) {
    return (factorial(n) / (factorial(k) * factorial(n - k))) 
           * pow(1 - t, n - k) * pow(t, k);
}

// Ham tinh toa do cua mot diem tren duong cong Bezier
Point calculateBezierPoint(const std::vector<Point>& points, float t) {
    Point result;
    int n = points.size() - 1;
    for (int k = 0; k <= n; k++) {
        float B = bernstein(t, n, k); // Tinh gia tri Bernstein
        result.x += points[k].x * B; // Tinh toa do x cua diem tren duong cong
        result.y += points[k].y * B; // Tinh toa do y cua diem tren duong cong
    }
    return result;
}

// Ham ve duong cong Bezier
void drawBezierCurve() {
    if (controlPoints.size() < 2) return; // Khong ve duoc neu khong co du diem kiem soat
    
    glColor3f(1.0f, 0.0f, 0.0f); // Mau do cho duong cong
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1; t += 0.01) {
        Point p = calculateBezierPoint(controlPoints, t); // Tinh diem tren duong cong voi gia tri t
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

// Ham ve cac diem kiem soat
void drawControlPoints() {
    glColor3f(0.0f, 0.0f, 1.0f); // Mau xanh duong cho cac diem kiem soat
    glPointSize(5.0f); // Kich thuoc diem kiem soat
    glBegin(GL_POINTS);
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y); // Ve tung diem kiem soat
    }
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Mau xanh la cho duong noi giua cac diem kiem soat (polygon control)
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y); // Ve duong noi giua cac diem kiem soat
    }
    glEnd();
}

// Ham hien thi chuong trinh
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Xoa man hinh
    drawControlPoints(); // Ve cac diem kiem soat
    drawBezierCurve(); // Ve duong cong Bezier
    glutSwapBuffers(); // Doi buffer de hien thi len man hinh
}

// Ham xu ly su kien chuot
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float wx = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f; // Tinh toa do x trong he toa do cua cua so
        float wy = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT); // Tinh toa do y trong he toa do cua cua so
        
        // Kiem tra xem co click gan diem kiem soat nao khong
        for (int i = 0; i < controlPoints.size(); ++i) {
            if (std::abs(wx - controlPoints[i].x) < 0.05 && 
                std::abs(wy - controlPoints[i].y) < 0.05) {
                selectedPoint = i; // Gan diem kiem soat duoc chon
                return;
            }
        }
        
        // Neu khong click vao diem kiem soat nao, them mot diem moi
        if (controlPoints.size() < n + 1) {
            controlPoints.push_back(Point(wx, wy));
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        selectedPoint = -1; // Huy chon diem khi tha chuot
    }
    glutPostRedisplay();
}

// Ham xu ly su kien keo chuot
void motion(int x, int y) {
    if (selectedPoint != -1) {
        float wx = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f; // Tinh toa do x moi
        float wy = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT); // Tinh toa do y moi
        controlPoints[selectedPoint] = Point(wx, wy); // Cap nhat vi tri diem kiem soat duoc chon
        glutPostRedisplay();
    }
}

// Ham xu ly su kien ban phim
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        exit(0); // Thoat chuong trinh
    } else if (key == '+' && n < 10) { // Tang bac cua duong cong
        n++;
        if (controlPoints.size() < n + 1) {
            // Them diem moi neu can thiet
            if (!controlPoints.empty()) {
                Point lastPoint = controlPoints.back();
                controlPoints.push_back(Point(lastPoint.x + 0.1f, lastPoint.y + 0.1f));
            } else {
                controlPoints.push_back(Point(0, 0));
            }
        }
    } else if (key == '-' && n > 1) { // Giam bac cua duong cong
        n--;
        if (controlPoints.size() > n + 1) {
            controlPoints.pop_back(); // Xoa bot diem kiem soat
        }
    }
    glutPostRedisplay();
}

// Ham in huong dan su dung chuong trinh
void printInstructions() {
    std::cout << "\n===== HUONG DAN SU DUNG =====\n";
    std::cout << "- Click chuot trai de them diem kiem soat (toi da " << n + 1 << " diem)\n";
    std::cout << "- Keo va tha diem kiem soat de thay doi vi tri\n";
    std::cout << "- Nhan '+' de tang bac cua duong cong (toi da 10)\n";
    std::cout << "- Nhan '-' de giam bac cua duong cong (toi thieu 1)\n";
    std::cout << "- Nhan 'ESC' de thoat chuong trinh\n";
    std::cout << "==============================\n";
}

// Ham main cua chuong trinh
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Khoi tao GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Chon che do hien thi
    glutInitWindowSize(800, 600); // Kich thuoc cua so
    glutCreateWindow("Duong cong Bezier"); // Tao cua so moi

    // Gan cac ham xu ly su kien
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Dat mau nen trang
    
    printInstructions(); // In huong dan su dung

    glutMainLoop(); // Bat dau vong lap GLUT
    return 0;
}

