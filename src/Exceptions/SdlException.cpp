#include "SdlException.h"

#include <SDL2/SDL.h>

namespace rf
{

SdlException::SdlException(const std::string& what) : Exception(what + std::string(": ") + SDL_GetError())
{
}

}
