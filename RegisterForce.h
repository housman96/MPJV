#ifndef REGISTERFORCE_H
#define REGISTERFORCE_H

#include <vector>
#include "Particle.h"
#include "ParticleForceGenerator.h"


class RegisterForce
{
public:
	struct ForceRecord
	{
		Particle *p;
		ParticleForceGenerator *pfg;
	};

	typedef std::vector<ForceRecord> Register;
};

#endif