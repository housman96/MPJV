#include "DragGenerator.h"


// ============================================================
// CONSTRUCTEURS
// ============================================================

DragGenerator::DragGenerator(const float &k1_, const float &k2_) {
  this->k1 = k1_;
  this->k2 = k2_;
}
DragGenerator::DragGenerator(const DragGenerator &other) {
  this->k1 = other.k1;
  this->k2 = other.k2;
}
DragGenerator::DragGenerator(const DragGenerator *other) {
  this->k1 = other->k1;
  this->k2 = other->k2;
}


// ============================================================
// MISE A JOUR
// ============================================================

void DragGenerator::updateForce(Particle *p, float duration) {
  Vect3 vel = p->getVelocity();
  Vect3 drag = vel.normalize().scale(-1);
  drag = drag.scale(k1 * vel.mag() + k2 * vel.magSq());
  p->applyForce(drag);
}

void DragGenerator::updateForce(Rigidbody * p, float duration)
{
}
