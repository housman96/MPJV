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

	// CONSTRUCTEURS ET DESTRUCTEUR
	Octree(); // Constructeur par défaut
	Octree(Octree & o); // Constructeur par recopie
	Octree(Vect3 * vectPtr, int max, int maxDepth);
	~Octree(); // Destructeur

	// METHODES
	void insert(Primitive * obj); // Insère une primitive
	int findIndex(Primitive* obj); // Trouve l'index de l'objet
	void subdivise();
	vector<Primitive*> retrieve(Primitive * obj); // Renvoie la liste des objets d'un octree
	void clear(); // Vide l'arbre
};

