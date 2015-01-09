#ifndef PLOT_H
#define PLOT_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "droite.h"

void plot_point(int x, int y, Color c);

void plot_square(int x, int y, int size, Color c);

void afficher_points(list l, Color c);

void afficher_lignes(list l, Color current_color, Color select_color);

void tracerPixel(int x, int y, Color c);

void tracerDroite(int xa, int ya, int xb, int yb, Color current_color);

#endif