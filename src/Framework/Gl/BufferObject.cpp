#include "BufferObject.h"



namespace rf
{
namespace gl
{

BufferObject::BufferObject(UsageType usage, Context* context): GlObject(0, context),
	m_usage(usage)
{
	glGenBuffers(1, &m_handle);
	CHECK_GL_ERROR(glGenBuffers);
}

BufferObject::~BufferObject()
{
	if(m_handle != 0)
	{
		glDeleteBuffers(1, &m_handle);
	}
}

BufferObject::BufferObject(BufferObject&& other) noexcept : BufferObject()
{
	if(&other != this)
	{
		swap(*this, other);
	}
}

BufferObject& BufferObject::operator =(BufferObject&& other) noexcept
{
	if(&other != this)
	{
		GlObject::operator =(std::move(other));
		m_usage = other.m_usage;
		m_size = other.m_size;
		other.m_size = 0;
	}
	return *this;
}

void swap(BufferObject& buffer1, BufferObject& buffer2)
{
	using std::swap;
	swap(buffer1.m_handle, buffer2.m_handle);
	swap(buffer1.m_usage, buffer2.m_usage);
	swap(buffer1.m_size, buffer2.m_size);
	swap(buffer1.m_context, buffer2.m_context);
}

void BufferObject::setData(const void* data, size_t sizeInBytes)
{
	glBufferData(static_cast<GLenum>(getTarget()), sizeInBytes, data, static_cast<GLenum>(m_usage));
	CHECK_GL_ERROR(glBufferData);
	m_size = sizeInBytes;
}

void BufferObject::clear(size_t bufferSize)
{
	glBufferData(static_cast<GLenum>(getTarget()), bufferSize, nullptr, static_cast<GLenum>(m_usage));
	CHECK_GL_ERROR(glBufferData);
	m_size = bufferSize;
}

void BufferObject::setSubData(const void* data, size_t sizeInBytes,
		intptr_t offset)
{
	glBufferSubData(static_cast<GLenum>(getTarget()), offset, sizeInBytes, data);
	CHECK_GL_ERROR(glBufferSubData);
}

#if GL_TARGET_VERSION >= 301
void BufferObject::copyBuffer(const BufferObject& buffer)
{
	clear(buffer.m_size);
	m_context->bindBuffer(BufferBindTarget::CopyReadBuffer, buffer);
	m_context->bindBuffer(BufferBindTarget::CopyWriteBuffer, *this);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, buffer.m_size);
	CHECK_GL_ERROR(glCopyBufferSubData);
	m_size = buffer.m_size;
}

void BufferObject::flushMappedBufferRange(intptr_t startOffset, size_t size)
{
	glFlushMappedBufferRange(static_cast<GLenum>(getTarget()), startOffset, size);
	CHECK_GL_ERROR(glFlushMappedBufferRange);
}

void BufferObject::getData(intptr_t offset, size_t count, char* outBuffer)
{
	glGetBufferSubData(static_cast<GLenum>(getTarget()), offset, count, outBuffer);
	CHECK_GL_ERROR(glGetBufferSubData);
}

void BufferObject::copyBuffer(const BufferObject& buffer, intptr_t sourceOffset, intptr_t destOffset, size_t count)
{
	m_context->bindBuffer(BufferBindTarget::CopyReadBuffer, buffer);
	m_context->bindBuffer(BufferBindTarget::CopyWriteBuffer, *this);

	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, sourceOffset, destOffset, count);
	CHECK_GL_ERROR(glCopyBufferSubData);
}
#endif

void BufferObject::unmap()
{
	glUnmapBuffer(static_cast<GLenum>(getTarget()));
	CHECK_GL_ERROR(glUnmapBuffer);
}

void* BufferObject::mapRaw(intptr_t startOffset, size_t count,
		const Flags<MappingOptions>& access)
{
	auto ret = glMapBufferRange(static_cast<GLenum>(getTarget()), startOffset, count,
				static_cast<GLbitfield>(access.getRawValue()));
	CHECK_GL_ERROR(glMapBufferRange);
	return ret;
}

void BufferObject::allocate(size_t size)
{
	glBufferData(static_cast<GLenum>(getTarget()), size, nullptr, static_cast<GLenum>(m_usage));
	CHECK_GL_ERROR(glBufferData);
	m_size = size;
}

void BufferObject::invalidate()
{
	glBufferData(static_cast<GLenum>(getTarget()), m_size, nullptr, static_cast<GLenum>(m_usage));
	CHECK_GL_ERROR(glBufferData);
}

void BufferObject::destroy()
{
	if(m_handle != 0)
	{
		glDeleteBuffers(1, &m_handle);
	}
}

}
}
