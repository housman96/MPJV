#pragma once
#include "Contact.h"
#include "Primitive.h"

class CollisionData
{
public:
	Contact *contacts;
	int contactsRestants;


	virtual void generateContact(Primitive, Primitive, CollisionData*) = 0;
	CollisionData();
	CollisionData(CollisionData & collisions);
	~CollisionData();
};
