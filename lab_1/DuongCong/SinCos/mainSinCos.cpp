#include <iostream>

#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define M_PI    3.14159265358979323846
using namespace std ;

int wScreen = 1000 , hScreen = 1000 ; 



void drawPointCos(float x , float y ){
	double size = 0.05;
	glBegin(GL_POINTS) ;
		for(int k = -2 ; k <= 2 ; k++){
		glVertex2f(size*(x + 2*k*M_PI),size*2*y) ;
		glVertex2f(size*(-x+ 2*k*M_PI),size*2*y) ;
		
		glVertex2f(size*(-x + M_PI + 2*k*M_PI ),size*2*-y) ;
		glVertex2f(size*(x+M_PI + 2*k*M_PI),size*2*-y) ;	
		glVertex2f(size*-(-x + M_PI + 2*k*M_PI ),size*2*-y) ;
		glVertex2f(size*-(x+M_PI + 2*k*M_PI),size*2*-y) ;	
	
		}
		
				
	glEnd();
}
void drawPointSin(float x , float y ){
	double size = 0.05;
	glBegin(GL_POINTS) ;
		for(int k = -2 ; k<=2 ; k++){
			glVertex2f(size*(x + 2*k*M_PI ),size*2*y) ;
			glVertex2f(size*(-x + 2*k*M_PI ),size*2*(-y)) ;
			glVertex2f(size*(-x + M_PI + 2*k*M_PI ),size*2*y) ;		
			glVertex2f(size*(x - M_PI  + 2*k*M_PI),size*2*(-y)) ;
		}

			
	glEnd();
}


void drawCosMidpoint(){
	float PI_2 = M_PI/2 ;
	float x = 0 , y = 1 ;
	float deta = (2 / M_PI )* 0.01;
	float p = 1 - cos(0.001) - deta/2 ;
	
	while (x <=  PI_2) {	
		drawPointCos(x , y);
		
		if(p < 0){
			p+= 2*sin((2*x+0.003)/2)*sin(0.001/2) ;
			
		}	
		else {
			p+= -deta +  2*sin((2*x+0.003)/2)*sin(0.001/2) ;
			y-=deta ;
		}
		x+=0.001 ;
	}
	

}

void drawSinMidPoint(){
	float deta = (2/M_PI ) * 0.01 ;
	double p = deta - sin(0.001)  ;
	float x = 0 , y = 0 ;
	float PI_2 = M_PI/2 ;
	
	while(x <= PI_2) {
		drawPointSin(x , y) ;
		cout << p << endl ;
		if(p<0){
			p+= deta -2*cos((2*x+0.003)/2)*sin(0.001/2) ;
			y+=deta ;
		}
		else {
			p+= -2*cos((2*x+0.003)/2)*sin(0.001/2) ;
		}
		x+=0.001 ;
		
		
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
	
	
	glColor3f(0.0f , 1.0f , 1.0f);
	drawCosMidpoint();
	
	glColor3f(1.0f , 0.0f , 1.0f);
	drawSinMidPoint();

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
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutMainLoop();
} 
