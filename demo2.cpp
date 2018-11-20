#include "Vect3.h"
#include "GameLoop.h"
#include "Rigidbody.h"
#include "GravityGenerator.h"
#include <vector>

using namespace std;


RegisterForce::Register records;
vector<GameObject *> GameLoop::world = vector<GameObject *>();
vector<ParticleContact*> GameLoop::listContact = vector<ParticleContact*>();

float GameLoop::lastLoopTime = 0.;
float GameLoop::timeAccumulatedMs = 0.;


int main(int argc, char** argv)
{
	// ==================================================
	//      RIGIGBODY
	// ==================================================

	float mass = 10.0f;
	float linD = 1.0f;
	float angD = 0.9f;

	// Déclaration des corps rigides
	Rigidbody rb1 = new Rigidbody(mass, linD, angD);
	Rigidbody rb2 = new Rigidbody(mass, linD, angD);

	// Initialisation des corps rigides
	rb1.init(Vect3(-12, 0, 0), Vect3(5, 0, 0), Quaternion(0,0,0,1), Vect3());
	rb1.boxInertialTensor(mass, 4, 2, 2);
	rb2.init(Vect3(12, 0, 0), Vect3(-5, 0, 0), Quaternion(0,0,0,1), Vect3());
	rb2.boxInertialTensor(mass, 4, 2, 2);


	// ==================================================
	//      BOUCLE DE JEU
	// ==================================================

	// Particules à afficher
	vector<GameObject*> objects;
	objects.push_back(&rb1);
	objects.push_back(&rb2);

	// Lancement de la boucle de jeu
	GameLoop gl(argc, argv, objects);

	return 0;
}

