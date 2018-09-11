#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <vector>
#include "Particle.h"

using namespace std;


class Affichage {
private:
	static vector<Particle> list;
	static float lastLoopTime;
	static float timeAccumulatedMs;
	static const int T;
	static const float D;
	static const int G;

public:
	Affichage(int argc, char ** argv, Particle part);
	Affichage(int argc, char ** argv);
	~Affichage();
	Affichage(int argc, char ** argv, vector<Particle> list);

	static void idle(void);
	void refresh(void);
	void setList(vector<Particle> list);
	vector<Particle> getList();
	static void Display();
	static void redim(int width, int height);
};


#endif
