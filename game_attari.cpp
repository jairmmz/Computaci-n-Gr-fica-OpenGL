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

float round_value(float v)
{
	return floor(v + 0.5);
}

struct brick
{
	int state;
	int e;
	brick()
	{
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
// static int tray_y = 0;

const double DEG2RAD = 3.14159 / 180;

void dda(int x0, int y0, int x1, int y1)
{
	float x, y, xs, ys;
	int dx, dy, st;
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;

	if (abs(dx) > abs(dy))
	{
		st = abs(dx);
	}
	else
	{
		st = abs(dy);
	};

	if (st == 0)
	{
		glVertex2f(x, y);
		return;
	}

	xs = (float)dx / st;
	ys = (float)dy / st;

	for (int i = 0; i < st; i++)
	{
		glVertex2f(x, y);
		x = x + xs;
		y = y + ys;
	}
}

void drawCircle(float radius)
{
	int x, y;
	int x0, y0, x1, y1;
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);

	x = radius * cos(0 * DEG2RAD);
	y = radius * sin(0 * DEG2RAD);
	x0 = ball_x + x;
	y0 = ball_y - y;

	for (int i = 0; i < 360; i++)
	{
		x = radius * cos(i * DEG2RAD);
		y = radius * sin(i * DEG2RAD);
		
		x1 = ball_x + x;
		y1 = ball_y - y;

		dda(x0, y0, x1, y1);
		x0 = x1;
		y0 = y1;
	}
	glEnd();
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
			if (arr[i][j].state == 1)
			{
				glBegin(GL_POLYGON);
				glColor3f(0.7, 0.7, 0.6);
				dda(i * 50, 900 - j * 52, i * 50, 950 - j * 52);
				dda(i * 50 + 45, 950 - j * 52, i * 50 + 45, 900 - j * 52);
				glEnd();
			}
	}

	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f((rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0);

	dda(tray_x - 60, 20, tray_x + 60, 20);
	glEnd();

	// glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
	drawCircle(10);

	glFlush();
}

void moveahead(void)
{
	if (ball_x >= 1000)
	{
		ball_vec_x *= -1;
	}
	else if (ball_y >= 1000)
	{
		ball_vec_y *= -1;
	}
	else if (ball_x <= 0)
	{
		ball_vec_x *= -1;
	}
	else if (ball_x >= tray_x - 60 && ball_x <= tray_x + 60 && ball_y == 40)
	{
		ball_vec_y *= -1;
	}
	ball_x += ball_vec_x;
	ball_y += ball_vec_y;

	if (ball_y >= 645)
	{
		int x = ball_x / 50;
		int y = (900 - ball_y) / 50;
		y--;
		if (arr[x][y].state == 1)
		{
			arr[x][y].state = 0;
			ball_vec_y *= -1;
		}
	}

	if (ball_y < 0)
	{
		cout << "Bien jugado int�ntalo de nuevo!!";
		exit(0);
	}
}

void animate(int value)
{
	if (isAnimate)
	{
		moveahead();
		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	case ' ':
		if (isAnimate)
			isAnimate = 0;
		else
		{
			isAnimate = 1;
			animate(1);
		}
		break;
	}
}

void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT && tray_x >= 60)
	{
		tray_x -= 20;
	}
	else if (key == GLUT_KEY_RIGHT && tray_x <= 940)
	{
		tray_x += 20;
	}
	glutPostRedisplay();
}

void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1000, 0.0, 1000);
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	/* Inicializar librer�a GLUT */
	glutInit(&argc, argv);

	/* Establecer el modo de visualizaci�n inicial */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	/* Establecer el tama�o y la posici�n de la ventana inicial */
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(100, 100);

	/* Cree la ventana con el t�tulo "DBrick Breaker with OpenGL and DDA" */
	glutCreateWindow("Brick Breaker with OpenGL and DDA");

	/* Inicializar colores de dibujo*/
	setup();

	/* Llame a la funci�n de visualizaci�n */
	glutDisplayFunc(render); // LineDDA

	// glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	/* Seguir mostrando hasta que se cierre el programa */
	glutMainLoop();
}
