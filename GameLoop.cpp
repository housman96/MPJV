#include "GameLoop.h"
#include "RegisterForce.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS ET DESTRUCTEUR
// ============================================================

GameLoop::GameLoop(int argc, char** argv)
{
	/* Initialisation de GLUT */
	glutInit(&argc, argv);

	/* Choix du type et d'affichage RGBA (mode couleur le plus fréquent), tampon
	 de profondeur et d'un double buffer */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	/* Taille et emplacement de la fenêtre */
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);

	/* Création de la fenêtre */
	glutCreateWindow("MPJV");
	glEnable(GL_DEPTH_TEST);

	/* Association des callback pour cette fenêtre */
	glutDisplayFunc(GameLoop::display);
	glutReshapeFunc(GameLoop::redim);
	TimerPhysicsLoop(0);
	TimerDrawLoop(0);

	glutMainLoop(); /* On entre dans la boucle d'événements */
}

GameLoop::GameLoop(int argc, char** argv, Particle& part)
{
	GameLoop::world.push_back(&part);
	GameLoop(argc, argv);
}

GameLoop::GameLoop(int argc, char** argv, Particle* part)
{
	GameLoop::world.push_back(part);
	GameLoop(argc, argv);
}

GameLoop::GameLoop(int argc, char** argv, vector<Particle*>& list)
{
	GameLoop::world = list;
	GameLoop(argc, argv);
}

GameLoop::GameLoop(int argc, char** argv, vector<Particle*>* list)
{
	GameLoop::world = *list;
	GameLoop(argc, argv);
}

GameLoop::~GameLoop()
{
	if (world.data()) {
		delete[] & world;
	}
}


// ============================================================
// CALLBACKS D'AFFICHAGE
// ============================================================

void GameLoop::display()
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
	for (Particle part : GameLoop::world) {
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
void GameLoop::redim(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 1.0, 90.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/*Eclairage*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat Lambiant[4] = { 0.4, 0.4, 0.4, 10.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Lambiant);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.7, 1.0, 100.0);
}

void GameLoop::TimerPhysicsLoop(int value)
{
	// Récupération du temps écoulé
	double now = glutGet(GLUT_ELAPSED_TIME);
	double timeElapsedMs = (now - lastLoopTime);
	lastLoopTime = now;

	// Lancement du timer physique
	glutTimerFunc(deltaT / 10.f, TimerPhysicsLoop, 0);

	if (timeElapsedMs > deltaT / 10.) {
		timeElapsedMs = deltaT / 10.;
	}

	// Ajout des contacts
	for (int i = 0; i < GameLoop::listContactGenerator.size(); i++) {
		GameLoop::listContactGenerator[i]->addContact();
	}

	// Détection des contatcts
	for (int i = 0; i < GameLoop::world.size(); i++) {
		for (int j = i + 1; j < GameLoop::world.size(); j++) {
			float dist = Vect3D::dist(GameLoop::world[i]->getPosition(), GameLoop::world[j]->getPosition());
			float distColision = GameLoop::world[i]->getRadius() + GameLoop::world[j]->getRadius();
			if (dist < distColision) {
				GameLoop::listContact.push_back(new ParticleContact(GameLoop::world[i], GameLoop::world[j], 0.5));
			}
		}
	}

	// Résolution des contacts
	GameLoop::resolver.setIter(GameLoop::listContact.size());
	GameLoop::resolver.setVector(GameLoop::listContact);
	GameLoop::resolver.resolveContact();
	GameLoop::listContact.clear();

	// Prise en compte des forces
	for (RegisterForce::ForceRecord record : records) {
		record.pfg->updateForce(record.p, timeElapsedMs / 1000.);
	}

	// Mise à jour de la physique
	for (Particle *p : GameLoop::world) {
		p->rebound();
		p->update(timeElapsedMs / 1000.);
		p->clearAccum();
	}

}

void GameLoop::TimerDrawLoop(int value)
{
	glutPostRedisplay();
	glutTimerFunc(deltaT, TimerDrawLoop, 0);
}
