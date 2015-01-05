#include "droite.h"
#include "evenement.h"


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
		newElement->id = newElement->next->id + 1;
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

