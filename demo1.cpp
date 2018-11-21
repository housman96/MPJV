#include "Vect3.h"
#include "GameLoop.h"
#include "Rigidbody.h"
#include "GravityGenerator.h"
#include <vector>

using namespace std;


//RegisterForce::Register records;
//vector<GameObject *> GameLoop::world = vector<GameObject *>();
//vector<ParticleContact*> GameLoop::listContact = vector<ParticleContact*>();
//vector<ParticleContactGenerator*> GameLoop::listContactGenerator = vector<ParticleContactGenerator*>();
//ParticleContactResolver GameLoop::resolver = ParticleContactResolver();
//
//float GameLoop::lastLoopTime = 0.;
//float GameLoop::timeAccumulatedMs = 0.;
//
//
//int main(int argc, char** argv)
//{
//	// ==================================================
//	//      RIGIGBODY
//	// ==================================================
//
//	float mass = 1.0f;
//	float linD = 0.9f;
//	float angD = 0.9f;
//
//	// Déclaration du corps rigide
//	Rigidbody rb = new Rigidbody(mass, linD, angD);
//
//	// Initialisation du corps rigide
//	rb.init(Vect3(0, 10, 0), Vect3(3, 5, 0), Quaternion(0, 0, 0, 1), Vect3(1, 2, 1));
//	rb.boxInertialTensor(mass, 2, 2, 2);
//
//
//	// ==================================================
//	//      GENERATEURS DE FORCE
//	// ==================================================
//
//	float G = 15.f;
//
//	// Déclaration du générateur de force
//	GravityGenerator grav = new GravityGenerator(Vect3(0, -G, 0));
//
//	// Remplissage des registres de forces
//	RegisterForce::ForceRecord fr_rb_gg;
//	fr_rb_gg.go = &rb;
//	fr_rb_gg.pfg = &grav;
//	records.push_back(fr_rb_gg);
//
//
//	// ==================================================
//	//      BOUCLE DE JEU
//	// ==================================================
//
//	// Particules à afficher
//	vector<GameObject*> objects;
//	objects.push_back(&rb);
//
//	// Lancement de la boucle de jeu
//	GameLoop gl(argc, argv, objects);
//
//	return 0;
//}