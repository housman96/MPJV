#ifndef ANCHOREDSPRINGFORCEGENERATOR_H
#define ANCHOREDSPRINGFORCEGENERATOR_H

#include "Vect3D.h"
#include "ParticleForceGenerator.h"

class AnchoredSpringForceGenerator : public ParticleForceGenerator
{
  private:
    Vect3D point;
    float k;
    float l0;

  public:
    /* CONSTRUCTEURS ET DESTRUCTEUR */
    AnchoredSpringForceGenerator(const Vect3D, const float, const float); /* Constructeur par dÃ©faut */
    AnchoredSpringForceGenerator(const AnchoredSpringForceGenerator &);   /* Constructeur de recopie */
    AnchoredSpringForceGenerator(const AnchoredSpringForceGenerator *);   /* Constructeur par pointeur */

    virtual void updateForce(Particle *p, float duration);
};

#endif
