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


	CollisionData();
	static void generateContact(Box box, Plane plan, CollisionData * data);
	CollisionData(CollisionData & collisions);
	void Log();
	~CollisionData();
};
