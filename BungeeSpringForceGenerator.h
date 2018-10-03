#ifndef BUNGEESPRINGFORCEGENERATOR_H
#define BUNGEESPRINGFORCEGENERATOR_H

#include "Vect3D.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"

class BungeeSpringForceGenerator : public ParticleForceGenerator
{
  private:
    Particle otherP;
    float k;
    float l0;

  public:
    /* CONSTRUCTEURS ET DESTRUCTEUR */
    BungeeSpringForceGenerator(const Particle &, const float, const float); /* Constructeur par dÃ©faut */
    BungeeSpringForceGenerator(const BungeeSpringForceGenerator &);         /* Constructeur de recopie */
    BungeeSpringForceGenerator(const BungeeSpringForceGenerator *);         /* Constructeur par pointeur */

    virtual void updateForce(Particle *p, float duration);
};

#endif
