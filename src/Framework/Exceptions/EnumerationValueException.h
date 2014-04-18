#ifndef ENUMERATIONVALUEEXCEPTION_H_
#define ENUMERATIONVALUEEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

namespace rf
{

class EnumerationValueException: public rf::Exception
{
public:
	EnumerationValueException(const std::string& enumName, const std::string& message);
	virtual ~EnumerationValueException() = default;

	const std::string& enumName() const {return m_enumName;}

protected:
	std::string m_enumName;
};

}

#endif
