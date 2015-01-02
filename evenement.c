#include "droite.h"
#include "evenement.h"


listc nouveauSommet(listc l, int x, int y)
{
	element * newElement = malloc(sizeof(element));
	newElement->x=x;
	newElement->y=y;

	newElement->next = l;

	return newElement;
}


void firstElement(listc l, int x, int y)
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
		tracerDroite(x, y, l->next->x, l->next->y);
		glutPostRedisplay();
	}
}

void keyboard_CB(unsigned char key, listc l)
{
	printf("key = %c = %d\n", key, key);
	if(key==99)
	{
		int x;
		int y;
		firstElement(l, x, y);
		tracerDroite(x, y, l->x, l->y);
	}
	if(key==27 || key==113) exit(0); // Touche Escape ou q : quitter le programme

	glutPostRedisplay();
}