#ifndef DRAGGENERATOR_H
#define DRAGGENERATOR_H

#include "ParticleForceGenerator.h"
#include "Vect3D.h"

class DragGenerator : public ParticleForceGenerator {
private:
    float k1;
    float k2;

public:
    /* CONSTRUCTEURS ET DESTRUCTEUR */
    DragGenerator(const float&, const float&);
    DragGenerator(const DragGenerator&);
    DragGenerator(const DragGenerator*);

    virtual void updateForce(Particle*, float);
};

#endif
