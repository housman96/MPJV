#ifndef PARTICLECONTACTRESOLVER_H
#define PARTICLECONTACTRESOLVER_H

#include <vector>
#include <limits>
#include "ParticleContact.h"

using namespace std;


class ParticleContactResolver
{
private:
	int iteration;
	int iterationUsed;
	vector<ParticleContact*> listContact;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	ParticleContactResolver();
	~ParticleContactResolver();

	/* ASCESSEURS */
	void setVector(vector<ParticleContact*>);
	void setIter(int);

	/* MISE A JOUR */
	void resolveContact();
};

#endif

