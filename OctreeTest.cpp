#include "Vect3.h"
#include "GameLoop.h"
#include "Rigidbody.h"
#include "GravityGenerator.h"
#include "Octree.h"
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
	Vect3 *tab = new Vect3[8];
	tab[0] = Vect3(0.f, 0.f, 0.f);
	tab[1] = Vect3(1.f, 0.f, 0.f);
	tab[2] = Vect3(0.f, 1.f, 0.f);
	tab[3] = Vect3(1.f, 1.f, 0.f);
	tab[4] = Vect3(0.f, 0.f, 1.f);
	tab[5] = Vect3(1.f, 0.f, 1.f);
	tab[6] = Vect3(0.f, 1.f, 1.f);
	tab[7] = Vect3(1.f, 1.f, 1.f);
	Octree o = Octree(tab, 3, 10);


	Rigidbody p1 = Rigidbody();
	p1.init(Vect3(0.8, 0, 0.8), Vect3(), Quaternion(), Vect3());
	o.insert(&p1);

	Particle p2 = Particle();
	p2.setPosition(Vect3(0.7, 0, 0.8));
	o.insert(&p2);

	Particle p3 = Particle();
	p3.setPosition(Vect3(0, 0.6, 0.8));
	o.insert(&p3);

	Rigidbody p4 = Rigidbody();
	p4.init(Vect3(0, 0, 0.1), Vect3(), Quaternion(), Vect3());
	o.insert(&p4);
	vector<GameObject*> tabO = o.retrieve(&p1);
	for (int i = 0; i < tabO.size(); i++)
	{
		((Particle*)tabO[i])->position.log();
	}


	return 0;
}