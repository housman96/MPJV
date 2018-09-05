#include "Vect3D.h"


using namespace std;


int main(int argc, char ** argv) {
	Vect3D u(1, 0, 0);
	Vect3D v = u.copy();
	u = u.add(u);

	u.log();
	v.log();

	Particle p = new Particle()
}
