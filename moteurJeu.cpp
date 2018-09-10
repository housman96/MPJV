#include "Vect3D.h"
#include "Particle.h"


using namespace std;


int main(int argc, char ** argv) {
	float t = 1;
	float d = 0.9;
	float g = 5;

	Vect3D grav = new Vect3D(0, -g, 0);
	Particle p = new Particle(Vect3D(0, 0, 0), Vect3D(1, 1, 0), 10);
	p.setDamping(d);

	p.log();
	for (int i = 0; i < 10; i++) {
		p.applyForce(grav);
		p.update(t);
		p.log();
	}
}
