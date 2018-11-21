#include "constants.h"
#include "Vect3.h"
#include "Particle.h"
#include "GameLoop.h"
#include "RegisterForce.h"
#include "GravityGenerator.h"
#include "DragGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeSpringForceGenerator.h"
#include "FloatingSpringForceGenerator.h"
#include "StiffSpringForceGenerator.h"
#include "ParticleContactResolver.h"
#include "ParticleCable.h"
#include "ParticleRod.h"
#include "Matrix33.h"
#include "Matrix34.h"
#include <vector>

using namespace std;


//int G = 15;
//RegisterForce::Register records;
//
//vector<GameObject *> GameLoop::world = vector<GameObject *>();
//vector<ParticleContact*> GameLoop::listContact = vector<ParticleContact*>();
//vector<ParticleContactGenerator*> GameLoop::listContactGenerator = vector<ParticleContactGenerator*>();
//ParticleContactResolver GameLoop::resolver = ParticleContactResolver();
//
//float GameLoop::lastLoopTime = 0.;
//float GameLoop::timeAccumulatedMs = 0.;
//
//
//int main(int argc, char** argv)
//{
//	// ==================================================
//	//      PARTICULES
//	// ==================================================
//
//		// Déclaration des particules
//	Particle p1 = Particle(20., 1.);
//	Particle p2 = Particle(20., 1.);
//	Particle p3 = Particle(20., 1.);
//	Particle p4 = Particle(20., 1.);
//	Particle p5 = Particle(20., 1.);
//
//	// Initialisation des particules
//	p1.init(Vect3(0, 16, 0), Vect3(0, 0, 0), Vect3(0, 0, 0));
//	p2.init(Vect3(6, 12, 0), Vect3(0, 0, 0), Vect3(0, 0, 0));
//	p3.init(Vect3(4, 6, 0), Vect3(0, 0, 0), Vect3(0, 0, 0));
//	p4.init(Vect3(-4, 6, 0), Vect3(0, 0, 0), Vect3(0, 0, 0));
//	p5.init(Vect3(-6, 12, 0), Vect3(0, 0, 0), Vect3(0, 0, 0));
//
//
//	// ==================================================
//	//      GENERATEURS DE FORCE
//	// ==================================================
//
//	// Déclaration des générateurs de force
//	GravityGenerator gg = GravityGenerator(Vect3(0, -G, 0));
//	DragGenerator dg = DragGenerator(.9f, .7f);
//	SpringForceGenerator sfg_p1_p2 = SpringForceGenerator(&p2, 30.f, 1.f);
//	SpringForceGenerator sfg_p2_p3 = SpringForceGenerator(&p3, 30.f, 1.f);
//	SpringForceGenerator sfg_p3_p4 = SpringForceGenerator(&p4, 30.f, 1.f);
//	SpringForceGenerator sfg_p4_p5 = SpringForceGenerator(&p5, 30.f, 1.f);
//	SpringForceGenerator sfg_p5_p1 = SpringForceGenerator(&p1, 30.f, 1.f);
//
//
//	// Remplissage des registres de forces
//	//	=== Gravité
//	//	===== Particule 1
//	RegisterForce::ForceRecord fr_p1_gg;
//	fr_p1_gg.go = &p1;
//	fr_p1_gg.pfg = &gg;
//	records.push_back(fr_p1_gg);
//
//	//	===== Particule 2
//	RegisterForce::ForceRecord fr_p2_gg;
//	fr_p2_gg.go = &p2;
//	fr_p2_gg.pfg = &gg;
//	records.push_back(fr_p2_gg);
//
//	//	===== Particule 3
//	RegisterForce::ForceRecord fr_p3_gg;
//	fr_p3_gg.go = &p3;
//	fr_p3_gg.pfg = &gg;
//	records.push_back(fr_p3_gg);
//
//	//	===== Particule 4
//	RegisterForce::ForceRecord fr_p4_gg;
//	fr_p4_gg.go = &p4;
//	fr_p4_gg.pfg = &gg;
//	records.push_back(fr_p4_gg);
//
//	//	===== Particule 5
//	RegisterForce::ForceRecord fr_p5_gg;
//	fr_p5_gg.go = &p5;
//	fr_p5_gg.pfg = &gg;
//	records.push_back(fr_p5_gg);
//
//	// === Drag
//	//	===== Particule 1
//	RegisterForce::ForceRecord fr_p1_dg;
//	fr_p1_dg.go = &p1;
//	fr_p1_dg.pfg = &dg;
//	records.push_back(fr_p1_dg);
//
//	//	===== Particule 2
//	RegisterForce::ForceRecord fr_p2_dg;
//	fr_p2_dg.go = &p2;
//	fr_p2_dg.pfg = &dg;
//	records.push_back(fr_p2_dg);
//
//	//	===== Particule 3
//	RegisterForce::ForceRecord fr_p3_dg;
//	fr_p3_dg.go = &p3;
//	fr_p3_dg.pfg = &dg;
//	records.push_back(fr_p3_dg);
//
//	//	===== Particule 4
//	RegisterForce::ForceRecord fr_p4_dg;
//	fr_p4_dg.go = &p4;
//	fr_p4_dg.pfg = &dg;
//	records.push_back(fr_p4_dg);
//
//	//	===== Particule 5
//	RegisterForce::ForceRecord fr_p5_dg;
//	fr_p5_dg.go = &p5;
//	fr_p5_dg.pfg = &dg;
//	records.push_back(fr_p5_dg);
//
//	// === Ressort
//	//	===== Particule 1 et 2
//	RegisterForce::ForceRecord fr_sfg_p1_p2;
//	fr_sfg_p1_p2.go = &p1;
//	fr_sfg_p1_p2.pfg = &sfg_p1_p2;
//	records.push_back(fr_sfg_p1_p2);
//
//	//	===== Particule 2 et 3
//	RegisterForce::ForceRecord fr_sfg_p2_p3;
//	fr_sfg_p2_p3.go = &p2;
//	fr_sfg_p2_p3.pfg = &sfg_p2_p3;
//	records.push_back(fr_sfg_p2_p3);
//
//	//	===== Particule 3 et 4
//	RegisterForce::ForceRecord fr_sfg_p3_p4;
//	fr_sfg_p3_p4.go = &p3;
//	fr_sfg_p3_p4.pfg = &sfg_p3_p4;
//	records.push_back(fr_sfg_p3_p4);
//
//	//	===== Particule 4 et 5
//	RegisterForce::ForceRecord fr_sfg_p4_p5;
//	fr_sfg_p4_p5.go = &p4;
//	fr_sfg_p4_p5.pfg = &sfg_p4_p5;
//	records.push_back(fr_sfg_p4_p5);
//
//	//	===== Particule 5 et 1
//	RegisterForce::ForceRecord fr_sfg_p5_p1;
//	fr_sfg_p5_p1.go = &p5;
//	fr_sfg_p5_p1.pfg = &sfg_p5_p1;
//	records.push_back(fr_sfg_p5_p1);
//
//
//	// ==================================================
//	//      CABLES
//	// ==================================================
//
//		// Déclaration des cables
//	ParticleCable c_p1_p2 = ParticleCable(&p1, &p2, 15.f, 0.5f); // Entre p1 et p2
//	ParticleCable c_p2_p3 = ParticleCable(&p2, &p3, 15.f, 0.5f); // Entre p2 et p3
//	ParticleCable c_p3_p4 = ParticleCable(&p3, &p4, 15.f, 0.5f); // Entre p3 et p4
//	ParticleCable c_p4_p5 = ParticleCable(&p4, &p5, 15.f, 0.5f); // Entre p4 et p5
//	ParticleCable c_p5_p1 = ParticleCable(&p5, &p1, 15.f, 0.5f); // Entre p5 et p1
//
//	// Passage des cables dans la structure de la physique
//	GameLoop::listContactGenerator.push_back(&c_p1_p2);
//	GameLoop::listContactGenerator.push_back(&c_p2_p3);
//	GameLoop::listContactGenerator.push_back(&c_p3_p4);
//	GameLoop::listContactGenerator.push_back(&c_p4_p5);
//	GameLoop::listContactGenerator.push_back(&c_p5_p1);
//
//
//	// ==================================================
//	//      BOUCLE DE JEU
//	// ==================================================
//
//	// Particules à afficher
//	vector<GameObject*> particles;
//	particles.push_back(&p1);
//	particles.push_back(&p2);
//	particles.push_back(&p3);
//	particles.push_back(&p4);
//	particles.push_back(&p5);
//
//	// Lancement de la boucle de jeu
//	GameLoop a(argc, argv, particles);
//
//	return 0;
//}
