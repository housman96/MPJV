#include "ParticleContactResolver.h"


// ============================================================
// CONSTRUCTEURS ET DESTRUCTEURS
// ============================================================

ParticleContactResolver::ParticleContactResolver()
{
	this->iteration = 0;
	this->iterationUsed = 0;
}



ParticleContactResolver::~ParticleContactResolver()
{
	if (listContact.data()) {
		delete[] & listContact;
	}
}

// ============================================================
// ASCESSEURS
// ============================================================


void ParticleContactResolver::setVector(vector<ParticleContact*> vect) {

	listContact.clear();
	listContact = vect;
}

void ParticleContactResolver::setIter(int iter) {
	iteration = iter;
}

// ============================================================
// RESOLUTION DES CONTACTS
// ============================================================

void ParticleContactResolver::resolveContact() {
	bool resolved = false;
	iterationUsed = 0;
	while (!resolved && iteration * 2 >= iterationUsed && iteration != 0) {
		int lowest = 0;
		float lowestValue = std::numeric_limits<float>::max();
		for (size_t i = 0; i < listContact.size(); i++)
		{
			if (listContact[i]->calcVs() < lowestValue && listContact[i]->calcVs() < 0)
			{
				lowestValue = listContact[i]->calcVs();
				lowest = i;
			}
		}

		if (lowestValue == std::numeric_limits<float>::max()) {
			resolved = true;
		}
		else {
			listContact[lowest]->resolve();
		}

		iterationUsed++;
	}
}
