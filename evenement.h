#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
 
typedef struct element element;
struct element
{
    int x;
    int y;
    struct element *next;
};
 
typedef element* listc;