#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "scanline.h"
#include <math.h>



//--------------------------------------------
//calcul du x minimum d'un polygone
int calc_x_min(list l, int x)
{
	int xmin;
	xmin = x;
	if(l == NULL)
	{
		return xmin;
	}
	else if(xmin < (l->x))
	{
		return calc_x_min(l->next, xmin);
	}
	else
	{
		return calc_x_min(l->next, l->x);
	}
}


//-----------------------------------------------
//calcul du x maximum d'un polygone
int calc_x_max(list l, int x)
{
	int xmax;
	xmax = x;
	if(l == NULL)
	{
		return xmax;
	}
	else if(xmax > (l->x))
	{
		return calc_x_max(l->next, xmax);
	}
	else
	{
		return calc_x_max(l->next, l->x);
	}
}


//------------------------------------------
//calcul du y minimum d'un polygone
int calc_y_min(list l, int y)
{
	int ymin;
	ymin = y;
	if(l == NULL)
	{
		return ymin;
	}
	else if(ymin < (l->y))
	{
		return calc_y_min(l->next, ymin);
	}
	else
	{
		return calc_y_min(l->next, l->y);
	}
}


//------------------------------------------
//calcul du x maximum d'un polygone
int calc_y_max(list l, int y)
{
	int ymax;
	ymax = y;
	if(l == NULL)
	{
		return ymax;
	}
	else if(ymax > (l->y))
	{
		return calc_y_max(l->next, ymax);
	}
	else
	{
		return calc_y_max(l->next, l->y);
	}
}


//------------------------------------------------------------------------------------------
//intersection d'une ligne horizontale et d'un point
void intersection(int y, int x1, int y1, int x2, int y2, int *resx, int *resy)
{
	if( ( (y1<y) && (y2<y)) || ( (y1>y) && (y2>y)) ) //pas d'intersection avec le segment
	{
		*resx = -1;
		*resy = -1;
	}
	else if( (y1==y) && (y2==y)) //pas d'intersection, segment horizontal
	{
		*resx = -1;
		*resy = -1;
	}
	else if(y==y1) //intersection à une extrémité
	{
		*resx = x1;
		*resy = y;
	}

	else if(y==y2) //intersection à l'autre extrémité
	{
		*resx = x2;
		*resy = y;
	}

	else //intersection entre les extrémités
	{
		float dx = ((float) (x2-x1)) / ((float) (y2-y1));
		*resx = x1 + round( ((float) (y-y1)) * dx);
		*resy = y;
	}
}


//-------------------------------------------------------------
//pointeur sur le début de liste
list pointeur_debut(list l)
{
  	list res = l;
  	if(l != NULL)
  	{
  		while(res->prev != NULL)
  		{
  			res = res->prev;
  		}
  	}
  	return res;
}


//---------------------------------------------------------------------------------------
//détermination de l'appartenance d'un point à l'intérieur d'un polygone
int in_polygone(int x, int y, list l)
{
	int nb_intersection = 0; //nombre d'intersection avec les segments hors extremité
	float nb_inter_sommet = 0.0; //nombre d'intersection avec des sommets inférieurs de segment
	list temp = pointeur_debut(l); //temp est un pointeur initialisé en début de liste
	int xs;
	int ys;
	while((temp != NULL) && (temp->next != NULL))//tant que temp à un suivant 
	{ 
		//on cherche une intersection avec la première arête 
		intersection(y, temp->x, temp->y, temp->next->x, temp->next->y, &xs, &ys);
		if(xs != -1)//si l'intersection existe
		{
			if(xs == x) //sur le segment donc dans le polygone
			{
				return 1;
			}
			if(xs > x)
			{
				//on incrémente nb_inter_sommet si l'intersection est le sommet du bas 
				if((y == temp->y) && (y < temp->next->y)) nb_inter_sommet += 1.0;
				if((y == temp->next->y) && (y < temp->y)) nb_inter_sommet += 1.0;
				//si l'intersection n'est pas un sommet on incrémente nb_intersection
				else if ( !( (y == temp->next->y) || (y == temp->y) ) ) //sur la demi-droite dans le segment
				{
					nb_intersection++;
				}
			}
		}
		temp = temp->next; //on décale le pointeur d'un crant
	}
	//on renvoie 1 ssi on a compté un nombre impair d'intersections
	return (( (nb_intersection + (int)nb_inter_sommet) % 2) == 1);
}


//----------------------------------------------------------------------------------
//coloriage de polygone
void scanline(list l, Color c)
{
  	printf("in\n");

	//calcul du cadre
	int xmin = 0;
	calc_x_min(l, xmin);
	int xmax = 400;
	calc_x_max(l, xmax);
	int ymin = 0; 
	calc_y_min(l, ymin);
	int ymax = 400;
	calc_y_max(l,ymax);

	//coloriage du polygone dans le cadre
	printf("cadre : X:%d - %d Y: %d - %d\n",xmin ,xmax ,ymin ,ymax);
	int i,j;
	int x;
	int y;
	for(i=xmin ; i<=xmax ; i++)
	{
		for(j=ymin ; j<=ymax ; j++)
		{
			x=i;
			y=j;
			if( in_polygone(x, y, l) )
			{
				plot_point(i, j, c);
				printf("color affect %d %d\n",i,j);
			}
		}
	}
	printf("out\n");
}