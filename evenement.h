#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
 
typedef struct element element;
struct element
{
    int x;
    int y;
    struct element *next;
};
 
typedef element* listc;

listc nouveauSommet(listc l, int x, int y);

void firstElement(listc l, int x, int y);

void mouseClick(int button, int state, int x, int y, listc l);

void keyboardC(unsigned char key, listc l);