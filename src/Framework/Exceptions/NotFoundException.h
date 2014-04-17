#ifndef NOTFOUNDEXCEPTION_H_
#define NOTFOUNDEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

namespace rf
{

class NotFoundException: public rf::Exception
{
public:
	NotFoundException(const std::string& what);
	virtual ~NotFoundException() = default;
};

}

#endif
