#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_

#include "Framework/GlHeaders.h"

#include "Texture2d.h"
#include "Framework/Flags.h"

#include "Enums.h"

namespace rf
{
class Color;

namespace gl
{
class BufferObject;
class VertexBufferObject;
class IndexBufferObject;

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

	void bindBuffer(BufferBindTarget target, const BufferObject& buffer);
	void bindBuffer(const VertexBufferObject& buffer);
	void bindBuffer(const IndexBufferObject& buffer);

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

inline void Context::bindBuffer(const VertexBufferObject& buffer)
{
	bindBuffer(BufferBindTarget::ArrayBuffer, reinterpret_cast<const BufferObject&>(buffer));
}

inline void Context::bindBuffer(const IndexBufferObject& buffer)
{
	bindBuffer(BufferBindTarget::IndexBuffer, reinterpret_cast<const BufferObject&>(buffer));
}

}
}

#endif
