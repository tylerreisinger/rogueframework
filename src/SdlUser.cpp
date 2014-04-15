#include "SdlUser.h"

SdlUser::SdlUser(const Flags<InitOption>& initOptions)
{
	SDL_Init(static_cast<Uint32>(initOptions.getRawValue()));
}

SdlUser::~SdlUser()
{
	SDL_Quit();
}

