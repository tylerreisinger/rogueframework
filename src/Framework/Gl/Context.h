#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_

#include "Framework/GlHeaders.h"

#include "Texture2d.h"
#include "Framework/Flags.h"

namespace rf
{
class Color;
namespace gl
{

enum class ClearFlags : GLbitfield
{
	ColorBuffer = GL_COLOR_BUFFER_BIT,
	DepthBuffer = GL_DEPTH_BUFFER_BIT,
	StencilBuffer = GL_STENCIL_BUFFER_BIT
};

class Context
{
public:

	enum class Settings : GLenum
	{
		DepthTest = GL_DEPTH_TEST,
		Dither = GL_DITHER
	};

	Context();
	virtual ~Context();

	void bindTexture(const Texture2d& texture);

	void clear(const Flags<ClearFlags>& flags);
	void setClearColor(const Color& color);

	void enable(Settings setting) {glEnable(static_cast<GLenum>(setting));}
	void disable(Settings setting) {glDisable(static_cast<GLenum>(setting));}

protected:

	const Texture2d* m_boundTexture2d = nullptr;

};

inline void Context::bindTexture(const Texture2d& texture)
{
	if(m_boundTexture2d != &texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture.handle());
		m_boundTexture2d = &texture;
	}
}

}
}

#endif
