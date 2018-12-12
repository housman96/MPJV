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
	GameLoop::drawGround();

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
	gluLookAt(0., 3.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/*Eclairage*/
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//GLfloat Lambiant[4] = { 0.4, 0.4, 0.4, 10.0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, Lambiant);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.7, 1.0, 100.0);
}

void GameLoop::TimerPhysicsLoop(int value)
{
	// Lancement du timer physique
	glutTimerFunc(deltaT / 10.f, TimerPhysicsLoop, 0);

	if (GameLoop::stop == false) {

		// Récupération du temps écoulé
		double now = glutGet(GLUT_ELAPSED_TIME);
		double timeElapsedMs = (now - lastLoopTime);
		lastLoopTime = now;

		if (timeElapsedMs > deltaT / 10) {
			timeElapsedMs = deltaT / 10;
		}
		timeAccumulatedMs += timeElapsedMs;

		// Ajout des contacts
		for (int i = 0; i < GameLoop::listContactGenerator.size(); i++) {
			GameLoop::listContactGenerator[i]->addContact();
		}

		// ##### POUR LES PARTICULES #####
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

		// Déclaration d'un octree de 20x20x20 centré en (0,0,0)
		Vect3 *octreeInitValues = new Vect3[8];
		CollisionData data = CollisionData();
		octreeInitValues[0] = Vect3(-10.f, -10.f, -10.f);
		octreeInitValues[1] = Vect3(10.f, -10.f, -10.f);
		octreeInitValues[2] = Vect3(-10.f, 10.f, -10.f);
		octreeInitValues[3] = Vect3(10.f, 10.f, -10.f);
		octreeInitValues[4] = Vect3(-10.f, -10.f, 10.f);
		octreeInitValues[5] = Vect3(10.f, -10.f, 10.f);
		octreeInitValues[6] = Vect3(-10.f, 10.f, 10.f);
		octreeInitValues[7] = Vect3(10.f, 10.f, 10.f);
		Octree o = Octree(octreeInitValues, 3, 10);

		// On insère toutes les primitives dans l'octree
		for (int i = 0; i < GameLoop::primitives.size(); i++) {
			o.insert(GameLoop::primitives[i]);
		}

		// Récupère les primitives voisines dans l'octree et cherche les vraies collisions
		for (int i = 0; i < GameLoop::primitives.size(); i++) {
			vector<Primitive*> neighbourPrims = o.retrieve(GameLoop::primitives[i]);
			for (int j = 0; j < neighbourPrims.size(); j++) {
				if (neighbourPrims[j] != GameLoop::primitives[i]) {
					// Si c'est une collision boîte - plan
					if (neighbourPrims[j]->type == PrimType::Box && GameLoop::primitives[i]->type == PrimType::Plane) {
						CollisionData::generateContact(*(Box*)(neighbourPrims[j]), *(Plane*)GameLoop::primitives[i], &data);
					}
					// Si c'est une collision plan - boîte (dans l'autre sens)
					if (neighbourPrims[j]->type == PrimType::Plane && GameLoop::primitives[i]->type == PrimType::Box) {
						CollisionData::generateContact(*(Box*)GameLoop::primitives[i], *(Plane*)(neighbourPrims[j]), &data);
					}
				}
			}
		}

		// Si on a un contact, on freeze l'animation
		if (data.contactsRestants != 0) {
			GameLoop::stop = true;
			data.Log();
		}

		//Résolution des contacts
		GameLoop::resolver.setIter(GameLoop::listContact.size());
		GameLoop::resolver.setVector(GameLoop::listContact);
		GameLoop::resolver.resolveContact();
		for (std::vector< ParticleContact* >::iterator it = GameLoop::listContact.begin(); it != GameLoop::listContact.end(); ++it) {
			delete (*it);
		}
		GameLoop::listContact.clear();

		// Prise en compte des forces
		for (RegisterForce::ForceRecord record : records) {
			record.pfg->updateForce(record.go, timeElapsedMs / 1000.);
		}

		//Mise à jour de la physique
		for (GameObject *go : GameLoop::world) {
			go->update(timeElapsedMs / 1000.);
		}
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
	glVertex3f(100, 2, 100);
	glVertex3f(100, 2, -100.0);
	glVertex3f(-100, 2, -100.0);
	glVertex3f(-100, 2., 100.0);
	glEnd();
	glPopMatrix();
}
