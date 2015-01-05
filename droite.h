#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

typedef struct
{
	float _red, _green, _blue;
}Color;

void tracerPixel(int x, int y, Color c);

void tracerDroite(int xa, int ya, int xb, int yb, Color current_color);

Color Color_new(float red, float green, float blue);
