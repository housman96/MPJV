#include "constants.h"
#include "Vect3D.h"
#include "Particle.h"
#include "Affichage.h"
#include <vector>

using namespace std;


int G = 200;

vector<Particle> Affichage::list = vector<Particle>();
float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;

int main(int argc, char ** argv) {
	Particle p1 = new Particle(20, 1., 0.92);
	Particle p2 = new Particle(30, 1., 0.92);
	p1.init(Vect3D(-1, 0, 0), Vect3D(-1, 25, 12), Vect3D(0, 0, 0));
	p2.init(Vect3D(1, 0, 0), Vect3D(1, 25, 12), Vect3D(0, 0, 0));

	vector<Particle> particules;
	particules.push_back(p1);
	particules.push_back(p2);

	Affichage a(argc, argv, particules);

	return 0;
}
