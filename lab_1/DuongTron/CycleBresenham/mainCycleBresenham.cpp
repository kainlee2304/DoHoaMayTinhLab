#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;

int x1s=0,x2s=0,y1s=0,y2s=50 ;
int index = 0 ;

void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300 , 300  , -300 , 300 , -1 , 1 );
}
// Ham ve 8 diem doi xung cua duong tron
void draw8point(int xc , int yc , int x , int y){
	glBegin(GL_POINTS) ;
			glVertex2i(xc+x,yc+y) ;// doi xung x,y qua tam xc,yc
			glVertex2i(xc+y,yc+x) ;
			glVertex2i(xc-x,yc+y) ;
			glVertex2i(xc-y,yc+x) ;
			glVertex2i(xc+x,yc-y) ;
			glVertex2i(xc+y,yc-x) ;
			glVertex2i(xc-x,yc-y) ;
			glVertex2i(xc-y,yc-x) ;
	
		glEnd();
}
// Ham ve nua tren cua duong tron su dung thuat toan Midpoint
void ClrcleBres1(int xc , int yc , int r ){
	double x , y , p , const1 , const2 ;
	x = r ; y = 0 ; p = 2*r-3;  
	
	while (y <= x){
		
		draw8point(xc , yc , x , y) ;// Ve 8 diem doi xung cua duong tron
		
		
			if(p < 0){
				//cong thuc khi p<0
				const1 = 4*(x-y) - 10  ;
				p+=const1 ;
				x-- ;
			}
			else {
				//cong thuc khi p>0
				const2 = 4*y+6  ;
				p-=const2;
				
			}
			y++ ;
		
	}
}
// Ham ve nua duoi cua duong tron su dung thuat toan Midpoint
void ClrcleBres2(int xc , int yc , int r ){
	double x , y , p , const1 , const2 ;
	x = 0 ; y = -r ; p = 3-2*r;  
	
	while (x <= -y){
		
		draw8point(xc , yc , x , y) ;
		
		
			if(p >= 0){
				
				const1 = 4*(y+x) + 2  ;
				p+=const1 ;
				y++ ;
			}
			else {
				
				const2 = 4*x+6  ;
				p+=const2;
				
			}
			x++ ;
		
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	glColor3f(1.0f , 0.0f , 0.0f);
	
	int r = sqrt(pow(x1s-x2s,2) + pow(y1s-y2s , 2)) ;//Tinh ban kinh r cua duong tron dua tren toa do hai diem x1s, y1s va x2s, y2s.
	
	ClrcleBres2(x1s,y1s, r);
	
	glFlush();//thuc thi lenh
}


void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout << "x=" << x << "y=" << y << endl ;
		xtest = x-300;
		ytest = 300 - y  ;
		
		if(index == 0){
			x1s = xtest ;
			y1s = ytest ;
			index = 1 ;
		}
		else {
			x2s = xtest ;
			y2s = ytest ;
			index = 0 ;
		}
		
		glutPostRedisplay();// cap nhat lai man hinh
	}
}

int main(int argc, char** argv) {
	glutInit(&argc , argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600 , 600) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Duong tron") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutMainLoop();
} 
