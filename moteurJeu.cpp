#include "Vect3D.h"
#include "Particle.h"


using namespace std;


int main(int argc, char ** argv) {
	float t = 1;
	float d = 0.9;

	Vect3D g = new Vect3D(0, -1, 0);
	Particle p = new Particle(Vect3D(0, 0, 0), Vect3D(1, 1, 0), 10);
	p.setDamping(d);

	p.log();
	p.applyForce(g);
	p.update(t);
	p.log();
}
