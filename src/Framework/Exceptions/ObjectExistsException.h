#ifndef OBJECTEXISTSEXCEPTION_H_
#define OBJECTEXISTSEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

namespace rf
{

class ObjectExistsException: public rf::Exception
{
public:
	ObjectExistsException(const std::string& what);
	virtual ~ObjectExistsException() = default;
};

}

#endif
