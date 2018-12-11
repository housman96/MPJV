#pragma once

#include "Vect3.h"


class Contact
{
public:
	Vect3 contactPoint;
	Vect3 contactNormal;
	float penetration;
	void Log();
	Contact();
};

