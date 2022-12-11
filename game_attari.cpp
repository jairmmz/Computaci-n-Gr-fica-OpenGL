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

