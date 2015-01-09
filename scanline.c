#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "scanline.h"


int calc_x_min(list l, int x)
{
	int xmin;
	xmin = x;
	if(l == NULL)
	{
		return xmin;
	}
	else if(xmin < (l->x))
	{
		return calc_x_min(l->next, xmin);
	}
	else
	{
		return calc_x_min(l->next, l->x);
	}
}

int calc_x_max(list l, int x)
{
	int xmax;
	xmax = x;
	if(l == NULL)
	{
		return xmax;
	}
	else if(xmax > (l->x))
	{
		return calc_x_max(l->next, xmax);
	}
	else
	{
		return calc_x_max(l->next, l->x);
	}
}

int calc_y_min(list l, int y)
{
	int ymin;
	ymin = y;
	if(l == NULL)
	{
		return ymin;
	}
	else if(ymin < (l->y))
	{
		return calc_y_min(l->next, ymin);
	}
	else
	{
		return calc_y_min(l->next, l->y);
	}
}

int calc_y_max(list l, int y)
{
	int ymax;
	ymax = y;
	if(l == NULL)
	{
		return ymax;
	}
	else if(ymax > (l->y))
	{
		return calc_y_max(l->next, ymax);
	}
	else
	{
		return calc_y_max(l->next, l->y);
	}
}

