#ifndef FREETYPEEXCEPTION_H_
#define FREETYPEEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

namespace rf
{

class FreeTypeException: public rf::Exception
{
public:
	FreeTypeException(const std::string& message, int errorCode);
	virtual ~FreeTypeException() = default;

	int errorCode() const {return m_errorCode;}

protected:
	int m_errorCode;
};

}

#endif
