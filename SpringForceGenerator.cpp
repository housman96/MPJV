#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Particle *p, const float k_, const float l0_)
{
    otherP = p;
    k = k_;
    l0 = l0_;
}

SpringForceGenerator::SpringForceGenerator(const SpringForceGenerator& other)
{
    otherP = other.otherP;
    k = other.k;
    l0 = other.l0;
}

SpringForceGenerator::SpringForceGenerator(const SpringForceGenerator* other)
{
    otherP = other->otherP;
    k = other->k;
    l0 = other->l0;
}

SpringForceGenerator::~SpringForceGenerator()
{
    delete otherP;
}

void SpringForceGenerator::updateForce(Particle* p, float duration)
{
    Vect3D d = p->getPosition().sub(otherP->getPosition());
    Vect3D springForce = d.normalize();
    springForce = springForce.scale(-k * (d.mag() - l0));
    p->applyForce(springForce);
}