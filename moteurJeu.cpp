#include "Affichage.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeSpringForceGenerator.h"
#include "DragGenerator.h"
#include "ParticleContactResolver.h"
#include "ParticleCable.h"
#include "ParticleRod.h"
#include "FloatingSpringForceGenerator.h"
#include "GravityGenerator.h"
#include "Particle.h"
#include "RegisterForce.h"
#include "SpringForceGenerator.h"
#include "StiffSpringForceGenerator.h"
#include "Vect3D.h"
#include "constants.h"

#include <vector>

using namespace std;

int G = 15;
RegisterForce::Register records;



vector<Particle *> Affichage::list = vector<Particle *>();
vector<ParticleContact*> Affichage::listContact = vector<ParticleContact*>();
vector<ParticleContactGenerator*> Affichage::listContactGenerator = vector<ParticleContactGenerator*>();
ParticleContactResolver Affichage::resolver = ParticleContactResolver();

float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;

int main(int argc, char** argv)
{

	/* DECLARATION DES PARTICULES */
	Particle p1 = new Particle(20., 1.);
	Particle p2 = new Particle(20., 1.);
	Particle p3 = new Particle(20., 1.);
	Particle p4 = new Particle(20., 1.);
	Particle p5 = new Particle(20., 1.);

	p1.init(Vect3D(0, 16, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));
	p2.init(Vect3D(6, 12, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));
	p3.init(Vect3D(4, 6, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));
	p4.init(Vect3D(-4, 6, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));
	p5.init(Vect3D(-6, 12, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));


	/* DECLARATION DES GENERATEURS DE FORCES */
	GravityGenerator gg = new GravityGenerator(Vect3D(0, -G, 0));
	DragGenerator dg = new DragGenerator(.9f, .7f);
	SpringForceGenerator sfg_p1_p2 = new SpringForceGenerator(&p2, 30.f, 1.f);
	SpringForceGenerator sfg_p2_p3 = new SpringForceGenerator(&p3, 30.f, 1.f);
	SpringForceGenerator sfg_p3_p4 = new SpringForceGenerator(&p4, 30.f, 1.f);
	SpringForceGenerator sfg_p4_p5 = new SpringForceGenerator(&p5, 30.f, 1.f);
	SpringForceGenerator sfg_p5_p1 = new SpringForceGenerator(&p1, 30.f, 1.f);


	/* REMPLISSAGE DU REGISTRE DE FORCE */
	RegisterForce::ForceRecord fr_p1_gg;
	fr_p1_gg.p = &p1;
	fr_p1_gg.pfg = &gg;
	records.push_back(fr_p1_gg);

	RegisterForce::ForceRecord fr_p2_gg;
	fr_p2_gg.p = &p2;
	fr_p2_gg.pfg = &gg;
	records.push_back(fr_p2_gg);

	RegisterForce::ForceRecord fr_p3_gg;
	fr_p3_gg.p = &p3;
	fr_p3_gg.pfg = &gg;
	records.push_back(fr_p3_gg);

	RegisterForce::ForceRecord fr_p4_gg;
	fr_p4_gg.p = &p4;
	fr_p4_gg.pfg = &gg;
	records.push_back(fr_p4_gg);

	RegisterForce::ForceRecord fr_p5_gg;
	fr_p5_gg.p = &p5;
	fr_p5_gg.pfg = &gg;
	records.push_back(fr_p5_gg);


	RegisterForce::ForceRecord fr_p1_dg;
	fr_p1_dg.p = &p1;
	fr_p1_dg.pfg = &dg;
	records.push_back(fr_p1_dg);

	RegisterForce::ForceRecord fr_p2_dg;
	fr_p2_dg.p = &p2;
	fr_p2_dg.pfg = &dg;
	records.push_back(fr_p2_dg);

	RegisterForce::ForceRecord fr_p3_dg;
	fr_p3_dg.p = &p3;
	fr_p3_dg.pfg = &dg;
	records.push_back(fr_p3_dg);

	RegisterForce::ForceRecord fr_p4_dg;
	fr_p4_dg.p = &p4;
	fr_p4_dg.pfg = &dg;
	records.push_back(fr_p4_dg);

	RegisterForce::ForceRecord fr_p5_dg;
	fr_p5_dg.p = &p5;
	fr_p5_dg.pfg = &dg;
	records.push_back(fr_p5_dg);


	RegisterForce::ForceRecord fr_sfg_p1_p2;
	fr_sfg_p1_p2.p = &p1;
	fr_sfg_p1_p2.pfg = &sfg_p1_p2;
	records.push_back(fr_sfg_p1_p2);

	RegisterForce::ForceRecord fr_sfg_p2_p3;
	fr_sfg_p2_p3.p = &p2;
	fr_sfg_p2_p3.pfg = &sfg_p2_p3;
	records.push_back(fr_sfg_p2_p3);

	RegisterForce::ForceRecord fr_sfg_p3_p4;
	fr_sfg_p3_p4.p = &p3;
	fr_sfg_p3_p4.pfg = &sfg_p3_p4;
	records.push_back(fr_sfg_p3_p4);

	RegisterForce::ForceRecord fr_sfg_p4_p5;
	fr_sfg_p4_p5.p = &p4;
	fr_sfg_p4_p5.pfg = &sfg_p4_p5;
	records.push_back(fr_sfg_p4_p5);

	RegisterForce::ForceRecord fr_sfg_p5_p1;
	fr_sfg_p5_p1.p = &p5;
	fr_sfg_p5_p1.pfg = &sfg_p5_p1;
	records.push_back(fr_sfg_p5_p1);


	/* DECLARATION CABLES */
	ParticleCable c_p1_p2 = ParticleCable(&p1, &p2, 15.f, 0.5f);
	ParticleCable c_p2_p3 = ParticleCable(&p2, &p3, 15.f, 0.5f);
	ParticleCable c_p3_p4 = ParticleCable(&p3, &p4, 15.f, 0.5f);
	ParticleCable c_p4_p5 = ParticleCable(&p4, &p5, 15.f, 0.5f);
	ParticleCable c_p5_p1 = ParticleCable(&p5, &p1, 15.f, 0.5f);

	Affichage::listContactGenerator.push_back(&c_p1_p2);
	Affichage::listContactGenerator.push_back(&c_p2_p3);
	Affichage::listContactGenerator.push_back(&c_p3_p4);
	Affichage::listContactGenerator.push_back(&c_p4_p5);
	Affichage::listContactGenerator.push_back(&c_p5_p1);


	/* CREATION DE L'AFFICHAGE */
	vector<Particle*> particules;
	particules.push_back(&p1);
	particules.push_back(&p2);
	particules.push_back(&p3);
	particules.push_back(&p4);
	particules.push_back(&p5);


	Affichage a(argc, argv, particules);

	return 0;
}
