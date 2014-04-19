#include "Framework/Exceptions/FileIoException.h"

namespace rf
{

FileIoException::FileIoException(const std::string& fileName,
		const std::string& message)
{
	setMessage(message + ": " + fileName);
}


}
