#include "Vect3D.h"


using namespace std;


int main(int argc, char ** argv) {
	Vect3D u(1, 0, 0);
	Vect3D v(0, 1, 0);
	Vect3D w = u.cross(v);
	Vect3D z;


	u.log();
	v.log();
	w.log();
}
