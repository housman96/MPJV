#include "constants.h"
#include "Vect3D.h"
#include "Particle.h"
#include "Affichage.h"
#include "RegisterForce.h"
#include "GravityGenerator.h"
#include "DragGenerator.h"
#include <vector>

using namespace std;

int G = 15;
RegisterForce::Register r;

vector<Particle> Affichage::list = vector<Particle>();
float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;

int main(int argc, char **argv)
{

	Particle p1 = new Particle(2., 1.);
	// Particle p2 = new Particle(3., 1.);
	p1.init(Vect3D(-1, 10, 0), Vect3D(-1, 2, 0), Vect3D(0, 0, 0));
	// p2.init(Vect3D(1, 10, 0), Vect3D(1, 2, 0), Vect3D(0, 0, 0));

	GravityGenerator gg = new GravityGenerator(Vect3D(0, -G, 0));
	RegisterForce::ForceRecord fr1;
	RegisterForce::ForceRecord fr2;
	RegisterForce::ForceRecord fr3;
	RegisterForce::ForceRecord fr4;
	fr1.p = &p1;
	fr1.pfg = &gg;
	// fr2.p = &p2;
	// fr2.pfg = &gg;

	// fr3.p = &p1;
	// fr3.pfg=
	// fr4.p = &p2;

	r.push_back(fr1);
	// r.push_back(fr2);

	cout << r.size() << endl;

	vector<Particle> particules;
	particules.push_back(p1);
	// particules.push_back(p2);

	Affichage a(argc, argv, particules);

	return 0;
}
