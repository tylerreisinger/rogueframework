#include "Context.h"

#include "Framework/Color.h"

#include "BufferObject.h"
#include "TextureArray2d.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"

#include "Framework/Exceptions/GlException.h"

namespace rf
{
namespace gl
{

Context::Context()
{
}

Context::~Context()
{
}

void Context::clear(const Flags<ClearFlags>& flags)
{
	glClear(flags.getRawValue());
	CHECK_GL_ERROR(glClear);
}

void Context::bindTexture(const TextureArray2d& texture)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture.handle());
	CHECK_GL_ERROR(glBindTexture);
}

void Context::bind(const VertexArrayObject& object)
{
	glBindVertexArray(object.handle());
	CHECK_GL_ERROR(glBindVertexArray);
}

void Context::unbindVertexArray()
{
	glBindVertexArray(0);
	CHECK_GL_ERROR(glBindVertexArray);
}

void Context::bindShaderProgram(const ShaderProgram& object)
{
	glUseProgram(object.handle());
	CHECK_GL_ERROR(glUseProgram);
}

void Context::setClearColor(const Color& color)
{
	glClearColor(color.red, color.green, color.blue, color.alpha);
	CHECK_GL_ERROR(glClearColor);
}

void Context::bindBuffer(BufferBindTarget target,
		const BufferObject& buffer)
{
	glBindBuffer(static_cast<GLenum>(target), buffer.handle());
	CHECK_GL_ERROR(glBindBuffer);
}

void Context::drawIndexedPrimitives(PrimitiveType type, int count,
		IndexFormat indexFormat, uintptr_t offset)
{
	glDrawElements(static_cast<GLenum>(type), count, static_cast<GLenum>(indexFormat),
			reinterpret_cast<void*>(offset));
	CHECK_GL_ERROR(glDrawElements);
}

}
}
