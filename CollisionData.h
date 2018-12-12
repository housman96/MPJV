#pragma once
#include "Contact.h"
#include "Primitive.h"
#include "Box.h"
#include "Plane.h"

class CollisionData
{
public:
	Contact *contacts;
	int contactsRestants;

	// CONSTRUCTEURS ET DESTRUCTEUR
	CollisionData();
	CollisionData(CollisionData & collisions);
	~CollisionData();
	
	// METHODES
	static void generateContact(Box box, Plane plan, CollisionData * data);
	void Log();
};
