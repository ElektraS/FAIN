#include "plot.h"

void tracerPixel(int x, int y, Color c)
{
	glBegin(GL_POINTS);
	glColor3f(c._red, c._green, c._blue);
	glVertex2i(x,y);
	glEnd();
}

//algorithme de Bresenham
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
				tracerPixel(currX, currY, current_color);
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
				tracerPixel(currX, currY, current_color);
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

void plot_point(int x, int y, Color c)
{
	glColor3f(c._red,c._green,c._blue);
	glVertex2i(x, y);
}

void afficher_points(list l, Color c)
{
    if(l!=NULL)
    {
        plot_point(l->x, l->y, Color_new(c._red,c._green,c._blue));
        if(l->next!=NULL)
        {
            if(l->id!=0) afficher_points(l->next, c);
        }  
    }
}

void afficher_lignes(list l, Color c)
{
    if(l!=NULL)
    {
        if(l->next != NULL)
        {
            if(l->id!=0)
            {
                tracerDroite(l->x, l->y, l->next->x, l->next->y, c);
                afficher_lignes(l->next, c);  
            }   
            else if(l->next !=NULL) tracerDroite(l->x, l->y, l->next->x, l->next->y, c);        
        }
    }
}

void plot_square(int x, int y, int size, Color c)
{
	int i = 0;
	for( i = x - size/2; i <=  x + size/2 ; i++)
	{
		plot_point(i, y+size/2, c);
		plot_point(i, y-size/2, c);
	}
	for( i = y - size/2; i <= y + size/2 ; i++)
	{
		plot_point(x-size/2, i, c);
		plot_point(x+size/2, i, c);
	}

}
