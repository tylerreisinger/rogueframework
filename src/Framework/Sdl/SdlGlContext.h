#ifndef SDLGLCONTEXT_H_
#define SDLGLCONTEXT_H_

#include "Framework/Gl/Context.h"

#include <SDL2/SDL.h>

namespace rf
{

class SdlWindow;

class SdlGlContext : public gl::Context
{
public:

	struct ContextSettings
	{
		bool doubleBuffered = false;
		int depthBufferSize = 0;
		int stencilBufferSize = 0;

		int glMajorVersion = 1;
		int glMinorVersion = 1;
	};


	SdlGlContext(const SdlWindow& window, const ContextSettings& settings);
	virtual ~SdlGlContext();

	SdlGlContext(const SdlGlContext&) = delete;
	SdlGlContext(SdlGlContext&&) = delete;

	SdlGlContext& operator =(const SdlGlContext&) = delete;
	SdlGlContext& operator =(SdlGlContext&&) = delete;

	void makeCurrent(const SdlWindow& window);

	void setVerticalSync(bool enabled);

	void display();

protected:

	void applyContextSettings(const ContextSettings& settings);

	SDL_GLContext m_context;
};

}

#endif
