#include "Framework/Exceptions/GlException.h"



namespace rf
{

GlException::GlException(const std::string& message, GLenum errorCode):
	m_errorCode(errorCode)
{
	std::string errorString = reinterpret_cast<const char*>(gluErrorString(errorCode));
	setMessage(message + ": " + errorString);
}

}
