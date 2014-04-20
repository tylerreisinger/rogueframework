#include "Context.h"

#include "Framework/Color.h"

#include "BufferObject.h"

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
}

void Context::setClearColor(const Color& color)
{
	glClearColor(color.red, color.green, color.blue, color.alpha);
}

void Context::bindBuffer(BufferBindTarget target,
		const BufferObject& buffer)
{
	glBindBuffer(static_cast<GLenum>(target), buffer.handle());
	CHECK_GL_ERROR(glBindBuffer);
}

}
}
