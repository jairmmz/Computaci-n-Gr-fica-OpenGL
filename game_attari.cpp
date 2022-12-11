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
