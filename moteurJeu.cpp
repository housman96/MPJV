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

vector<Particle *> Affichage::list = vector<Particle *>();
float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;

int main(int argc, char **argv)
{
	/*DECLARATION DES PARTICULES*/
	Particle p1 = new Particle(1., 1.);
	Particle p2 = new Particle(2000., 1.);
	p1.init(Vect3D(-1, 10, 0), Vect3D(0, 2, 0), Vect3D(0, 0, 0));
	p2.init(Vect3D(1, 10, 0), Vect3D(0, 2, 0), Vect3D(0, 0, 0));

	/*DECLARATION DES GENERATEURS DE FORCES*/
	GravityGenerator gg = new GravityGenerator(Vect3D(0, -G, 0));
	DragGenerator dg = new DragGenerator(50.f, 30.f);
	DragGenerator dg2 = new DragGenerator(50.f, 30.f);

	/*REMPLISSAGE DU REGISTRE DE FORCE*/
	RegisterForce::ForceRecord fr1;
	RegisterForce::ForceRecord fr2;
	RegisterForce::ForceRecord fr3;
	RegisterForce::ForceRecord fr4;

	fr1.p = &p1;
	fr1.pfg = &gg;
	fr2.p = &p2;
	fr2.pfg = &gg;
	fr3.p = &p1;
	fr3.pfg = &dg;
	fr4.p = &p2;
	fr4.pfg = &dg2;

	r.push_back(fr1);
	r.push_back(fr2);
	r.push_back(fr3);
	r.push_back(fr4);

	/*CREATION DE L'AFFICHAGE*/
	vector<Particle *> particules;

	particules.push_back(&p1);
	particules.push_back(&p2);

	// for (int i = 1; i < 10; i++)
	// {
	// 	Particle *p = new Particle(i * 100., 1.);
	// 	p->init(Vect3D(i * 3 - 20, 8, 0), Vect3D(0, 2, 0), Vect3D(0, 0, 0));
	// 	RegisterForce::ForceRecord fri1;
	// 	RegisterForce::ForceRecord fri2;

	// 	fri1.p = p;
	// 	fri1.pfg = &gg;
	// 	fri2.p = p;
	// 	fri2.pfg = &dg;

	// 	r.push_back(fri1);
	// 	r.push_back(fri2);

	// 	particules.push_back(p);
	// }

	Affichage a(argc, argv, particules);

	return 0;
}
