#include "CollisionData.h"



CollisionData::CollisionData()
{
	contacts = NULL;
	contactsRestants = 0;
}

CollisionData::CollisionData(CollisionData &collisions)
{
	contacts = collisions.contacts;
	contactsRestants = collisions.contactsRestants;
}



CollisionData::~CollisionData()
{
	if (contacts) {
		delete[] contacts;
	}
}

