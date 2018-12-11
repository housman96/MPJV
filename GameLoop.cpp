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

GameLoop::GameLoop(int argc, char** argv, GameObject& part)
{
	GameLoop::world.push_back(&part);
	GameLoop(argc, argv);
}

GameLoop::GameLoop(int argc, char** argv, GameObject* part)
{
	GameLoop::world.push_back(part);
	GameLoop(argc, argv);
}

GameLoop::GameLoop(int argc, char** argv, vector<GameObject*>& objects)
{
	GameLoop::world = objects;
	GameLoop(argc, argv);
}

GameLoop::GameLoop(int argc, char** argv, vector<GameObject*>& objects, vector<Primitive*>& prim)
{
	GameLoop::world = objects;
	GameLoop::primitives = prim;
	GameLoop(argc, argv);
}

GameLoop::~GameLoop()
{
	if (world.data()) {
		delete[] & world;
	}
	if (listContact.data()) {
		delete[] & listContact;
	}
	if (listContactGenerator.data()) {
		delete[] & listContactGenerator;
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
	//GameLoop::drawGround();

	//Affichage des particules
	for (GameObject* part : GameLoop::world) {
		part->draw();
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
	gluLookAt(0., 10.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/*Eclairage*/
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//GLfloat Lambiant[4] = { 0.4, 0.4, 0.4, 10.0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, Lambiant);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.7, 1.0, 100.0);
}


bool crashDone = false;
void GameLoop::TimerPhysicsLoop(int value)
{
	// Lancement du timer physique
	glutTimerFunc(deltaT / 10.f, TimerPhysicsLoop, 0);

	// Récupération du temps écoulé
	double now = glutGet(GLUT_ELAPSED_TIME);
	double timeElapsedMs = (now - lastLoopTime);
	lastLoopTime = now;



	if (timeElapsedMs > deltaT / 10) {
		timeElapsedMs = deltaT / 10;
	}
	timeAccumulatedMs += timeElapsedMs;

	//Ajout des contacts
	for (int i = 0; i < GameLoop::listContactGenerator.size(); i++) {
		GameLoop::listContactGenerator[i]->addContact();
	}

	//Détection des contatcts
	//for (int i = 0; i < GameLoop::world.size(); i++) {
	//	for (int j = i + 1; j < GameLoop::world.size(); j++) {
	//		if (GameLoop::world[i]->t == Type::Particle && GameLoop::world[j]->t == Type::Particle) {
	//			float dist = Vect3::dist(((Particle*)GameLoop::world[i])->getPosition(), ((Particle*)GameLoop::world[j])->getPosition());
	//			float distColision = ((Particle*)GameLoop::world[i])->getRadius() + ((Particle*)GameLoop::world[j])->getRadius();
	//			if (dist < distColision) {
	//				GameLoop::listContact.push_back(new ParticleContact(((Particle*)GameLoop::world[i]), ((Particle*)GameLoop::world[j]), 0.5));
	//			}
	//		}
	//	}
	//}
	Vect3 *tab = new Vect3[8];
	CollisionData data = CollisionData();
	tab[0] = Vect3(-10.f, -10.f, -10.f);
	tab[1] = Vect3(10.f, -10.f, -10.f);
	tab[2] = Vect3(-10.f, 10.f, -10.f);
	tab[3] = Vect3(10.f, 10.f, -10.f);
	tab[4] = Vect3(-10.f, -10.f, 10.f);
	tab[5] = Vect3(10.f, -10.f, 10.f);
	tab[6] = Vect3(-10.f, 10.f, 10.f);
	tab[7] = Vect3(10.f, 10.f, 10.f);
	Octree o = Octree(tab, 3, 10);

	for (int i = 0; i < GameLoop::world.size(); i++) {
		o.insert(GameLoop::world[i]);
	}
	for (int i = 0; i < GameLoop::world.size(); i++) {
		vector<GameObject*> tabO = o.retrieve(GameLoop::world[i]);
		for (size_t j = 0; j < tabO.size(); j++) {
			if (tabO[j] != GameLoop::world[i]) {
				CollisionData::generateContact(Box(), Plan(), data);
			}
		}
	}


	//Résolution des contacts
	GameLoop::resolver.setIter(GameLoop::listContact.size());
	GameLoop::resolver.setVector(GameLoop::listContact);
	GameLoop::resolver.resolveContact();
	for (std::vector< ParticleContact* >::iterator it = GameLoop::listContact.begin(); it != GameLoop::listContact.end(); ++it) {
		delete (*it);
	}
	GameLoop::listContact.clear();

	////ajout des forces pour le scénario crash
	//if (timeAccumulatedMs >= 1000 && !crashDone) {

	//	Rigidbody* car = (Rigidbody*)world[0];
	//	Rigidbody* car2 = (Rigidbody*)world[1];
	//	car->addForceAtPoint(Vect3(-50000, 0, 0), Vect3(0, 0, 0));
	//	car2->addForceAtPoint(Vect3(50000, 0, 0), Vect3(0, 0, 0));
	//	crashDone = true;

	//}


	// Prise en compte des forces
	for (RegisterForce::ForceRecord record : records) {
		record.pfg->updateForce(record.go, timeElapsedMs / 1000.);
	}

	//Mise à jour de la physique
	for (GameObject *go : GameLoop::world) {
		go->update(timeElapsedMs / 1000.);
	}

}

void GameLoop::TimerDrawLoop(int value)
{
	glutPostRedisplay();
	glutTimerFunc(deltaT, TimerDrawLoop, 0);
}


// ============================================================
// METHODES DE DESSIN
// ============================================================

void GameLoop::drawGround()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3b(50, 50, 50);
	glVertex3f(100, 0, 100);
	glVertex3f(100, 0, -100.0);
	glVertex3f(-100, 0, -100.0);
	glVertex3f(-100, 0., 100.0);
	glEnd();
	glPopMatrix();
}
