#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
 
typedef struct element* list;
struct element
{
    int x;
    int y;
    list next;
};

typedef struct point point;
struct point
{
	int x;
	int y;
};

list nouveauSommet(list l, int x, int y);

point firstElement(list l);

void keyboardC(unsigned char key, list l);