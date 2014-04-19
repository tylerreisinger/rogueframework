#include "Framework/Exceptions/FreeTypeException.h"

#include <sstream>

namespace rf
{

FreeTypeException::FreeTypeException(const std::string& message, int errorCode):
	m_errorCode(errorCode)
{
	std::stringstream stream;
	stream << message << " error code = " << errorCode;
	setMessage(stream.str());
}

}
