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
int nb_Summit(list l, int a)
{
	int res;
	res = a;
	if(l==NULL)
	{
		return a + 0;
	}
	else if(l->next != NULL)
	{
		if(l->id!=0)
		{
			return nb_Summit(l->next, res + 1);
		}
		else 
		{
			return res;
		}	
	}
	else 
	{
		return res;
	}
}

list supprimerSommet(list l)
{
	list tmp;
	if(l==NULL)
	{
		return NULL;
	}
	else if(l->id != 0)
	{
		tmp = l->prev;
		tmp->next = l->next;
		l->next->prev = tmp;
		return l->next;		
	}
	else 
	{
		if(l->prev != NULL)
		{
			l->prev->id = 0;
			l->prev->next = l->next;
			tmp = l->prev;	
		}
		else if(l->next != NULL)
		{
			l->next->id=0;
			l->next->prev = NULL;
			tmp = l->next;
		}
		else tmp = NULL;
	}
	free(l);
	return tmp;	
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

