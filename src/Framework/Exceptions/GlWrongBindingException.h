#ifndef GLWRONGBINDINGEXCEPTION_H_
#define GLWRONGBINDINGEXCEPTION_H_

#include <Framework/Exceptions/Exception.h>

namespace rf
{

class GlWrongBindingException: public rf::Exception
{
public:
	GlWrongBindingException(const std::string& target);
	virtual ~GlWrongBindingException();
};

}

#endif
