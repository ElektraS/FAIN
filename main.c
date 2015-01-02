#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "droite.h"
#include "evenement.h"

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(20,0,0);

    glBegin(GL_POINTS);
    glColor3ub(255,255,255);
    glVertex2i(200,40);
    glVertex2i(40,200);
    glEnd();
    glutSwapBuffers();
}

void int main(int argc, char const *argv[])
{
	int largeur = 400, hauteur = 400;
    int windowPosX = 100, windowPosY = 10;

    // Definition de la taille de la fenetre pour glut
    glutInitWindowSize(largeur,hauteur);

	// Definition de la position de la fenetre
    glutInitWindowPosition(windowPosX,windowPosY);

    // Allocation des buffers images (et autres eventuellement)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );

	// Initialisation de glut
    glutInit(&argc, argv);

	// Donner un nom à la fenetre
    glutCreateWindow(argv[0]);

	// Definition de la taille de la fenêtre pour OpenGL
    glViewport(0, 0, largeur, hauteur);

	// Initialisation des matrices de modelisation et de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// On n'a pas de projection perspective mais orthogonal
    glOrtho(0,largeur,hauteur,0,-1,1);

	// Definition de display_CB comme fonction à appeler pour l'affichage
    glutDisplayFunc(display_CB);

	// Démarrage de la boucle d'attente des événements
    glutMainLoop();

	return 0;
}