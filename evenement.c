#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "evenement.h"


listc nouveauSommet(listc l, int x, int y)
{
	element * newElement = malloc(sizeof(element));
	newElement->x=x;
	newElement->y=y;

	newElement->next = l;

	return newElement;
}


void firstElement (listc l, int x, int y)
{
	if(l->next != NULL)
	{
		firstElement(l->next,x,y);
	}
	else 
	{
		x = l->x;
		y = l->y;
	}
}


void mouseClick(int button, int state, int x, int y, listc l)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
	{
		fprintf(stderr,"Presser ");
		nouveauSommet(l,x,y);
		glutPostRedisplay();
	}
}