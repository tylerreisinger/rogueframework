#ifndef FILEIOEXCEPTION_H_
#define FILEIOEXCEPTION_H_

#include "Framework/Exceptions/Exception.h"

namespace rf
{

class FileIoException: public rf::Exception
{
public:
	FileIoException(const std::string& fileName, const std::string& message);
	virtual ~FileIoException() = default;

	const std::string& fileName() const {return m_fileName;}

protected:
	std::string m_fileName;
};

}

#endif
