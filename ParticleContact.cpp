#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle &p1, Particle &p2, float c_) {
  particles[0] = &p1;
  particles[1] = &p2;
  c = c_;

  Vect3D p1_pos = p1.getPosition();
  Vect3D p2_pos = p1.getPosition();
  n = p1_pos.sub(p2_pos).normalize();

  //d = 2*r - dist pa pb
}
