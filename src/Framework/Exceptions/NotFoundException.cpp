#include "Framework/Exceptions/NotFoundException.h"

namespace rf
{

NotFoundException::NotFoundException(const std::string& what) : Exception(what)
{
}

}
