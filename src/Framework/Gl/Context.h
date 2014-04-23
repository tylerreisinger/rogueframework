#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_

#include "Framework/GlHeaders.h"

#include "Texture2d.h"
#include "Framework/Flags.h"

#include "Framework/Exceptions/GlException.h"

#include "Enums.h"

namespace rf
{
class Colorf;

namespace gl
{
class BufferObject;
class VertexBufferObject;
class IndexBufferObject;
class TextureArray2d;
class VertexArrayObject;
class ShaderProgram;

class Context
{
public:

	enum class Settings : GLenum
	{
		Blend = GL_BLEND,
		CullFace = GL_CULL_FACE,
		DepthTest = GL_DEPTH_TEST,
		Dither = GL_DITHER
	};

	Context();
	virtual ~Context();

	void bindTexture(const Texture2d& texture);
	void bindTexture(const TextureArray2d& texture);

	void bindBuffer(BufferBindTarget target, const BufferObject& buffer);
	void bindBuffer(const VertexBufferObject& buffer);
	void bindBuffer(const IndexBufferObject& buffer);

	void bind(const VertexArrayObject& object);
	void unbindVertexArray();

	void bindShaderProgram(const ShaderProgram& object);

	void clear(const Flags<ClearFlags>& flags);
	void setClearColor(const Colorf& color);

	void setActiveTextureUnit(int index);

	void drawIndexedPrimitives(PrimitiveType type, int count, IndexFormat indexFormat, uintptr_t offset = 0);

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
		CHECK_GL_ERROR(glBindTexture);
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

inline void Context::setActiveTextureUnit(int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	CHECK_GL_ERROR(glActiveTexture);
}


}
}

#endif
