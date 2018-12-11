#include "Contact.h"


void Contact::Log()
{
	std::cout << "contactPoint" << std::endl;
	contactPoint.log();
	std::cout << "contactNormal" << std::endl;
	contactNormal.log();
	std::cout << "penetration=" << penetration << std::endl;
}

Contact::Contact()
{
}
