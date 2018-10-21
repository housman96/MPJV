#include "Affichage.h"
#include "DragGenerator.h"
#include "GravityGenerator.h"
#include "Particle.h"
#include "RegisterForce.h"
#include "SpringForceGenerator.h"
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
    Particle p1 = new Particle(10., 1.);
    Particle p2 = new Particle(2000., 1.);
    p1.init(Vect3D(-2, 10, 0), Vect3D(-5, 0, 0), Vect3D(0, 0, 0));
    p2.init(Vect3D(2, 10, 0), Vect3D(2, 0, 0), Vect3D(0, 0, 0));

    /* DECLARATION DES GENERATEURS DE FORCES */
    GravityGenerator gg = new GravityGenerator(Vect3D(0, -G, 0));
    DragGenerator dg = new DragGenerator(.9f, .7f);
    SpringForceGenerator sfg = new SpringForceGenerator(p2, 15, 2);
    //cout << "Main : " << &p2 << endl;

    /* REMPLISSAGE DU REGISTRE DE FORCE */
    // RegisterForce::ForceRecord fr_p1_gg;
    // RegisterForce::ForceRecord fr_p1_dg;
    RegisterForce::ForceRecord fr_p1_sfg;


    // fr_p1_gg.p = &p1;
    // fr_p1_gg.pfg = &gg;
    // fr_p1_dg.p = &p1;
    // fr_p1_dg.pfg = &dg;
    fr_p1_sfg.p = &p1;
    fr_p1_sfg.pfg = &sfg;
    // fr_p2_dg.p = &p2;
    // fr_p2_dg.pfg = &dg;

    // records.push_back(fr_p1_gg);
    // records.push_back(fr_p1_dg);
    records.push_back(fr_p1_sfg);

    /* CREATION DE L'AFFICHAGE */
    vector<Particle*> particules;

    particules.push_back(&p1);
    particules.push_back(&p2);

    Affichage a(argc, argv, particules);

    return 0;
}
