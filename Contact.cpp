#include "Contact.h"


void Contact::Log()
{
	std::cout << "===== CONTACT =====" << std::endl;
	std::cout << "contactPoint = ";
	contactPoint.log();
	std::cout << "contactNormal = ";
	contactNormal.log();
	std::cout << "penetration = " << penetration << std::endl;
}
