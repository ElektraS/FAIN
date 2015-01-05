#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "droite.h"
#include "evenement.h"

list _currentSummits = NULL;

void afficher_points(list l)
{
    if(l!=NULL)
    {
        glVertex2i(l->x, l->y);
        if(l->next!=NULL)
        {
            afficher_points(l->next);
        }  
    }
}

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);



    if(_currentSummits != NULL)
    {
        glBegin(GL_POINTS);
        glColor3ub(255,255,255);
        afficher_points(_currentSummits);
        glEnd();
    }

    glutSwapBuffers();
}

void mouse_CB(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
    {
        _currentSummits = nouveauSommet(_currentSummits,x,y);;
    }
    glutPostRedisplay(); 
}

int main(int argc, char **argv)
{
	int largeur = 400, hauteur = 400;
    int windowPosX = 100, windowPosY = 10;
    char *window_name = "Project";

    Color currentColor = Color_new(255, 255, 255);

    // Definition de la taille de la fenetre pour glut
    glutInitWindowSize(largeur,hauteur);

	// Definition de la position de la fenetre
    glutInitWindowPosition(windowPosX,windowPosY);

    // Allocation des buffers images (et autres eventuellement)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );

	// Initialisation de glut
    glutInit(&argc, argv);

	// Donner un nom à la fenetre
    glutCreateWindow(window_name);

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
    glutMouseFunc(mouse_CB);

	// Démarrage de la boucle d'attente des événements
    glutMainLoop();

	return 0;
}