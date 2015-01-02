#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "droite.h"
#include "evenement.h"

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}