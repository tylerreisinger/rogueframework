#include "Framework/Exceptions/ObjectExistsException.h"

namespace rf
{

ObjectExistsException::ObjectExistsException(const std::string& what) : Exception(what)
{
}


}
