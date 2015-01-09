#ifndef SCANLINE_H
#define SCANLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "droite.h"

int calc_x_min(list l);
int calc_x_max(list l);
int calc_y_min(list l);
int calc_y_max(list l);