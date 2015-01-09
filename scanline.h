#ifndef SCANLINE_H
#define SCANLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "droite.h"
#include "plot.h"

int calc_x_min(list l, int x);
int calc_x_max(list l, int x);
int calc_y_min(list l, int y);
int calc_y_max(list l, int y);

void intersection(int y, int x1, int y1, int x2, int y2, int *resx, int *resy);
list pointeur_debut(list l);
int in_polygone(int x, int y, list l);

#endif