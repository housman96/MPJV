#include "StiffSpringForceGenerator.h"

StiffSpringForceGenerator::StiffSpringForceGenerator(const Vect3D pos, const float k_, const float damping_)
{
    this->anchorPos = pos;
    this->k = k_;
    this->damping = damping_;
}

StiffSpringForceGenerator::StiffSpringForceGenerator(const StiffSpringForceGenerator &other)
{
    anchorPos = other.anchorPos;
    k = other.k;
    damping = other.damping;
}

StiffSpringForceGenerator::StiffSpringForceGenerator(const StiffSpringForceGenerator *other)
{
    anchorPos = other->anchorPos;
    k = other->k;
    damping = other->damping;
}

void StiffSpringForceGenerator::updateForce(Particle *p, float duration)
{
    // TODO
}