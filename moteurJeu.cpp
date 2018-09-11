#include "Vect3D.h"
#include "Particle.h"
#include "Affichage.h"
#include "vector"

using namespace std;


const float T = 1.6;
const float D = 0.9;
const int G = 5;
vector<Particle> Affichage::list = vector<Particle>();
float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;


int main(int argc, char ** argv) {
	Particle p = new Particle(Vect3D(-1, 0, 0), Vect3D(0, 0, 0), 10);
	Particle p2 = new Particle(Vect3D(1, 0, 0), Vect3D(0, 0, 0), 10);
	vector<Particle> tampon;
	tampon.push_back(p2);
	tampon.push_back(p);
	Affichage a(argc, argv, tampon);
	a.setList(tampon);
	a.refresh();
	return 0;
}
