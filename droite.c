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

void tracerPixel(int x, int y, Color c)
{
	glBegin(GL_POINTS);
	glColor3f(c._red, c._green, c._blue);
	glVertex2i(x,y);
	glEnd();
}

void tracerDroite(int xa, int ya, int xb, int yb, Color current_color)
{
	int count;
	int currY;
	int currX;
	int dX = (xb-xa);
	int dY = (yb-ya);

	//1er et 2ème octants
	if(dX>=0 && dY>=0)
	{ //1er octant
		if(dX>dY)
		{
			count = dX;
			currY = ya;
			for(currX=xa; currX<=xb; currX++)
			{
				tracerPixel(currX, currY, current_color);
				if(count>0)
				{
					count = count - 2*dY;
				}
				else
				{
					currY++;
					count = count - 2*dY + 2*dX;
				}
			}
		}
		//2ème octant
		else
		{
			count = dY;
			currX = xa;
			for(currY=ya; currY<=yb; currY++)
			{
				tracerPixel(currX, currY, current_color);
				if(count>0)
				{
					count = count - 2*dX;
				}
				else
				{
					currX++;
					count = count - 2*dX + 2*dY;
				} 
			} 
		}
	} 

	//3ème et 4ème octants
	else if(dX<0 && dY>=0)
		 {
		 //3ème octant
		 if(dY>-dX)
		 {
		 	count = dY;
		 	currX = xa;
		 	for(currY=ya; currY<=yb; currY++)
		 	{
		 		tracerPixel(currX, currY, current_color);
		 		if(count<0)
		 		{
		 			count = count - 2*dX;
		 		}
		 		else
		 		{
		 			currX--;
		 			count = count - 2*dX - 2*dY;
		 		}
		 	}
		 }
		 //4ème octant
		 else
		 {
		 	count = dX;
		 	currY = ya;
		 	for(currX=xa; currX>=xb; currX--)
		 	{
		 		tracerPixel(currX, currY, current_color);
		 		if(count<0)
		 		{
		 			count = count + 2*dY;
		 		}
		 		else
		 		{
		 			currY++;
		 			count = count + 2*dY + 2*dX;
		 		}
		 	}
		 }
	}

	//5ème et 6ème octants
	else if(dX<0 && dY<0)
		 {
		 //5ème octant
		 if(-dX>-dY)
		 {
		 	count = dX;
		 	currY = ya;
		 	for(currX=xa; currX>=xb; currX--)
		 	{
		 		tracerPixel(currX, currY, current_color);
		 		if(count<0)
		 		{
		 			count = count - 2*dY;
		 		}
		 		else
		 		{
		 			currY--;
		 			count = count - 2*dY + 2*dX;
		 		}
		 	}
		 }
		 //6ème octant
		 else
		 {
		 	count = dY;
		 	currX = xa;
		 	for(currY=ya; currY>=yb; currY--)
		 	{
		 		tracerPixel(currX, currY, current_color);
		 		if(count<0)
		 		{
		 			count = count - 2*dX;
		 		}
		 		else
		 		{
		 			currX--;
		 			count = count - 2*dX + 2*dY;
		 		}
		 	}
		 }
	}

	//7ème et 8ème octants
	else /*if(dX>=0 && dY<0)*/
	{
	//7ème octant
		if(-dY>dX)
		{
			count = dY;
			currX = xa;
			for(currY=ya; currY>=yb; currY--)
			{
				tracerPixel(currX, currY, Color_new(255,255,255));
				if(count>0)
				{
					count = count - 2*dX;
				}
				else
				{
					currX++;
					count = count - 2*dX - 2*dY;
				}
			}
		}
		//8ème octant
		else
		{
			count = dX;
			currY = ya;
			for(currX=xa; currX<=xb; currX++)
			{
				tracerPixel(currX, currY, Color_new(255,255,255));
				if(count>0)
				{
					count = count + 2*dY;
				}
				else
				{
					currY--;
					count = count + 2*dY + 2*dX;
				}
			}
		}
	}
}

void afficher_points(list l)
{
    if(l!=NULL)
    {
        glVertex2i(l->x, l->y);
        if(l->next!=NULL)
        {
            if(l->id!=0) afficher_points(l->next);
        }  
    }
}

void afficher_lignes(list l)
{
    if(l!=NULL)
    {
        if(l->next != NULL)
        {
            if(l->id!=0)
            {
                tracerDroite(l->x, l->y, l->next->x, l->next->y, Color_new(255,255,255));
                afficher_lignes(l->next);  
            }   
            else if(l->next !=NULL) tracerDroite(l->x, l->y, l->next->x, l->next->y, Color_new(255,255,255));        
        }
    }
}
