#ifndef SPRINGFORCEGENERATOR_H
#define SPRINGFORCEGENERATOR_H

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vect3D.h"

class SpringForceGenerator : public ParticleForceGenerator {
private:
    Particle otherP;
    float k;
    float l0;

public:
    /* CONSTRUCTEURS ET DESTRUCTEUR */
    SpringForceGenerator(const Particle&, const float, const float); /* Constructeur par dÃ©faut */
    SpringForceGenerator(const SpringForceGenerator&); /* Constructeur de recopie */
    SpringForceGenerator(const SpringForceGenerator*); /* Constructeur par pointeur */

    virtual void updateForce(Particle*, float);
};

#endif
