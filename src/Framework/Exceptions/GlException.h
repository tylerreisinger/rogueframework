#ifndef GLEXCEPTION_H_
#define GLEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

#include "Framework/GlHeaders.h"

namespace rf
{

class GlException: public rf::Exception
{
public:
	GlException(const std::string& message, GLenum errorCode);
	virtual ~GlException() = default;

protected:
	GLenum m_errorCode;
};

}

#endif
