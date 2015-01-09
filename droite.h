#ifndef DROITE_H
#define DROITE_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

typedef struct
{
	float _red, _green, _blue;

}Color;

typedef struct element* list;
struct element
{
	int id;
    int x;
    int y;
    list next;
    list prev;
};


typedef struct point point;
struct point
{
	int x;
	int y;
};


list nouveauSommet(list l, int x, int y);

list firstElement(list l);

int nb_Summit(list l, int a);

list supprimerSommet(list l);

list add_summit(list l, int x, int y);

Color Color_new(float red, float green, float blue);

list next_Summit(list l);

list previous_Summit(list l);

list move_left(list l);

list move_right(list l);

list move_top(list l);

list move_bottom(list l);

void select_edge(list l, Color select_color, Color current_color);

#endif