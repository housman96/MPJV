#include "Affichage.h"
#include "AnchoredSpringForceGenerator.h"
#include "BungeeSpringForceGenerator.h"
#include "DragGenerator.h"
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

vector<Particle*> Affichage::list = vector<Particle*>();
float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;

int main(int argc, char** argv)
{
    /* DECLARATION DES PARTICULES */
    Particle p1 = new Particle(500., 1.);
    Particle p2 = new Particle(20., 1.);
    p1.init(Vect3D(-2, 10, 0), Vect3D(-0.5, 0, 0), Vect3D(0, 0, 0));
    p2.init(Vect3D(2, 10, 0), Vect3D(1, 0, 0), Vect3D(0, 0, 0));

    /* DECLARATION DES GENERATEURS DE FORCES */
    GravityGenerator gg = new GravityGenerator(Vect3D(0, -G, 0)); // OK
    DragGenerator dg = new DragGenerator(.9f, .7f); // OK
    SpringForceGenerator sfg = new SpringForceGenerator(&p2, 30.f, 1.f); // OK
    BungeeSpringForceGenerator bsfg = new BungeeSpringForceGenerator(&p2, 50.f, 3.f); // OK
    AnchoredSpringForceGenerator asfg = new AnchoredSpringForceGenerator(Vect3D(0, 10, 0), 30.f, 0.5f); // OK
    FloatingSpringForceGenerator fsfg = new FloatingSpringForceGenerator(Vect3D(0, 5, 0), 1000.f, 2.f, 4.f * 3.14f); // OK

    /* REMPLISSAGE DU REGISTRE DE FORCE */
    //RegisterForce::ForceRecord fr_p1_gg;
    //RegisterForce::ForceRecord fr_p1_dg;
    //RegisterForce::ForceRecord fr_p1_sfg;
    RegisterForce::ForceRecord fr_p1_bsfg;
    //RegisterForce::ForceRecord fr_p1_asfg;
    //RegisterForce::ForceRecord fr_p1_fsfg;

    //fr_p1_gg.p = &p1;
    //fr_p1_gg.pfg = &gg;
    //fr_p1_dg.p = &p1;
    //fr_p1_dg.pfg = &dg;
    //fr_p1_sfg.p = &p1;
    //fr_p1_sfg.pfg = &sfg;
    fr_p1_bsfg.p = &p1;
    fr_p1_bsfg.pfg = &bsfg;
    //fr_p1_asfg.p = &p1;
    //fr_p1_asfg.pfg = &asfg;
    //fr_p1_fsfg.p = &p1;
    //fr_p1_fsfg.pfg = &fsfg;

    //records.push_back(fr_p1_gg);
    //records.push_back(fr_p1_dg);
    //records.push_back(fr_p1_sfg);
    records.push_back(fr_p1_bsfg);
    //records.push_back(fr_p1_asfg);
    //records.push_back(fr_p1_fsfg);

    /* CREATION DE L'AFFICHAGE */
    vector<Particle*> particules;
    particules.push_back(&p1);
    particules.push_back(&p2);

    Affichage a(argc, argv, particules);

    return 0;
}
