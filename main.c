#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "droite.h"
#include "plot.h"

list _currentSummits = NULL;

int id_nbr = 0;
int can_add_summit = 1;
int polygone_closed = 0;

Color _currentColor; 

int mode = 1;

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);



    if(_currentSummits != NULL)
    {
        glBegin(GL_POINTS);
        glColor3ub(255,255,255);
        afficher_points(_currentSummits, _currentColor);
        afficher_lignes(_currentSummits, _currentColor);
        plot_square(_currentSummits->x, _currentSummits->y, 10, Color_new(255, 0, 0));
        glEnd();
    }

    glutSwapBuffers();
}

void mouse_CB(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON && can_add_summit == 1 && mode == 1)
    {
        _currentSummits = nouveauSommet(_currentSummits,x,y);
    }
    glutPostRedisplay(); 
}

void keyboard_CB(unsigned char key, int x, int y)
{
//    printf("key = %c = %d\n", key, key);
    if(mode == 1) // On est dans le mode append
    {
        if(key==99 || key==67) //touche c : devient polygone
        {
            if(polygone_closed==0)
            {
                list firstElem;
                firstElem = firstElement(_currentSummits);
                if(firstElem != NULL)
                {
                    firstElem->next = _currentSummits;
                    _currentSummits->prev = firstElem;
                }   
                polygone_closed = 1;
                can_add_summit = 0;   
            }
            else
            {
                list firstElem;
                firstElem = firstElement(_currentSummits);
                if(firstElem != NULL)
                {
                    firstElem->next = NULL;
                    _currentSummits ->prev = NULL;
                }
                polygone_closed = 0;
                can_add_summit = 1;
            }
        }
    }
    else if (mode == 2) // Quand on est dans le mode vertex
    {

    }
    else if (mode == 3) // Quand on est dans le mode edge
    {
        /* code */
    }

    if(key== 97 || key ==65) mode = 1;
    if (key == 118 || key == 86) mode = 2;
    if (key == 101 || key == 69) mode = 3;
    if(key==27 || key==113) exit(0); // Touche Escape ou q : quitter le programme

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
	int largeur = 400, hauteur = 400;
    int windowPosX = 100, windowPosY = 10;
    char *window_name = "Project";
    _currentColor = Color_new(255, 255, 255);

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
    glutKeyboardFunc(keyboard_CB);

	// Démarrage de la boucle d'attente des événements
    glutMainLoop();

	return 0;
}