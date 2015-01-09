#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "droite.h"
#include "plot.h"

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
		if(l->prev != NULL && l->next != NULL)
		{
			tmp = l->prev;
			tmp->next = l->next;
			l->next->prev = tmp;
			tmp = l->next;	
		}	
		else if(l->prev == NULL)
		{
			l->next->prev = NULL;
			tmp = l->next;
		}
		else 
		{
			l->prev->next = l->next;
			tmp = l->prev;
		}		
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

list add_summit(list l, int x, int y)
{
	list tmp = malloc(sizeof(struct element));
	if(l==NULL)
	{
		return nouveauSommet(l, x, y);
	}

	tmp->x = x;
	tmp->y = y;
	if(l != NULL && l->next != NULL)
	{
		tmp->next = l->next;
		tmp->prev = l;
		l->next = tmp;
		tmp->next->prev=tmp;	
	}	
	else
	{
		tmp->prev = l;
	}
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

list move_left(list l)
{
	l->x -= 1;
	return l;
}

list move_right(list l)
{
	l->x += 1;
	return l;
}

list move_top(list l)
{
	l->y -= 1;
	return l;
}

list move_bottom(list l)
{
	l->y += 1;
	return l;
}

void select_edge(list l, Color select_color, Color current_color)
{
	if(l != NULL)
	{
		if(l->next != NULL)
		{
			tracerDroite(l->x, l->y, l->next->x, l->next->y, select_color);
			if(l->prev != NULL) tracerDroite(l->x, l->y, l->prev->x, l->prev->y, current_color);
		}
		else if(l->prev != NULL)
		{
			tracerDroite(l->x, l->y, l->next->x, l->next->y, current_color);
		}
	} 

		
}