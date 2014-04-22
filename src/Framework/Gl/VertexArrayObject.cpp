#include "VertexArrayObject.h"

#include "VertexBufferObject.h"
#include "IndexBufferObject.h"
#include "Context.h"

#include "Framework/Exceptions/GlException.h"

namespace rf
{
namespace gl
{


VertexArrayObject::VertexArrayObject(Context* context) : GlObject(0, context)
{
	glGenVertexArrays(1, &m_handle);
	CHECK_GL_ERROR(glGenVertexArrays);
}

VertexArrayObject::~VertexArrayObject()
{
	destroy();
}

void VertexArrayObject::attachVertexBuffer(int attribIndex, int components,
		VertexBufferObject::ComponentType componentType, const VertexBufferObject* buffer, intptr_t dataOffset,
		int stride, bool normalize)
{
	glEnableVertexAttribArray(attribIndex);
	CHECK_GL_ERROR(glEnableVertexAttribArray);
	m_context->bindBuffer(*buffer);
	glVertexAttribPointer(attribIndex, components, static_cast<GLenum>(componentType),
			normalize, stride, reinterpret_cast<void*>(dataOffset));
	CHECK_GL_ERROR(glVertexAttribPointer);
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) noexcept: GlObject(std::move(other))
{
}

VertexArrayObject& VertexArrayObject::operator =(VertexArrayObject&& other) noexcept
{
	GlObject::operator =(std::move(other));
	return *this;
}

void VertexArrayObject::setIndexBuffer(const IndexBufferObject* buffer)
{
	m_context->bindBuffer(*buffer);
}

void VertexArrayObject::destroy()
{
	if(m_handle)
	{
		glDeleteVertexArrays(1, &m_handle);
	}
}

void VertexArrayObject::bind() const
{
	m_context->bind(*this);
}

}
}
