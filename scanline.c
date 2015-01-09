#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "scanline.h"
#include <math.h>

#include "droite.h"
#include "plot.h"



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


//---------------------------------------------------------------------------------------
//détermination de l'appartenance d'un point à l'intérieur d'un polygone
int in_polygone(int x, int y, list l)
{
	int nb_intersection = 0; //nombre d'intersection avec les segments hors extremité
	float nb_inter_sommet = 0.0; //nombre d'intersection avec des sommets inférieurs de segment
	list temp = firstElement(l); //temp est un pointeur initialisé en début de liste
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
  	list temp;
  	temp = firstElement(l);
	//calcul du cadre
	int xmin = 400;
	int xmax = 0;
	int ymin = 400;
	int ymax = 0;

	while(temp != NULL && temp->id != 0)
	{
		if(temp->x < xmin)
		{
			xmin = temp->x;
		}
		if(temp->x > xmax)
		{
			xmax = temp->x;
		}
		if(temp->y < ymin)
		{
			ymin = temp->y;
		}
		if(temp->y > ymax)
		{
			ymax = temp->y;
		}
		temp=temp->next;
	}

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


//-----------------------------------------------------------------------------------------------------
//tableau des intersections du polygone avec une droite horizontale
//renvoie le nombre d'intersection trouvé (forcément paire si le polygone est fermé) 
int intersection_table(Table *t,int y,list l)
{
	int nb_intersection = 0; //initialisation du nombre d'intersections à 0
	list temp = firstElement(l); //pointeur en début de liste
	int xs,ys;
	while((temp != NULL) && (temp->next != NULL)) //tant qu'il y a un suivant non vide
	{
		intersection(y, temp->x, temp->y, temp->next->x, temp->next->y, &xs, &ys); //calcul de la première intersection
		if(xs != -1) //si elle existe
		{
			if((y == temp->y) && (y < temp->next->y))
			{
				(*t)[nb_intersection] = xs; //ajout au tableau
				nb_intersection++; //sommet inf
			}
			else if((y == temp->next->y) && (y < temp->y))
			{
				(*t)[nb_intersection] = xs; //ajout au tableau
				nb_intersection++; //sommet inf
			}
			else if ( !( (y == temp->next->y)||(y == temp->y) ) )
			{
				(*t)[nb_intersection] = xs; //ajout au tableau
				nb_intersection++; //sur la demi-droite dans le segment
			}
		}
		temp = temp->next; //décalage du pointeur 
	}
	return nb_intersection;
}


//---------------------------------------------------------
//tri croissant naif des élément entre deb et size-1
void T_tri(Table *t,int deb,int size)
{
	if(deb < size-1){

		int temp,i;
		for(i=deb ; i<size ; i++)
		{
			if((*t)[deb] > (*t)[i])
			{
				temp = (*t)[deb];
				(*t)[deb] = (*t)[i];
				(*t)[i] = temp;
			}
		}
		T_tri(t, deb+1, size);

	}
}



//coloriage de polygone
void scanline2(list l, Color c)
{
  	printf("in\n");
  	list temp = firstElement(l);
	//calcul du cadre
	int xmin = 400;
	int xmax = 0;
	int ymin = 400; 
	int ymax = 0;
	while(temp != NULL && temp->id != 0)
	{
		if(temp->x < xmin)
		{
			xmin = temp->x;
		}
		if(temp->x > xmax)
		{
			xmax = temp->x;
		}
		if(temp->y < ymin)
		{
			ymin = temp->y;
		}
		if(temp->y > ymax)
		{
			ymax = temp->y;
		}
		temp = temp->next;
	}
	//coloriage du polygone dans le cadre
	printf("cadre : X:%d - %d Y: %d - %d\n", xmin, xmax, ymin, ymax);
	int n,i,j;
	Table TAB = malloc(ymax+1);
	for(j=ymin ; j<=ymax ; j++)
		{
			n = intersection_table(&TAB,j,l);
			T_tri(&TAB,0,n);
			for(i=0 ; i<n-1 ; i=i+2)
			{
				tracerDroite(TAB[i], j, TAB[i+1], j, c);
			}
		}
	printf("out\n");
}
