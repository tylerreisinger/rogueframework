#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_

#include "Framework/GlHeaders.h"

#include "Texture2d.h"

namespace rf
{
namespace gl
{

class Context
{
public:

	Context();
	virtual ~Context();

	void bindTexture(const Texture2d& texture);



protected:

	const Texture2d* m_boundTexture2d = nullptr;

};

inline void Context::bindTexture(const Texture2d& texture)
{
	if(m_boundTexture2d != &texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture.handle());
		m_boundTexture2d = &texture;
	}
}

}
}

#endif
