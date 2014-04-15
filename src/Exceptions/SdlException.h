#ifndef SDLEXCEPTION_H_
#define SDLEXCEPTION_H_

#include "Exception.h"

class SdlException: public Exception
{
public:
	SdlException(const std::string& what);
	~SdlException() noexcept = default;
};

#endif
