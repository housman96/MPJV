#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Affichage.h"

using namespace std;

void Affichage::Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    // for (Particle part : list)
    // {
    //     glTranslatef(part.getPosition().getX(), part.getPosition().getY(), part.getPosition().getZ());
    // }
    glutSolidSphere(1.0, 50, 50);

    glPopMatrix();

    glutSwapBuffers();
}

/* la fonction "redim" est appelée : une fois a la creation de la fenêtre ;
 ensuite à chaque fois que la fenêtre est redimmensionnée
 width et height representent la taille de la fenêtre */
void Affichage::redim(int width, int height)
{
    glViewport(0, 0, width, height); /* Oups ! on reviendra sur la notion de viewport plus tard, on va simplement retenir ici que cette instruction veut dire :
                                    on affiche dans toute la fenêtre */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2., 2.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 10.0);
}

Affichage::Affichage(int argc, char **argv, Particle part)
{

    list.push_back(part);

    /* Initialisation de GLUT */

    glutInit(&argc, argv);

    /* Choix du type et d'affichage RGBA (mode couleur le plus fréquent), tampon de profondeur
    et d'un double buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    /* Taille et emplacement de la fenêtre */
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 100);

    /* Création de la fenêtre */
    glutCreateWindow("GLUTfenetre");
    glEnable(GL_DEPTH_TEST);

    /* Association des callback pour cette fenêtre */
    glutDisplayFunc(Affichage::Display);
    glutReshapeFunc(Affichage::redim);

    glutMainLoop(); /* On entre dans la boucle d'événements */
}
