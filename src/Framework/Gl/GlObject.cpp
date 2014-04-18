#include "Framework/Gl/GlObject.h"

#include <utility>

namespace rf
{
namespace gl
{

GlObject::GlObject(GlObject&& other) noexcept:
	m_handle(other.m_handle), m_context(other.m_context)
{
	other.m_handle = 0;
}

GlObject& GlObject::operator =(GlObject&& other) noexcept
{
	if(&other != this)
	{
		if(m_handle)
		{
			destroy();
		}
		m_handle = other.m_handle;
		m_context = other.m_context;
		other.m_handle = 0;
	}
	return *this;
}

GlObject::GlObject():
	m_handle(0), m_context(nullptr)
{

}

void GlObject::swap(GlObject& obj1, GlObject& obj2)
{
	std::swap(obj1.m_handle, obj2.m_handle);
	std::swap(obj1.m_context, obj2.m_context);
}

GlObject::GlObject(GLuint handle, Context* context):
	m_handle(handle), m_context(context)
{
}

}
}
