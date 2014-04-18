#include "Framework/Exceptions/EnumerationValueException.h"

namespace rf
{

EnumerationValueException::EnumerationValueException(
		const std::string& enumName, const std::string& message)
{
	std::string fullMessage = message + std::string(" with ") + enumName;
	setMessage(fullMessage);
}

}
