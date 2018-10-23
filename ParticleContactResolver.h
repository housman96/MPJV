#ifndef PARTICLECONTACTRESOLVER_H
#define PARTICLECONTACTRESOLVER_H

#include <vector>
#include "ParticleContact.h"
using namespace std;

class ParticleContactResolver
{
private:
	int iteration;
	int iterationUsed;
	vector<ParticleContact*> listContact;

public:
	ParticleContactResolver();
	~ParticleContactResolver();

	void setVector(vector<ParticleContact*>);
	void setIter(int);
	void resolveContact();
};

#endif

