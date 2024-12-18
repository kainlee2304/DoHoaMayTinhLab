#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;

int wScreen = 600 , hScreen = 600 ; 

void init(){
	glClearColor(0.0 , 0.0 , 0.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-wScreen/2 , wScreen/2  , -hScreen/2 , hScreen/2 , -1 , 1 );
}
// ve doi xung qua truc y
// a:he so trong parabol x,y:toa do cua diem can ve xt,yt:Toa do diem dinh cua parabol (diem doi xung).
void draw2point(int x , int y , double a , double xt , double yt){
	glBegin(GL_POINTS) ;
		if(a > 0) {
			glVertex2i(x+xt,y+yt) ;//Ve diem tai (x + xt, y + yt)
			glVertex2i(-x+xt,y+yt) ;
		}
		else {
			glVertex2i(x+xt,-y+yt) ;
			glVertex2i(-x+xt,-y+yt) ;
		}
					
	glEnd();
}
//Ve parabol bang thuat toan Bresenham
void drawParabolBresenham(double a , double b , double c) {
	double p , const1 , const2 , x0 , y0 , x , y , as ;
	as = abs(a) ;
	x = 0 , y = 0 ;
	x0 = 0.5/as ;//Gioi han ban dau cho x dua tren do doc cua parabol
	y0 = hScreen/2 - 50 ;//// Gioi han tren cua y de ngan parabol vuot khoi man hinh
	
	double xt = -b/(2*a) , yt = -(pow(b , 2) - 4*a*c)/(4*a);
	// Nhánh 1:gan dinh
	p = 1 - 2 * as ;
	while(x<=x0){
		draw2point(x , y , a , xt , yt) ;
		
		if(p<0){
			const1 = 2 - 2*as*(2*x + 3) ;
			p+=const1;
			y++ ;
		}
		else {
			const2 = - 2*as*(2*x + 3) ;
			p+=const2 ;
		}
		
		x++ ;
	}
	
	// Nhánh 2:xa dinh hon
	p = (2*(y+1)/as) - (2*pow(x,2) + 2*x +1) ;
	while( y <= y0){
		draw2point(x , y, a , xt , yt) ;
		if(p < 0){
			const1 = 2/as ;
			p+=const1 ;
		}
		else {
			const2 = (2/as) - 4*(x+1) ;
			p+=const2;
			x++ ;
		}
		y++ ;
	}
	
	
	
}

void drawParabolMidpoint(double a , double b , double c){
	double p,x,y,x0,y0,consts,absA;
	absA = abs(a) ;
	x = 0 ; y=0 ;
	x0 = 0.5/absA ; y0 = (hScreen/2) - 50 ;
	//toa do dinh
	double xt = -b/(2*a) , yt = -(pow(b , 2) - 4*a*c)/(4*a); //toa do dinh
	
	//Nhánh 1
	p = absA-1/2 ;
	while(x <= x0){
		draw2point(x, y, a, xt, yt) ;
		
		if(p<0){
			consts = absA*(2*x + 3) ;
			p+=consts ;
		}
		else {
			consts = absA*(2*x + 3) - 1 ;
			p+=consts;
			y++ ;
		}
		x++ ;
	} 
	
	//Nhánh 2 
	
	p = absA*pow(x+0.5 , 2) - (y+1) ;
	while(y <=y0){
		draw2point(x, y, a, xt, yt) ;
		
		if(p<0){
			consts = absA*(2*x + 2) - 1 ;
			p+=consts ;
			x++;
		}
		else {
			p--;
		}
		y++ ;
	} 
	
}



void draw(double a , double b , double c , bool condition){
	if(a == 0){
		if(b == 0){
			
		}
		else {
		
		}
	}
	else {
		if(condition){
			drawParabolBresenham(a , b , c) ;
		}
		else {
			drawParabolMidpoint(a,b,c);
		}
		
	}
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	glColor3f(1.0f , 0.0f , 0.0f);
	
	glBegin(GL_LINE_LOOP);
		glVertex2i(-wScreen/2 , 0) ;
		glVertex2i(wScreen/2 , 0) ;
			
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, hScreen/2) ;
		glVertex2i(0 , -hScreen/2) ;
	glEnd();
	//true: Bresenham
	//false: MidPoint
	glColor3f(1.0f , 1.0f , 0.0f);
	draw(0.05 , 5 , -4,true);
	glColor3f(1.0f , 0.0f , 1.0f);
	draw(-0.05 , 2 , 8,false);
	
	
	
	
	glFlush();
}


void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout << "x=" << x << "y=" << y << endl ;
		xtest = x-300;
		ytest = 300 - y  ;
		
		
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc , argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wScreen , hScreen) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Parabol") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutMainLoop();
} 
