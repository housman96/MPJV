#include "FloatingSpringForceGenerator.h"

FloatingSpringForceGenerator::FloatingSpringForceGenerator(const Vect3D pos, const float density, const float objDepth, const float objVolume)
{
    this->waterPos = pos;
    this->liquidDensity = density;
    this->maxObjectDepth = objDepth;
    this->objectVolume = objVolume;
}

FloatingSpringForceGenerator::FloatingSpringForceGenerator(const FloatingSpringForceGenerator &other)
{
    waterPos = other.waterPos;
    liquidDensity = other.liquidDensity;
    maxObjectDepth = other.maxObjectDepth;
    objectVolume = other.objectVolume;
}

FloatingSpringForceGenerator::FloatingSpringForceGenerator(const FloatingSpringForceGenerator *other)
{
    waterPos = other->waterPos;
    liquidDensity = other->liquidDensity;
    maxObjectDepth = other->maxObjectDepth;
    objectVolume = other->objectVolume;
}

void FloatingSpringForceGenerator::updateForce(Particle *p, float duration)
{
    float submersion = (p->getPosition().getY() - waterPos.getY() - maxObjectDepth) / (2 * maxObjectDepth);
    Vect3D floatingForce;

    if (submersion <= 0)
    {
        floatingForce = new Vect3D(0, 0, 0);
    }
    else if (submersion >= 1)
    {
        floatingForce = new Vect3D(0, 1, 0);
        floatingForce = floatingForce.scale(objectVolume * liquidDensity);
    }
    else
    {
        floatingForce = new Vect3D(0, 1, 0);
        floatingForce = floatingForce.scale(objectVolume * liquidDensity * submersion);
    }

    p->applyForce(floatingForce);
}