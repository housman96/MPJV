#pragma once
#include "CollisionData.h"
#include "Box.h"
#include "Plane.h"

class CollisionBoxPlane :CollisionData
{
public:


	void generateContact(Box box, Plane plan, CollisionData* data) {
		Matrix34 matTemp = box.body->transformMatrix.mult(box.offset);
		Vect3* points = new Vect3[8];
		points[0] = Vect3(box.halfSizes.getX(), box.halfSizes.getY(), box.halfSizes.getZ());
		points[1] = Vect3(box.halfSizes.getX(), box.halfSizes.getY(), -box.halfSizes.getZ());
		points[2] = Vect3(box.halfSizes.getX(), -box.halfSizes.getY(), box.halfSizes.getZ());
		points[3] = Vect3(box.halfSizes.getX(), -box.halfSizes.getY(), -box.halfSizes.getZ());
		points[4] = Vect3(-box.halfSizes.getX(), box.halfSizes.getY(), box.halfSizes.getZ());
		points[5] = Vect3(-box.halfSizes.getX(), box.halfSizes.getY(), -box.halfSizes.getZ());
		points[6] = Vect3(-box.halfSizes.getX(), -box.halfSizes.getY(), box.halfSizes.getZ());
		points[7] = Vect3(-box.halfSizes.getX(), -box.halfSizes.getY(), -box.halfSizes.getZ());
		for (int i = 1;i <= 8;i++) {
			if (matTemp.mult(points[i]).dot(plan.normal) + plan.offset < 0) {
				data->contactsRestants++;
				data->contacts->contactNormal = plan.normal;
				data->contacts->contactPoint = points[i];
				data->contacts->penetration = matTemp.mult(points[i]).dot(plan.normal) + plan.offset;
			}
		}
	}
};