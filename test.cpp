#include "Vect3.h"
#include "Matrix34.h"
#include "GameLoop.h"
#include "Rigidbody.h"
#include "Box.h"
#include "Plane.h"
#include "Sphere.h"
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
	Rigidbody rb;
	Box b(&rb, Matrix34(), Vect3(1, 1, 1));
	Plane p(Vect3(0,1,0), 5);
	Sphere s(&rb, Matrix34(), 3);

	p.normal.log();

	return 0;
}
