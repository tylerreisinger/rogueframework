#include "SdlGlContext.h"

#include "SdlWindow.h"

#include "Framework/Exceptions/SdlException.h"

namespace rf
{

SdlGlContext::SdlGlContext(const SdlWindow& window, const ContextSettings& settings)
{
	applyContextSettings(settings);
	m_context = SDL_GL_CreateContext(window.getHandle());
	if(!m_context)
	{
		throw SdlException("Failed to create OpenGL context");
	}
}

SdlGlContext::~SdlGlContext()
{
	if(m_context != nullptr)
	{
		SDL_GL_DeleteContext(m_context);
	}
}

void SdlGlContext::setVerticalSync(bool enabled)
{
	SDL_GL_SetSwapInterval(enabled == true ? 1 : 0);
}

void SdlGlContext::applyContextSettings(const ContextSettings& settings)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, settings.doubleBuffered == true ? 1 : 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.glMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.glMinorVersion);

	if(settings.depthBufferSize != 0)
	{
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, settings.depthBufferSize);
	}

	if(settings.stencilBufferSize != 0)
	{
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, settings.stencilBufferSize);
	}
}

void SdlGlContext::makeCurrent(const SdlWindow& window)
{
	SDL_GL_MakeCurrent(window.getHandle(), m_context);
}

}


