#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "constants.h"
#include "Particle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

class Affichage
{
  private:
	static vector<Particle *> list; /* Liste des particules à afficher */
	static float lastLoopTime;
	static float timeAccumulatedMs;
	static constexpr float deltaT = 16.f; /* Temps entre 2 images en ms */

  public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	Affichage(int argc, char **argv);
	Affichage(int argc, char **argv, Particle &part);
	Affichage(int argc, char **argv, Particle *part);
	Affichage(int argc, char **argv, vector<Particle *> &list);
	Affichage(int argc, char **argv, vector<Particle *> *list);
	~Affichage();

	/* ASCESSEURS */
	vector<Particle *> getList();
	void setList(vector<Particle *> list);

	/* CALLBACKS D'AFFICHAGE */
	static void display();
	static void redim(int width, int height);
	static void idle();
	static void TimerPhysiqueLoop(int value);
	static void TimerDrawLoop(int value);
};

#endif
