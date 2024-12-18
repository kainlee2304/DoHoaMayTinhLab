#include <iostream>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std ;
int x1s = 10 , x2s = -10 , y1s = 30 , y2s = -30 ; // luu toa do diem bat dau va ket thuc cua duong thang
int index = 0 ; //kiem tra trang thai cua diem dau va diem cuoi
float pointsize = 1.5 ; // thiet lap kich thuo diem ve

//thiet lap cac thong so co ban
void init(){
	glClearColor(1.0 , 1.0 , 1.0 , 0.0); //thiet lap mau nen:mau trang
	glMatrixMode(GL_PROJECTION); // chuy sang che do thiet lap phoi canh
	glLoadIdentity();// dat lai ma tran don vi
	glOrtho(-300 , 300  ,  -300 , 300 , -1 , 1 ); //dat goc toa do 00 vào giua cua so
}


//Ham LineBres thuat toan Bresenham de ve duon thang
void LineBres(int x1 , int y1 , int x2 , int y2) {
	double p,Dx,Dy,x,y,const1,const2 ;
	Dx = x2-x1 ; Dy = y2 - y1 ;
	x = x1 ; y = y1 ;
	double m = Dy/Dx ;// m:he so goc
	
	if( m <= 1 && m >= 0 ){ // duong thang di tu trai qua phai voi do doc nho hon hoac bang 45
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
	else if(m > 1) { //Duong thang co do doc lon hon 45 do, di tu duoi len tren.
		p = 2*Dx - Dy ;
		const1 = 2*Dx ; const2 = 2*(Dx - Dy) ;
		if(Dy > 0){
			
			while(y <= y2){	
				glBegin(GL_POINTS) ;
					glVertex2i(x , y) ;
				glEnd();
			
				if(p < 0){
					p+=const1 ;	
				}
				else {
					p+=const2 ;
					x++ ;
				}
				y++;
			}
		}
		else {
			
			while(y >= y2){
				glBegin(GL_POINTS) ; //ve diem xy
					glVertex2i(x , y) ;
				glEnd();
				
				if(p < 0){
					p+=const2 ;	
					x-- ;
				}
				else {
					p+=const1 ;
					
				}
				y--;
			}
		}
		
			
	}
	else if(m <-1) {//Duong thang co do doc lon hon 45 do, di tu tren xuong duoi.
		p = -2*Dx + Dy ;
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
	else if( m <= 0 && m >= -1) {//Duong thang co do doc nho hon 45 do, di tu phai qua trai.
		p = -2*Dy+Dx ;
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
// ve duong thang 
void display(){
	glClear(GL_COLOR_BUFFER_BIT) ;//xoa toan bo buffer mau
	glPointSize(pointsize);// thiet lap kich thuoc diem
	glColor3f(1.0f , 0.0f , 0.0f);//thiet lap mau cua diem
		
	LineBres(x1s,y1s,x2s,y2s);	// goi ham LineBress de ve duon thang tu x1s ,y1s den x2s,y2s
	glFlush(); //ket thuc qua trinh ve
}

//xy ly su kien chuot cho phep nguoi dung chon cac diem ve duong thang 
void mouse(int button , int state , int x , int y) {
	int xtest = 0 , ytest = 0 ;//xtest,ytest bien trung gian de luu trang thai cua x,y
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){ //GLUT_LEFT_BUTTON: nut chuot trai |GLUT_DOWN: chuot da duoc nhan
		cout << "x=" << x << "y=" << y << endl ;// button la tham so dau vao cua ham mouse | stace:tham so dau vao chua trang thai cua chuot
		xtest = x-300; //chuyen toa do x,y tu he toa do mac dinh ve he toa do glOrtho
		ytest = 300 - y  ;
		
		if(index == 0){// index = 0 chuong trinh hieu nguoi dung chon diem dau tien va index duoc dat lai = 1
			x1s = xtest ;
			y1s = ytest ;
			index = 1 ;
		}
		else { // index=1 chuong trinh hieu la nguoi dung dang chon diem cuoi va index duoc dat lai = 0
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
	glutCreateWindow("Duong thang") ;
	init();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse) ;
	glutMainLoop();
} 
