#include "droite.h"

void tracerPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(0,0,0);
	glVertex2i(x,y);
	glEnd();
}
