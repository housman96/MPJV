#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "constants.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "ParticleContactGenerator.h"
#include "ParticleContactResolver.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;


class GameLoop
{
private:
	static float lastLoopTime;
	static float timeAccumulatedMs;
	static constexpr float deltaT = 16.f; // Temps entre 2 images en ms
	static ParticleContactResolver resolver;

public:
	/* VARIABLES STATIQUES */
	static vector<Particle *> world; // Liste des particules à afficher
	static vector<ParticleContact*> listContact;
	static vector<ParticleContactGenerator*> listContactGenerator;

	/* CONSTRUCTEURS ET DESTRUCTEUR */
	GameLoop(int, char **);
	GameLoop(int, char **, Particle &);
	GameLoop(int, char **, Particle *);
	GameLoop(int, char **, vector<Particle *> &);
	GameLoop(int, char **, vector<Particle *> *);
	~GameLoop();

	/* CALLBACKS D'AFFICHAGE */
	static void display();
	static void redim(int, int);
	static void TimerPhysicsLoop(int);
	static void TimerDrawLoop(int);
};

#endif
