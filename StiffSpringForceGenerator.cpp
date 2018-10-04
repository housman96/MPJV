#include "StiffSpringForceGenerator.h"

StiffSpringForceGenerator::StiffSpringForceGenerator(const Vect3D pos, const float k_, const float d_)
{
    this->anchorPos = pos;
    this->k = k_;
    this->d = d_;
}

StiffSpringForceGenerator::StiffSpringForceGenerator(const StiffSpringForceGenerator &other)
{
    anchorPos = other.anchorPos;
    k = other.k;
    d = other.d;
}

StiffSpringForceGenerator::StiffSpringForceGenerator(const StiffSpringForceGenerator *other)
{
    anchorPos = other->anchorPos;
    k = other->k;
    d = other->d;
}

void StiffSpringForceGenerator::updateForce(Particle *p, float duration)
{
    Vect3D p0 = p->getPosition();
    Vect3D v0 = p->getVelocity();
    float m = p->getMass();

    float gamma = 0.5 * sqrt(4 * k - d * d);
    Vect3D c = p0.scale(d / 2 * gamma);
    c = c.add(v0.scale(1. / gamma));

    Vect3D pt = p0.scale(cos(gamma * duration));
    pt = pt.add(c.scale(sin(gamma * duration)));
    pt = pt.scale(exp(-d * duration / gamma));

    Vect3D acc = pt.sub(p0);
    acc = acc.scale(1. / (duration * duration));
    acc = acc.sub(v0);

    Vect3D force = acc.scale(m);
    p->applyForce(force);
}