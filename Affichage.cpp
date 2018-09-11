#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Affichage.h"

using namespace std;


// ============================================================
// METHODE GLUT
// ============================================================

void Affichage::Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	cout << "Display" << Affichage::list.size() << endl;
	for (Particle part : Affichage::list) {
		glPushMatrix();
		glTranslatef(part.getPosition().getX(), part.getPosition().getY(), part.getPosition().getZ());
		glutSolidSphere(1.0, 50, 50);
		glPopMatrix();
	}

	glPopMatrix();

	glutSwapBuffers();
}

/*  La fonction "redim" est appelée :
 *   une fois a la creation de la fenêtre ;
 *  ensuite à chaque fois que la fenêtre est redimmensionnée
 *  width et height representent la taille de la fenêtre
 */
void Affichage::redim(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2., 2.0, 2.0,
	          0.0, 0.0, 0.0,
	          0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.0, 1.0, 10.0);
}

void Affichage::idle(void) {
	double now = glutGet(GLUT_ELAPSED_TIME);
	double timeElapsedMs = ((now - Affichage::lastLoopTime) * 1000) / (CLOCKS_PER_SEC);
	Affichage::timeAccumulatedMs += timeElapsedMs;

	while (Affichage::timeAccumulatedMs >= Affichage::T) {
		for (Particle p : Affichage::list) {
			Vect3D grav = new Vect3D(0, -Affichage::G, 0);
			p = new Particle(Vect3D(0, 0, 0), Vect3D(1, 1, 0), 10);
			p.setDamping(Affichage::D);

			for (int i = 0; i < 10; i++) {
				p.applyForce(grav);
				p.update(Affichage::T);
			}
		}
		glutPostRedisplay();
	}

	Affichage::lastLoopTime = now;
}

void Affichage::refresh(void) {
	glutPostRedisplay();
}


// ============================================================
// CONSTRUCTEURS
// ============================================================

Affichage::Affichage(int argc, char ** argv, Particle part) {
	Affichage::list.push_back(part);

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
	glutIdleFunc(Affichage::idle);

	glutMainLoop(); /* On entre dans la boucle d'événements */
}

Affichage::Affichage(int argc, char ** argv) {
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

Affichage::Affichage(int argc, char ** argv, vector<Particle> list) {
	Affichage::list = list;
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

Affichage::~Affichage() {
	if (list.data())
		delete[] & list;
}


// ============================================================
// ASCESSEUR
// ============================================================

vector<Particle> Affichage::getList() {
	return Affichage::list;
}

void Affichage::setList(vector<Particle> newList) {
	Affichage::list = newList;
}
