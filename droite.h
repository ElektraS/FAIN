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

void tracerPixel(int x, int y, Color c);

void tracerDroite(int xa, int ya, int xb, int yb, Color current_color);

Color Color_new(float red, float green, float blue);

void afficher_points(list l);

void afficher_lignes(list l);
