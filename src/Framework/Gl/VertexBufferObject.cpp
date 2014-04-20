#include "VertexBufferObject.h"

namespace rf
{
namespace gl
{

VertexBufferObject::VertexBufferObject(VertexBufferObject&& other) : VertexBufferObject()
{
	swap(*this, other);
}

VertexBufferObject& VertexBufferObject::operator =(VertexBufferObject&& other)
{
	BufferObject::operator =(std::move(other));
	return *this;
}

#if GL_TARGET_VERSION >= 301
VertexBufferObject::VertexBufferObject(const VertexBufferObject& other) : VertexBufferObject(other.m_usage, other.m_context)
{
	copyBuffer(other);
}

VertexBufferObject& VertexBufferObject::operator =(VertexBufferObject other)
{
	swap(*this, other);
	return *this;
}

}
}

#endif
