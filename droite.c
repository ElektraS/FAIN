#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "droite.h"

Color Color_new(float red, float green, float blue)
{
	Color c;
	c._red = red;
	c._green = green;
	c._blue = blue;
	return c;
}

list nouveauSommet(list l, int x, int y)
{
	list newElement = malloc(sizeof(struct element));
	newElement->x=x;
	newElement->y=y;
	newElement->next = l;
	newElement->prev = NULL;


	if(l!=NULL)
	{
		newElement->next->prev = newElement;
		newElement->id = 1;
	}
	else newElement->id = 0;

	return newElement;
}


list firstElement(list l)
{
	if(l==NULL)
	{
		return NULL;
	}
	else if(l->next != NULL)
	{
		if(l->id!=0)
		{
			return firstElement(l->next);
		}
		else 
		{
			return l;
		}	
	}
	else 
	{
		return l;
	}
}

list supprimerSommet(list l)
{
	if(l==NULL)
	{
		return NULL;
	}
	else if(l->id != 0)
	{
		if(l->prev != NULL)
		{
			l->next->prev = l->prev;
			l->prev->next = l->next;
		}
		else l->next->prev = l->prev;
	}
	else 
	{
		if(l->prev != NULL)
		{
			l->prev->id = 0;
			l->prev->next = l->next;	
		}
		else if(l->next != NULL)
		{
			l->next->id=0;
			l->next->prev = l->prev;
		}
	}
	return l;
}

list next_Summit(list l)
{
	list tmp;
	if(l!=NULL)
	{
		if(l->next != NULL)
			{
				tmp = firstElement(l);
				tmp->id = 1;
				tmp->next->id = 0;
				return l->next;
			}
		else return l;
	}
	else return l;
}

list previous_Summit(list l)
{
	list tmp;
	if(l!=NULL)
	{
		if(l->prev != NULL) 
			{
				tmp = firstElement(l);
				tmp->id = 1;
				tmp->prev->id = 0;
				return l->prev;
			}
		else return l;
	}
	else return NULL;
}

