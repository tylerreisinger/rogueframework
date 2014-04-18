#include "Shader.h"

#include <memory>
#include <fstream>

#include "Framework/Gl/Context.h"

namespace rf
{
namespace gl
{

Shader::Shader(ShaderType type, Context* context): GlObject(0, context),
	m_type(type)
{
	m_handle = glCreateShader(static_cast<GLenum>(type));
}

Shader::~Shader()
{
	if(m_handle)
	{
		glDeleteShader(m_handle);
	}
}

void Shader::compileSource(const std::string& source)
{
	int size = source.size();
	const char* text = source.c_str();
	glShaderSource(m_handle, 1, &text, &size);
	glCompileShader(m_handle);
}

Shader::Shader(Shader&& other) noexcept: GlObject(std::move(other)),
	m_type(other.m_type)
{
}

Shader& Shader::operator =(Shader&& other) noexcept
{
	GlObject::operator =(std::move(other));
	m_type = other.m_type;
	return *this;
}

void Shader::compileSourceFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::unique_ptr<char[]> fileData(new char[fileSize]);
	file.read(fileData.get(), fileSize);
	file.close();
	const char* fileDataRaw = fileData.get();
	glShaderSource(m_handle, 1, &fileDataRaw, &fileSize);
	glCompileShader(m_handle);
}

bool Shader::isCompiled() const
{
	GLint out = GL_FALSE;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &out);

	return out == GL_TRUE;
}

std::string Shader::getInfoLog() const
{
	int length = 0;
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	std::string logText;

	if(length > 0)
	{
		std::unique_ptr<char []> text(new char[length]);
		int charsCopied = 0;
		glGetShaderInfoLog(m_handle, length, &charsCopied, text.get());
		logText = text.get();
	}
	return logText;
}

}
}
