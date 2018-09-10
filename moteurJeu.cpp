#include "Vect3D.h"
#include "Particle.h"
#include "Affichage.h"
#include "vector"

using namespace std;

std::vector<Particle> Affichage::list = vector<Particle>();

int main(int argc, char **argv)
{
	Particle p = new Particle(Vect3D(0, 0, 0), Vect3D(0, 0, 0), 10);
	return 0;
}
