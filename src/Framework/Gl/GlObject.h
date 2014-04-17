#ifndef GLOBJECT_H_
#define GLOBJECT_H_

#include "Framework/GlHeaders.h"

namespace rf
{
namespace gl
{
class Context;

class GlObject
{
public:

	virtual ~GlObject();

	GlObject(const GlObject&) = delete;
	GlObject& operator =(const GlObject&) = delete;

	GlObject(GlObject&& other) noexcept;
	GlObject& operator =(GlObject&& other) noexcept;

	GLuint handle() {return m_handle;}

	static void swap(GlObject& obj1, GlObject& obj2);

protected:
	GlObject();
	GlObject(GLuint handle, Context* context);

	virtual void destroy() = 0;

	GLuint m_handle;
	Context* m_context;

};


}
}

#endif
