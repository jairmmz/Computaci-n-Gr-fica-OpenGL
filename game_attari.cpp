#include <iostream>
#include <cmath> // #include <math.h> //-> DDA
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxn 100
using namespace std;

//static int X1 = 500, Y1, X2 = 500, Y2;

float round_value(float v)
{
	return floor(v + 0.5);
}

struct brick{
	int state;
	int e;
	brick(){
		state = 1;
		e = 1;
	}
};
brick arr[maxn][5];
static int ball_x = 500;
static int ball_y = 40;
static int ball_vec_x = 1;
static int ball_vec_y = -1;
static int animationPeriod = 4;
static int isAnimate = 0;
static int tray_x = 500;
//static int tray_y = 0;
const double DEG2RAD = 3.14159/180;

void dda(int x0, int y0, int x1, int y1){
	float x, y, xs, ys;
	int dx, dy, st;
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;
	
	if(abs(dx) > abs(dy)){
		st = abs(dx);
	}else{
		st = abs(dy);
	};
	
	if(st==0){
		glVertex2f(x,y);
		return;
	}
	
	xs = (float)dx/st;
	ys = (float)dy/st;
	
	for(int i=0; i<st; i++){
		glVertex2f(x,y);
		x = x + xs;
		y = y + ys;
	}
}

void drawCircle(float radius)
{
	//int n = 7;
	//int r = 10;
	int x, y;
	int x0, y0, x1, y1;	
	glBegin(GL_POINTS);
	glColor3f(1.0f,0.0f,0.0f);
	
	x = radius*cos(0*DEG2RAD);
	y = radius*sin(0*DEG2RAD);
	x0 = ball_x + x;
	y0 = ball_y - y;

	for (int i=0; i < 360 ; i++)
	{
		//double degInRad = i*DEG2RAD;
		//glVertex2f(x+ball_x  ,y+ball_y  );
		x1 = ball_x + x;
		y1 = ball_y - y;
		
		dda(x0, y0, x1, y1);
		x0 = x1;
		y0 = y1;
		
		/*if(i%18==0){
			r++;
		}
		*/
	}
	glEnd();
}

void render( void ){
	glClear(GL_COLOR_BUFFER_BIT);
	
	for( int i = 0; i < 20 ; i++){
		for( int j =0 ; j<5 ; j++)
			if( arr[i][j].state == 1){
			glBegin(GL_POLYGON);
			glColor3f(0.7,0.7,0.6);
			glVertex2i(i*50,900-j*52);
			glVertex2i(i*50,950-j*52);
			glVertex2i(i*50+45,950-j*52);
			glVertex2i(i*50+45,900-j*52);
			glEnd();
		}
	}
	
	glPointSize(10);
	glBegin(GL_POLYGON);
	glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
	glVertex2i(tray_x-60,2);
	glVertex2i(tray_x-60,20);
	glVertex2i(tray_x+60,20);
	glVertex2i(tray_x+60,2);
	glEnd();
	
	glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
	drawCircle(10);
	
	glFlush();
}