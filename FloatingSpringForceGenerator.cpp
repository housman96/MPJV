#include "FloatingSpringForceGenerator.h"


// ============================================================
// CONSTRUCTEURS
// ============================================================

FloatingSpringForceGenerator::FloatingSpringForceGenerator(const Vect3 pos, const float density, const float objDepth, const float objVolume)
{
    this->waterPos = pos;
    this->liquidDensity = density;
    this->maxObjectDepth = objDepth;
    this->objectVolume = objVolume;
}

FloatingSpringForceGenerator::FloatingSpringForceGenerator(const FloatingSpringForceGenerator& other)
{
    waterPos = other.waterPos;
    liquidDensity = other.liquidDensity;
    maxObjectDepth = other.maxObjectDepth;
    objectVolume = other.objectVolume;
}

FloatingSpringForceGenerator::FloatingSpringForceGenerator(const FloatingSpringForceGenerator* other)
{
    waterPos = other->waterPos;
    liquidDensity = other->liquidDensity;
    maxObjectDepth = other->maxObjectDepth;
    objectVolume = other->objectVolume;
}


// ============================================================
// MISE A JOUR
// ============================================================

void FloatingSpringForceGenerator::updateForce(Particle* p, float duration)
{
	// Changement de la formule, car résultats incohérents
	// d = - (y0 - yw - s) / 2s
	//     ^
    float submersion = -(p->getPosition().getY() - waterPos.getY() - maxObjectDepth) / (2 * maxObjectDepth);
    Vect3 floatingForce;

    if (submersion <= 0) {
        floatingForce = new Vect3(0, 0, 0);
    } else if (submersion >= 1) {
        floatingForce = new Vect3(0, 1, 0);
        floatingForce = floatingForce.scale(objectVolume * liquidDensity);
    } else {
        floatingForce = new Vect3(0, 1, 0);
        floatingForce = floatingForce.scale(objectVolume * liquidDensity * submersion);
    }

    p->applyForce(floatingForce);
}

void FloatingSpringForceGenerator::updateForce(Rigidbody *, float)
{
}
