#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#define  INC 10
#define M_PI 3.14159265358979323846


typedef struct {
	int x , y , z;
} Point;

Point A,B,wmax,wmin ;
float goc;
bool stateMouse = true ;


void init() {
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300 , 300  , -300 , 300 , -1 , 1 );
	
	A.x = 200 ; A.y = 200 ;  A.z = 1 ;
	B.x = 50 ; B.y = -100 ; B.z = 1 ;
	
	wmin.x = -120 ; wmin.y = -50 ; wmin.z =1; 
	wmax.x = 100 ; wmax.y= 100 ; wmax.z = 1 ;
	
	goc = 0 ;
}
int Code(Point M){
	int m=0;
	if(M.x<wmin.x) m |=1;
	if(M.x>wmax.x) m |=2;
	if(M.y<wmin.y) m |=4;
	if(M.y>wmax.y) m |=8;
	return m;
}
Point rotate(Point A, int g){
	float goc_rad =g * M_PI/180;
	Point T;
	T.x=A.x*cos(goc_rad)-A.y*sin(goc_rad);
	T.y=A.x*sin(goc_rad)+A.y*cos(goc_rad);
	T.z = 1 ;
	return T;
}
void createRectangle(Point wmin,Point wmax,int g) {
	Point A,B,C,D;	
	A=wmin;
	C=wmax;
	B.x=wmax.x; B.y=wmin.y; B.z = 1 ;
	D.x=wmin.x; D.y=wmax.y; D.z = 1 ;
	
	A=rotate(A,g);
	B=rotate(B,g);
	C=rotate(C,g);
	D=rotate(D,g);
	
	glBegin(GL_LINE_LOOP);
	glVertex2i(A.x,A.y);
	glVertex2i(B.x,B.y);
	glVertex2i(C.x,C.y);
	glVertex2i(D.x,D.y);
	glEnd();
	
}

void createLine(Point A , Point B){
	glBegin(GL_LINES);
		glVertex2i(A.x,A.y);
		glVertex2i(B.x,B.y);
	glEnd();
}	

void swapHandle(Point *A,Point *B){
	Point T;
	T=*A;	*A=*B;	*B=T;
}

void XenHinhNhiPhan(Point A,Point B,Point wmin,Point wmax,int g){
	Point P,Q,M;
	
	if((Code(A)|Code(B))==0) createLine(rotate(A,g),rotate(B,g));
	if((Code(A)&Code(B))!=0) return ;
	if((Code(A)!=0) &&(Code(B)==0))	swapHandle(&A,&B);
	if((Code(A)==0) &&(Code(B)!=0)) 
	{
		P=A;Q=B;
		while((abs(P.x-Q.x)+abs(P.y-Q.y))>2)
		{
			M.x=(P.x+Q.x)/2;
			M.y=(P.y+Q.y)/2;
			if(Code(M)==0)	P=M;
			else			Q=M;				
		}
		createLine(rotate(A,g),rotate(P,g));
	}
	if((Code(A)!=0)&&(Code(B)!=0)&&((Code(A) & Code(B))==0))
	{
		P=A;Q=B;
		M.x=(P.x+Q.x)/2;
		M.y=(P.y+Q.y)/2;

		while(( Code(M)!=0) && ((abs(P.x-Q.x)+abs(P.y-Q.y))>2))
		{
			if((Code(P)& Code(M)) !=0)	P=M;
			else Q=M;
			M.x=(P.x+Q.x)/2;
			M.y=(P.y+Q.y)/2;			
		}
		if(Code(M)==0)
		{
			XenHinhNhiPhan(P,M,wmin,wmax,g);
			XenHinhNhiPhan(M,Q,wmin,wmax,g);
		}
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;
	
	
	float size = 4.0 ;
	glPointSize(size) ;
	
	glColor3f(1.0f , 1.0f , 1.0f) ;
	createRectangle(wmin , wmax , goc);
	
	glColor3f(1.0f , 0.0f , 0.0f) ;
	createLine(A, B);
	
	glColor3f(0.0 , 1.0 , 1.0) ;
	XenHinhNhiPhan(rotate(A,-goc),rotate(B,-goc),wmin,wmax,goc);
	 
	glFlush();
}

void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		xtest = x-300;
		ytest = 300 - y  ;
		
		if(stateMouse ){
			A.x = xtest ;
			A.y = ytest;
			stateMouse = false ;
		}
		else {
			B.x = xtest ;
			B.y = ytest;
			stateMouse = true  ;
			
		}
		
		glutPostRedisplay();
	}
}
void keyboard(int key , int x , int y) {
	switch(key)
	{
	case GLUT_KEY_UP:
		goc += INC;
		if(goc >360) goc=0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		goc -= INC;
		if(goc <0) goc=360;
		glutPostRedisplay();
		break;
	}
}

int main(int argc,char* arg[]){
	glutInit(&argc , arg);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize (600, 600); 
	glutInitWindowPosition (10, 10); 
	init();
	glutCreateWindow("Thuat Toan Xen Hinh");
	gluOrtho2D(-300, 300, -300, 300);
	
	glutMouseFunc(mouse);	
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutMainLoop();
}
