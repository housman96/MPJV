#include "Affichage.h"
#include "RegisterForce.h"

using namespace std;

// ============================================================
// CONSTRUCTEURS
// ============================================================

Affichage::Affichage(int argc, char **argv)
{
	/* Initialisation de GLUT */
	glutInit(&argc, argv);

	/* Choix du type et d'affichage RGBA (mode couleur le plus fréquent), tampon de profondeur
	   et d'un double buffer */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	/* Taille et emplacement de la fenêtre */
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(200, 100);

	/* Création de la fenêtre */
	glutCreateWindow("GLUTfenetre");
	glEnable(GL_DEPTH_TEST);

	/* Association des callback pour cette fenêtre */
	glutDisplayFunc(Affichage::display);
	glutReshapeFunc(Affichage::redim);
	glutIdleFunc(Affichage::idle);

	glutMainLoop(); /* On entre dans la boucle d'événements */
}

Affichage::Affichage(int argc, char **argv, Particle part)
{
	Affichage::list.push_back(part);
	Affichage(argc, argv);
}

Affichage::Affichage(int argc, char **argv, vector<Particle> list)
{
	Affichage::list = list;
	Affichage(argc, argv);
}

Affichage::~Affichage()
{
	if (list.data())
	{
		delete[] & list;
	}
}

// ============================================================
// ASCESSEUR
// ============================================================

vector<Particle> Affichage::getList()
{
	return Affichage::list;
}

void Affichage::setList(vector<Particle> newList)
{
	Affichage::list = newList;
}

// ============================================================
// CALLBACKS D'AFFICHAGE
// ============================================================

void Affichage::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	// Affichage du sol
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3b(50, 50, 50);
	glVertex3f(100, 0, 100);
	glVertex3f(100, 0, -100.0);
	glVertex3f(-100, 0, -100.0);
	glVertex3f(-100, 0., 100.0);
	glEnd();
	glPopMatrix();

	// Affichage des particules
	for (Particle part : Affichage::list)
	{
		glPushMatrix();
		glColor3b(0, 0, 50);
		glTranslatef(part.getPosition().getX(), part.getPosition().getY(), part.getPosition().getZ());
		glutSolidSphere(part.getRadius(), 50, 50);
		glPopMatrix();
	}

	glutSwapBuffers();
}

/*  La fonction "redim" est appelée :
 *    une fois a la creation de la fenêtre ;
 *    ensuite à chaque fois que la fenêtre est redimmensionnée
 *  width et height representent la taille de la fenêtre
 */
void Affichage::redim(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 1.0, 90.0,
			  0.0, 0.0, 0.0,
			  0.0, 1.0, 0.0);

	/*Eclairage*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat Lambiant[4] = {0.4, 0.4, 0.4, 10.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, Lambiant);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.7, 1.0, 100.0);
}

/*La fonction IDLE calcul en arrière plan, toute la physique du moteur*/
void Affichage::idle(void)
{
	double now = glutGet(GLUT_ELAPSED_TIME);
	double timeElapsedMs = (now - lastLoopTime);
	timeAccumulatedMs += timeElapsedMs;

	if (timeAccumulatedMs >= deltaT)
	{
		glutPostRedisplay();
		for (RegisterForce::ForceRecord record : r)
		{

			record.pfg->updateForce(record.p, deltaT / 1000.);
		}
		for (Particle &p : Affichage::list)
		{
			p.log();
			p.rebound();
			p.update(deltaT / 1000.);

			p.clearAccum();
		}

		timeAccumulatedMs = 0.;
	}

	lastLoopTime = now;
}
