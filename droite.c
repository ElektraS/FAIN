#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "droite.h"
#include "plot.h"
#include <math.h>

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
	list res/* = malloc(sizeof(struct element))*/;
	list tmp;
	if(l==NULL)
	{
		return nouveauSommet(l, x, y);
	}

	/*tmp->x = x;
	tmp->y = y;*/
	if(l != NULL && l->next != NULL)
	{
		/*if(l->id == 0) 
		{
			l->id = 1;
			tmp->id =0;
		}
		tmp->next = l->next;
		tmp->prev = l;
		l->next->prev = tmp;
		l->next = tmp;*/
		tmp = l->prev;
		res =nouveauSommet(l, x,y);
		res->prev = tmp;
		tmp->next = res;

	
	}	
	else
	{
		//tmp->prev = l;
	}
	return res;	
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

list closestVertex(list l, int x, int y, list res, double sdis)
{
	if(l ==NULL)
	{
		return res;
	}
	else if(l->id != 0)
	{
		if (distanceBetweenPoints(l->x, l->y, x, y) < sdis)
		{
			return closestVertex(l->next, x, y, l, distanceBetweenPoints(l->x, l->y, x, y));
		}
		else return closestVertex(l->next, x, y, res, sdis);
	}
	else 
	{
		if (distanceBetweenPoints(l->x, l->y, x, y) < sdis)
		{
			return l;
		}
		else 
		{
			return res;
		}
	}
}

double distanceBetweenPoints(int xa, int ya, int xb, int yb)
{
	double tmp = 0;
    tmp =  pow(xb - xa, 2) + pow(yb - ya, 2);
    return sqrt(tmp);
}

list MoveSummit(list l, list target)
{
	if(l == NULL)
	{
		return NULL;
	}
	else if (l != target)
	{
		return MoveSummit(next_Summit(l), target);
	}
	else return target;
}

list closestEdge(list l, int x, int y)
{

	if(l ==NULL)
	{
		return l;
	}
	if(distanceBetweenPoints(x, y, l->next->x, l->next->y)>distanceBetweenPoints(x, y, l->prev->x, l->prev->y))
	{
		return l->prev;
	}
	else return l->next;
}