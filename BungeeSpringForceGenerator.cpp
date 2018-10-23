#include "BungeeSpringForceGenerator.h"

BungeeSpringForceGenerator::BungeeSpringForceGenerator(const Particle &p, const float k_, const float l0_)
{
    this->otherP = p;
    this->k = k_;
    this->l0 = l0_;
}

BungeeSpringForceGenerator::BungeeSpringForceGenerator(const BungeeSpringForceGenerator &other)
{
    otherP = other.otherP;
    k = other.k;
    l0 = other.l0;
}

BungeeSpringForceGenerator::BungeeSpringForceGenerator(const BungeeSpringForceGenerator *other)
{
    otherP = other->otherP;
    k = other->k;
    l0 = other->l0;
}

void BungeeSpringForceGenerator::updateForce(Particle *p, float duration)
{
    Vect3D d = p->getPosition().sub(otherP.getPosition());
    Vect3D springForce;

    if (d.mag() <= l0)
    {
        springForce = new Vect3D(0, 0, 0);
    }
    else
    {
        springForce = d.normalize();
        springForce = springForce.scale(-k * (d.mag() - l0));
    }

    p->applyForce(springForce);
}