#ifndef VERTEXBUFFEROBJECT_H_
#define VERTEXBUFFEROBJECT_H_

#include "Framework/GlHeaders.h"

#include "BufferObject.h"


namespace rf
{
namespace gl
{

class VertexBufferObject : public BufferObject
{
public:
	enum class ComponentType
	{
		Byte = GL_BYTE,
		UByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UInt = GL_UNSIGNED_INT,
		Float = GL_FLOAT,
		Double = GL_DOUBLE
	};

	VertexBufferObject(UsageType usage, Context* context) : BufferObject(usage, context) {};
	virtual ~VertexBufferObject() {};

#if GL_TARGET_VERSION >= 301
	VertexBufferObject& operator =(VertexBufferObject other);
	VertexBufferObject(const VertexBufferObject& other);
#endif

	VertexBufferObject(VertexBufferObject&& other);
	VertexBufferObject& operator =(VertexBufferObject&& other);

	virtual BufferBindTarget getTarget() const override {return BufferBindTarget::ArrayBuffer;}

	virtual void bind() const override;

protected:
	VertexBufferObject() : BufferObject() {};
};

}
}

#endif /* VERTEXBUFFEROBJECT_H_ */
