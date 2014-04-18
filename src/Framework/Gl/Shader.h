#ifndef SHADER_H_
#define SHADER_H_

#include "GlObject.h"

#include "Framework/GlHeaders.h"

#include <string>

namespace rf
{
namespace gl
{
class Context;

class Shader : public GlObject
{
public:

	enum class ShaderType : GLenum
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER
	};

	explicit Shader(ShaderType type, Context* context);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator =(const Shader&) = delete;

	Shader(Shader&& other) noexcept;
	Shader& operator =(Shader&& other) noexcept;

	void compileSource(const std::string& source);
	void compileSourceFromFile(const std::string& fileName);

	bool isCompiled() const;

	std::string getInfoLog() const;

	ShaderType type() const {return m_type;}

protected:

	ShaderType m_type;
};

}
}

#endif
