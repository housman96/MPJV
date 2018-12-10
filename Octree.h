#pragma once

#include "Vect3.h"
#include "Rigidbody.h"
#include "Particle.h"
#include <vector>

using namespace std;

class Octree
{
public:
	Vect3* bounds;
	vector<GameObject*> children;
	vector<Octree*> nodes;
	int maxChildren;
	int maxDepth;
	int depth;
	Octree();
	Octree(Octree & o);
	Octree(Vect3 * vectPtr, int max, int maxDepth);
	void insert(GameObject * obj);
	int findIndex(GameObject* obj);
	void subdivise();
	vector<GameObject*> retrieve(GameObject * obj);
	~Octree();
	void clear();
};

