#ifndef DRAGGENERATOR_H
#define DRAGGENERATOR_H

#include "Vect3D.h"
#include "ParticleForceGenerator.h"

class DragGenerator : public ParticleForceGenerator
{
private:
  float k1;
  float k2;

public:
  /* CONSTRUCTEURS ET DESTRUCTEUR */
  DragGenerator(const float &, const float &);
  DragGenerator(const DragGenerator &other);
  DragGenerator(const DragGenerator *other);

  virtual void updateForce(Particle *p, float duration);
};

#endif
