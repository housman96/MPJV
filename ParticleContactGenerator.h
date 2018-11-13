#ifndef PARTICLECONTACTGENERATOR_H
#define PARTICLECONTACTGENERATOR_H


class ParticleContactGenerator
{
public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	ParticleContactGenerator();
	~ParticleContactGenerator();

	/* MISE A JOUR */
	virtual void addContact();
};

#endif

