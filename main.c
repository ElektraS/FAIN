#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "droite.h"
#include "plot.h"

#define APPEND 1
#define VERTEX 2
#define EDGE 3

list _currentSummits = NULL;

int id_nbr = 0;
int can_add_summit = 1;
int polygone_closed = 0;

Color _currentColor; 

int mode = APPEND;

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);



    if(_currentSummits != NULL)
    {
        glBegin(GL_POINTS);
        if(mode == VERTEX)
        {
            plot_square(_currentSummits->x, _currentSummits->y, 10, Color_new(255, 0, 0));
            plot_square(_currentSummits->x, _currentSummits->y, 15, Color_new(255, 0, 0));
        }
        glColor3ub(255,255,255);
        afficher_points(_currentSummits, _currentColor);
        afficher_lignes(_currentSummits, _currentColor);

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
    printf("key = %c = %d\n", key, key);
    if(mode == APPEND) // On est dans le mode append
    {
        if((key==99 || key==67) &&  nb_Summit(_currentSummits, 0) >= 2) //touche c : devient polygone
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
    else if (mode == VERTEX) // Quand on est dans le mode vertex
    {
        if((key == 8 || key == 127) && nb_Summit(_currentSummits, 0) >= 2) 
        //Si on appuie sur la touche suppr ou la touche delete à condition d'avoir au moins 2 sommets 
        {
            _currentSummits = supprimerSommet(_currentSummits);
        }
    }
    else if (mode == EDGE) // Quand on est dans le mode edge
    {
        /* code */
    }

    if(key== 97 || key ==65) mode = APPEND; 
    //Si le polygone est fermé on peut utiliser le mode VERTEX !
    if ((key == 118 || key == 86) && polygone_closed == 1) mode = VERTEX; 
    if ((key == 101 || key == 69) && polygone_closed == 1) mode = EDGE;
    if(key==27 || key==113) exit(0); // Touche Escape ou q : quitter le programme

    glutPostRedisplay();
}

void special_CB(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_PAGE_DOWN : 
               if( mode == VERTEX )
               {
                   
                    _currentSummits = previous_Summit(_currentSummits);
               }
               /*else if( MODE == EDGE )
               {
                current_courbe=prec_BCourbe(current_courbe);
               } */break;

        case GLUT_KEY_PAGE_UP : 
               if( mode == VERTEX )
               {
                    _currentSummits = next_Summit(_currentSummits);
               } 
               /*else if( MODE == EDGE )
               {
                current_courbe=next_BCourbe(current_courbe);
               } */break;


        //default : fprintf(stderr,"special_CB : %d : unknown key.\n",key);
    }
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
    glutSpecialFunc(special_CB);

	// Démarrage de la boucle d'attente des événements
    glutMainLoop();

	return 0;
}