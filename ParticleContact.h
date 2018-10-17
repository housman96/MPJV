#include "Particle.h"
#include "Vect3D.h"

class ParticleContact {
private:
	Particle *particles[2]; /* Les deux particules en contact */
	float c;                /* Coefficient de restitution */
	float d;                /* Interpenetration */
	Vect3D n;               /* Normale au point de contact */

public:
	ParticleContact(Particle &, Particle &, float);
	void resolve(float);
	float calcVs();
	void resolveVelocity();
	void resolveInterpenetration();
};
