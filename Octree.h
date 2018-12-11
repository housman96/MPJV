#pragma once

#include "Vect3.h"
#include "Rigidbody.h"
#include "Particle.h"
#include "Primitive.h"
#include <vector>

using namespace std;

class Octree
{
public:
	Vect3* bounds;
	vector<Primitive*> children;
	vector<Octree*> nodes;
	int maxChildren;
	int maxDepth;
	int depth;
	Octree();
	Octree(Octree & o);
	Octree(Vect3 * vectPtr, int max, int maxDepth);
	void insert(Primitive * obj);
	int findIndex(Primitive* obj);
	void subdivise();
	vector<Primitive*> retrieve(Primitive * obj);
	~Octree();
	void clear();
};

