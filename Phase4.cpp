#include "Vect3.h"
#include "GameLoop.h"
#include "Rigidbody.h"
#include "Box.h"
#include "Plane.h"
#include "GravityGenerator.h"
#include <vector>

using namespace std;


RegisterForce::Register records;
vector<GameObject *> GameLoop::world = vector<GameObject *>();
vector<ParticleContact*> GameLoop::listContact = vector<ParticleContact*>();
vector<ParticleContactGenerator*> GameLoop::listContactGenerator = vector<ParticleContactGenerator*>();
ParticleContactResolver GameLoop::resolver = ParticleContactResolver();

float GameLoop::lastLoopTime = 0.;
float GameLoop::timeAccumulatedMs = 0.;


int main(int argc, char** argv)
{
	// ==================================================
	//      RIGIGBODY
	// ==================================================

	float boxMass = 1.0f;
	float boxLinD = 0.9f;
	float boxAngD = 0.9f;

	// Déclaration du corps rigide de la boite
	Rigidbody boxRb = Rigidbody(boxMass, boxLinD, boxAngD);

	// Initialisation du corps rigide de la boîte
	boxRb.init(Vect3(0, 10, 0), Vect3(3, 5, 0), Quaternion(0, 0, 0, 1), Vect3(1, 2, 1));
	boxRb.boxInertialTensor(boxMass, 2, 2, 2);


	// ==================================================
	//      PRIMITIVE
	// ==================================================

	// Décralartion de la primitive boîte pour le rigidbody Box
	Matrix34 identity;
	identity.tab[0] = 1.0f;
	identity.tab[5] = 1.0f;
	identity.tab[10] = 1.0f;
	Box b = Box(&boxRb, identity, Vect3(1, 1, 1));

	// Déclaration de la primitive pour le mur
	Plane p = Plane(Vect3(1, 0, 0), -10.f);


	// ==================================================
	//      GENERATEURS DE FORCE
	// ==================================================

	float G = 15.f;

	// Déclaration du générateur de force
	GravityGenerator grav = GravityGenerator(Vect3(0, -G, 0));

	// Remplissage des registres de forces
	RegisterForce::ForceRecord fr_rb_gg;
	fr_rb_gg.go = &boxRb;
	fr_rb_gg.pfg = &grav;
	records.push_back(fr_rb_gg);


	// ==================================================
	//      BOUCLE DE JEU
	// ==================================================

	// GameObjects en mouvement
	vector<GameObject*> objects;
	objects.push_back(&boxRb);

	// Primitives à afficher
	vector<Primitive*> primitives;
	primitives.push_back(&b);
	primitives.push_back(&p);

	// Lancement de la boucle de jeu
	GameLoop gl(argc, argv, objects);

	return 0;
}