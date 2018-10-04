#ifndef STIFFSPRINGFORCEGENERATOR_H
#define STIFFSPRINGFORCEGENERATOR_H

#include "Vect3D.h"
#include "ParticleForceGenerator.h"

class StiffSpringForceGenerator : public ParticleForceGenerator
{
private:
  Vect3D anchorPos;
  float k;
  float d;

public:
  /* CONSTRUCTEURS ET DESTRUCTEUR */
  StiffSpringForceGenerator(const Vect3D, const float, const float); /* Constructeur par dÃ©faut */
  StiffSpringForceGenerator(const StiffSpringForceGenerator &);      /* Constructeur de recopie */
  StiffSpringForceGenerator(const StiffSpringForceGenerator *);      /* Constructeur par pointeur */

  virtual void updateForce(Particle *p, float duration);
};

#endif
