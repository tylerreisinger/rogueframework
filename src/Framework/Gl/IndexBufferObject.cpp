#include "IndexBufferObject.h"

namespace rf
{
namespace gl
{

IndexBufferObject::IndexBufferObject(UsageType usage, IndexFormat format,
		Context* context) : BufferObject(usage, context), m_format(format)
{
}

IndexBufferObject::IndexBufferObject(IndexBufferObject&& other) : IndexBufferObject()
{
	swap(*this, other);
	m_format = other.m_format;
}

IndexBufferObject& IndexBufferObject::operator =(IndexBufferObject&& other)
{
	BufferObject::operator =(std::move(other));
	m_format = other.m_format;
	return *this;
}

#if GL_TARGET_VERSION >= 301
IndexBufferObject::IndexBufferObject(const IndexBufferObject& other) : IndexBufferObject(other.m_usage, other.m_format, other.m_context)
{
	copyBuffer(other);
}

IndexBufferObject& IndexBufferObject::operator =(IndexBufferObject other)
{
	swap(*this, other);
	m_format = other.m_format;
	return *this;
}

void IndexBufferObject::bind() const
{
	m_context->bindBuffer(*this);
}

}
}

#endif
