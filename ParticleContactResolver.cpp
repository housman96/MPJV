#include "ParticleContactResolver.h"



ParticleContactResolver::ParticleContactResolver()
{
	this->iteration = 0;
	this->iterationUsed = 0;
}

void ParticleContactResolver::setVector(vector<ParticleContact*> vect) {
	this->listContact = vect;
}

ParticleContactResolver::~ParticleContactResolver()
{
}

void ParticleContactResolver::setIter(int iter) {
	this->iteration = iter;
}

void ParticleContactResolver::resolveContact() {
	bool resolved = false;
	iterationUsed = 0;
	while (!resolved && iteration * 2 >= iterationUsed && iteration != 0) {
		int lowest = 0;
		float lowestValue = 10000;
		for (size_t i = 0; i < listContact.size(); i++)
		{
			float test = listContact[i]->calcVs();
			if (listContact[i]->calcVs() < lowestValue && listContact[i]->calcVs() < 0)
			{
				lowestValue = listContact[i]->calcVs();
				lowest = i;
			}
		}

		if (lowestValue == 10000) {
			resolved = true;
		}
		else {
			listContact[lowest]->resolve();
		}

		iterationUsed++;
	}
}
