#include "CollisionData.h"


// ============================================================
// CONSTRUCTEURS ET DESTRUCTEURS
// ============================================================

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


// ============================================================
// METHODES
// ============================================================

void CollisionData::generateContact(Box box, Plane plan, CollisionData* data)
{
	Matrix34 worldToLocal = box.body->transformMatrix.mult(box.offset);
	Vect3* points = new Vect3[8];
	points[0] = Vect3(box.halfSizes.getX(), box.halfSizes.getY(), box.halfSizes.getZ());
	points[1] = Vect3(box.halfSizes.getX(), box.halfSizes.getY(), -box.halfSizes.getZ());
	points[2] = Vect3(box.halfSizes.getX(), -box.halfSizes.getY(), box.halfSizes.getZ());
	points[3] = Vect3(box.halfSizes.getX(), -box.halfSizes.getY(), -box.halfSizes.getZ());
	points[4] = Vect3(-box.halfSizes.getX(), box.halfSizes.getY(), box.halfSizes.getZ());
	points[5] = Vect3(-box.halfSizes.getX(), box.halfSizes.getY(), -box.halfSizes.getZ());
	points[6] = Vect3(-box.halfSizes.getX(), -box.halfSizes.getY(), box.halfSizes.getZ());
	points[7] = Vect3(-box.halfSizes.getX(), -box.halfSizes.getY(), -box.halfSizes.getZ());
	for (int i = 0; i < 8; i++) {
		Vect3 localPoint = worldToLocal.mult(points[i]);
		float dist = localPoint.dot(plan.normal) - plan.offset;
		if (dist < 0) {
			if (!data->contacts) {
				data->contacts = new Contact[200];
			}
			data->contacts[data->contactsRestants].contactNormal = plan.normal;
			data->contacts[data->contactsRestants].contactPoint = localPoint;
			data->contacts[data->contactsRestants].penetration = dist;
			data->contactsRestants++;
		}
	}
}

void CollisionData::Log()
{
	for (int i = 0; i < contactsRestants; i++) {
		contacts[i].Log();
	}
	std::cout << std::endl;
}
