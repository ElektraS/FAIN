#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "droite.h"
#include "evenement.h"

Color Color_new(float red, float green, float blue)
{
	Color c;
	c._red = red;
	c._green = green;
	c._blue = blue;
	return c;
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