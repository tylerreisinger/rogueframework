#ifndef VERTEXARRAYOBJECT_H_
#define VERTEXARRAYOBJECT_H_

#include "GlObject.h"

#include "Framework/GlHeaders.h"

#include "VertexBufferObject.h"

namespace rf
{
namespace gl
{

class IndexBufferObject;

class VertexArrayObject : public GlObject
{
public:

	VertexArrayObject(Context* context);
	virtual ~VertexArrayObject();

	VertexArrayObject(const VertexArrayObject&) = delete;
	VertexArrayObject& operator =(const VertexArrayObject&) = delete;

	VertexArrayObject(VertexArrayObject&& other) noexcept;
	VertexArrayObject& operator =(VertexArrayObject&& other) noexcept;

	void attachVertexBuffer(int attribIndex, int components, VertexBufferObject::ComponentType componentType,
			const VertexBufferObject* buffer, intptr_t dataOffset = 0, int stride = 0,
			bool normalize = false);
	void setIndexBuffer(const IndexBufferObject* buffer);

	virtual void destroy() override;

protected:
};

}
}


#endif /* VERTEXARRAYOBJECT_H_ */
