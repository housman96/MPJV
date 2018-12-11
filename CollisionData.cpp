#include "CollisionData.h"



CollisionData::CollisionData()
{
	contacts = NULL;
	contactsRestants = 0;
}

void CollisionData::generateContact(Box box, Plane plan, CollisionData* data) {
	Matrix34 matTemp = box.body->transformMatrix.mult(box.offset);
	//std::cout << matTemp << std::endl;
	//plan.normal.log();
	Vect3* points = new Vect3[8];
	points[0] = Vect3(box.halfSizes.getX(), box.halfSizes.getY(), box.halfSizes.getZ());
	points[1] = Vect3(box.halfSizes.getX(), box.halfSizes.getY(), -box.halfSizes.getZ());
	points[2] = Vect3(box.halfSizes.getX(), -box.halfSizes.getY(), box.halfSizes.getZ());
	points[3] = Vect3(box.halfSizes.getX(), -box.halfSizes.getY(), -box.halfSizes.getZ());
	points[4] = Vect3(-box.halfSizes.getX(), box.halfSizes.getY(), box.halfSizes.getZ());
	points[5] = Vect3(-box.halfSizes.getX(), box.halfSizes.getY(), -box.halfSizes.getZ());
	points[6] = Vect3(-box.halfSizes.getX(), -box.halfSizes.getY(), box.halfSizes.getZ());
	points[7] = Vect3(-box.halfSizes.getX(), -box.halfSizes.getY(), -box.halfSizes.getZ());
	for (int i = 0;i < 8;i++) {
		if (matTemp.mult(points[i]).dot(plan.normal) - plan.offset < 0) {
			if (!data->contacts) {
				data->contacts = new Contact[200];
			}
			points[i].log();
			data->contacts[data->contactsRestants].contactNormal = plan.normal;
			data->contacts[data->contactsRestants].contactPoint = matTemp.mult(points[i]);
			data->contacts[data->contactsRestants].penetration = matTemp.mult(points[i]).dot(plan.normal) - plan.offset;
			data->contactsRestants++;
		}
	}
}

CollisionData::CollisionData(CollisionData &collisions)
{
	contacts = collisions.contacts;
	contactsRestants = collisions.contactsRestants;
}

void CollisionData::Log()
{
	for (int i = 0;i < contactsRestants;i++) {
		contacts[i].Log();
	}
}



CollisionData::~CollisionData()
{
	if (contacts) {
		delete[] contacts;
	}
}

