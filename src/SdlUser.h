#ifndef SDLUSER_H_
#define SDLUSER_H_

#include <SDL2/SDL.h>

#include "Flags.h"

///@brief Base class for SDL2 applications.
///@details Initializes SDL on creation and frees
///resources on deletion.
class SdlUser
{
public:
	enum class InitOption {Timer = SDL_INIT_TIMER, Audio = SDL_INIT_AUDIO, Video = SDL_INIT_VIDEO,
		Joystick = SDL_INIT_JOYSTICK, Events = SDL_INIT_EVENTS};

	explicit SdlUser(const Flags<InitOption>& initOptions);
	virtual ~SdlUser();

	SdlUser(const SdlUser&) = delete;
	SdlUser(SdlUser&&) = delete;
	SdlUser& operator =(const SdlUser&) = delete;
	SdlUser& operator =(SdlUser&&) = delete;

};

#endif
