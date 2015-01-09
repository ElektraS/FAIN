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

list supprimerSommet(list l);

Color Color_new(float red, float green, float blue);

#endif