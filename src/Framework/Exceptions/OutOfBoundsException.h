#ifndef OUTOFBOUNDSEXCEPTION_H_
#define OUTOFBOUNDSEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

namespace rf
{

class OutOfBoundsException: public rf::Exception
{
public:
	OutOfBoundsException(const std::string& message);
	~OutOfBoundsException() = default;
};

}

#endif
