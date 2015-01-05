#include "droite.h"
#include "evenement.h"


list nouveauSommet(list l, int x, int y)
{
	list newElement = malloc(sizeof(struct element));
	newElement->x=x;
	newElement->y=y;

	newElement->next = l;

	return newElement;
}


point firstElement(list l)
{
	point res;
	if(l->next != NULL)
	{
		firstElement(l->next);
	}
	else 
	{
		res.x = l->x;
		res.y = l->y;
	}
	return res;
}

void keyboardC(unsigned char key, list l)
{
	printf("key = %c = %d\n", key, key);
	if(key==99) //touche c : devient polygone
	{
		point firstElem;
		firstElem = firstElement(l);
		tracerDroite(firstElem.x, firstElem.y, l->x, l->y, Color_new(255, 255, 255));
	}
	if(key==27 || key==113) exit(0); // Touche Escape ou q : quitter le programme

	glutPostRedisplay();
}