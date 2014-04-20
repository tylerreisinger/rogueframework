#ifndef INDEXBUFFEROBJECT_H_
#define INDEXBUFFEROBJECT_H_

#include "BufferObject.h"

#include "Framework/GlHeaders.h"

namespace rf
{
namespace gl
{

class IndexBufferObject: public BufferObject
{
public:
	enum class IndexFormat
	{
		Byte = GL_BYTE,
		UShort = GL_UNSIGNED_SHORT,
		UInt = GL_UNSIGNED_INT
	};

	IndexBufferObject(UsageType usage, IndexFormat format, Context* context);
	virtual ~IndexBufferObject() {};

#if GL_TARGET_VERSION >= 301
	IndexBufferObject& operator =(IndexBufferObject other);
	IndexBufferObject(const IndexBufferObject& other);
#endif

	IndexBufferObject(IndexBufferObject&& other);
	IndexBufferObject& operator =(IndexBufferObject&& other);

	IndexFormat getIndexFormat() const {return m_format;}
	void setIndexFormat(IndexFormat value) {m_format = value;}

	virtual BufferBindTarget getTarget() const override {return BufferBindTarget::IndexBuffer;}

protected:
	IndexBufferObject() : BufferObject() {};

	IndexFormat m_format = IndexFormat::UShort;
};

}
}

#endif
