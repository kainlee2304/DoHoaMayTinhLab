#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;
int x1s = 10 , x2s = -10 , y1s = 30 , y2s = -90 ;
int index = 0 ;
//khoi tao moi truong do hoa
void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300 , 300  ,  -300 , 300 , -1 , 1 );
}



void MidPoint(int x1 , int y1 , int x2 , int y2) {
	double p,Dx,Dy,x,y,const1,const2 ;
	Dx = (x2-x1) ; Dy = y2 - y1 ;
	x = x1 ; y = y1 ;
	double m = Dy/Dx ;
	cout << x1 << "=" << y1 << endl ;
	if( m <= 1 && m >= 0 ){
		p = 2*Dy-Dx ;
		const1 = 2*Dy ; const2 = 2*(Dy - Dx) ;
		if(Dx < 0 && m!= 0){
			while(x >= x2){
				glBegin(GL_POINTS);
					glVertex2i(x,y);
				glEnd();
				if(p < 0){
					p+=const2 ;
					y-- ;
					
				}
				else {
					p+=const1 ;	
				}
				x-- ;
			}
			
		}
		else {
			while(x<=x2){
				glBegin(GL_POINTS);
					glVertex2i(x,y);
				glEnd();
				if(p < 0){
					p+=const1 ;
				}
				else {
					p+=const2 ;
					y++ ;	
				}
				x++ ;
			}
		}
		
	}
	else if(m > 1) {
		p =  Dy - 2*Dx ;
		const1 = 2*Dx ; const2 = 2*(Dx - Dy) ;
		if(Dy > 0){
			
			while(y <= y2){	
				glBegin(GL_POINTS) ;
					glVertex2i(x , y) ;
				glEnd();
			
				if(p < 0){
					p-=const2 ;	x++ ;
				}
				else {
					p-=const1 ;
					
				}
				y++;
			}
		}
		else {
			cout << "s" ;
			while(y > y2){
				glBegin(GL_POINTS) ;
					glVertex2i(x , y) ;
				glEnd();
				
				if(p < 0){
					p-=const1 ;	
					
				}
				else {
					p-=const2 ;
					x-- ;
				}
				y--;
			}
		}
		
			
	}
	else if(m <-1) {
		p = -2*Dx - Dy ;
		const1 = 2*Dx ; const2 = 2*(Dx + Dy) ;
		if(Dy > 0){
			while (y <=y2) {
			
				glBegin(GL_POINTS) ;
					glVertex2i(x , y) ;
				glEnd();	
			
				if(p < 0){
					p-=const1 ;	
				}
				else {
					p-=const2 ;
					x-- ;
				}
				y++;
			}
		}
		else {
			while (y >= y2) {
			
				glBegin(GL_POINTS) ;
					glVertex2i(x , y) ;
				glEnd();	
			
				if(p < 0){
					p-=const2 ;
					x++ ;
					
				}
				else {
					p-=const1 ;	
				}
				y--;
			}
		}
		
	}
	else if( m <= 0 && m >= -1) {
		p = -2*Dy-Dx ;
		const1 = 2*Dy ; const2 = 2*(Dy + Dx) ;
		if(Dx < 0 && m!= 0){
			while(x>=x2){
				glBegin(GL_POINTS);
					glVertex2i(x,y);
				glEnd();
				if(p < 0){
					p-=const2 ;
					y++ ;
					
				}
				else {
					p-=const1 ;	
				}
				x-- ;
			}
			
		}
		else {
			while(x<=x2){
				glBegin(GL_POINTS);
					glVertex2i(x,y);
				glEnd();
				if(p < 0){
					p-=const1 ;
				}
				else {
					p-=const2 ;
					y-- ;	
				}
				x++ ;
			}
		}	
	}
	
	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	float size = 2.0 ;
	glColor3f(1.0f , 0.0f , 0.0f);
	MidPoint(x1s,y1s,x2s,y2s);	
	
	glColor3f(0.0f , 0.0f , 1.0f);
	
	glPointSize(size) ;
	glBegin(GL_POINTS);
		glVertex2i(x1s , y1s) ;
		glVertex2i(x2s , y2s) ;
	glEnd();	
	
	
	glFlush();
}


void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
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
		
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc , argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600 , 600) ;
	glutInitWindowPosition(50, 50) ;
	glutCreateWindow("Duong thang") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutMainLoop();
} 
