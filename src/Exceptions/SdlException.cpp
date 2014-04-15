#include "SdlException.h"

#include <SDL2/SDL.h>

SdlException::SdlException(const std::string& what) : Exception(what + std::string(": ") + SDL_GetError())
{
}
