#include "Affichage.h"
#include "DragGenerator.h"
#include "GravityGenerator.h"
#include "Particle.h"
#include "RegisterForce.h"
#include "Vect3D.h"
#include "constants.h"
#include <vector>

using namespace std;

int G = 15;
RegisterForce::Register r;

vector<Particle *> Affichage::list = vector<Particle *>();
float Affichage::lastLoopTime = 0.;
float Affichage::timeAccumulatedMs = 0.;

int main(int argc, char **argv) {
  /* DECLARATION DES PARTICULES */
  Particle p1 = new Particle(10., 1.);
  // Particle p2 = new Particle(2000., 1.);
  p1.init(Vect3D(0, 10, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));
  // p2.init(Vect3D(2, 10, 0), Vect3D(0, 0, 0), Vect3D(0, 0, 0));

  /* DECLARATION DES GENERATEURS DE FORCES */
  GravityGenerator gg = new GravityGenerator(Vect3D(0, -G, 0));
  // DragGenerator dg = new DragGenerator(.9f, .7f);

  /* REMPLISSAGE DU REGISTRE DE FORCE */
  RegisterForce::ForceRecord fr_p1_gg;
  // RegisterForce::ForceRecord fr_p1_dg;
  // RegisterForce::ForceRecord fr_p2_gg;
  // RegisterForce::ForceRecord fr_p2_dg;

  fr_p1_gg.p = &p1;
  fr_p1_gg.pfg = &gg;
  // fr_p1_dg.p = &p1;
  // fr_p1_dg.pfg = &dg;
  // fr_p2_gg.p = &p2;
  // fr_p2_gg.pfg = &gg;
  // fr_p2_dg.p = &p2;
  // fr_p2_dg.pfg = &dg;

  r.push_back(fr_p1_gg);
  // r.push_back(fr_p1_dg);
  // r.push_back(fr_p2_gg);
  // r.push_back(fr_p2_dg);

  /* CREATION DE L'AFFICHAGE */
  vector<Particle *> particules;

  particules.push_back(&p1);
  // particules.push_back(&p2);

  Affichage a(argc, argv, particules);

  return 0;
}
