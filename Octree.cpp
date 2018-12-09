#include "Octree.h"



Octree::Octree()
{
	depth = 0;
	maxDepth = 1;
	bounds = new Vect3[8];
	maxChildren = 1;
	children = vector<GameObject*>();
	nodes = vector<Octree*>();
}

Octree::Octree(Octree &o) {
	maxChildren = o.maxChildren;
	maxDepth = o.maxDepth;
	depth = o.depth;
	for (size_t i = 0; i < 8; i++)
	{
		bounds[i] = o.bounds[i];
	}

	for (size_t i = 0; i < o.children.size(); i++)
	{
		children[i] = o.children[i];
	}

	for (size_t i = 0; i < 8; i++)
	{
		nodes[i] = o.nodes[i];
	}

}

Octree::Octree(Vect3* vectPtr, int maxChildren, int maxDepth)
{
	depth = 0;
	this->maxDepth = maxDepth;
	bounds = vectPtr;
	this->maxChildren = maxChildren;
	children = vector<GameObject*>();
	nodes = vector<Octree*>();
}

Octree::~Octree()
{
	if (bounds) {
		delete[] bounds;
	}
	if (children.data()) {
		for (size_t i = 0; i < children.size(); i++)
		{
			children[i] = NULL;
			delete children[i];
		}
		children.clear();
	}
	if (nodes.data()) {
		for (size_t i = 0; i < nodes.size(); i++)
		{
			nodes[i] = NULL;
			delete nodes[i];
		}
		nodes.clear();
		//delete[] & nodes;
	}
}

void Octree::clear()
{
	depth = 0;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		nodes[i]->clear();
		delete nodes[i];
	}
	children.clear();
}

int Octree::findIndex(GameObject* obj) {
	int res = 0;
	Vect3 pos = obj->position;
	if (pos.getX() > (bounds[0].getX() + bounds[1].getX()) / 2) {
		res++;
	}
	if (pos.getY() > (bounds[0].getY() + bounds[2].getY()) / 2) {
		res += 2;
	}
	if (pos.getZ() > (bounds[0].getZ() + bounds[4].getZ()) / 2) {
		res += 4;
	}
	return res;
}



void Octree::insert(GameObject* obj) {
	if ((children.size() < maxChildren) || maxDepth < depth) {
		children.push_back(obj);
	}
	else {
		if (nodes.size() == 0) {
			subdivise();
			for (int i = 0; i < children.size();i++) {
				nodes[findIndex(children[i])]->insert(children[i]);
			}
			children.clear();
			children.size();
		}
		nodes[findIndex(obj)]->insert(obj);
	}
}

void Octree::subdivise() {
	Vect3 **vec = new Vect3*[8];

	for (int i = 0;i < 8;i++) {
		vec[i] = new Vect3[8];
	}

	for (int i = 0;i < 8;i++) {
		for (int j = 0; j < 8; j++)
		{
			if (i == j) {
				vec[i][j] = bounds[i];
			}
			else {
				vec[i][j] = bounds[i].add(bounds[j].sub(bounds[i]).scale(1.f / 2.f));
			}
		}
		nodes.push_back(new Octree(vec[i], maxChildren, maxDepth));
		nodes[nodes.size() - 1]->depth = depth + 1;
	}
	delete vec;
}


vector<GameObject*> Octree::retrieve(GameObject* obj) {
	if (nodes.size() != 0) {

		return nodes[findIndex(obj)]->retrieve(obj);
	}
	for (size_t i = 0; i < children.size(); i++)
	{
		if (obj == children[i]) {
			return children;
		}
	}

	return vector<GameObject*>();

}



