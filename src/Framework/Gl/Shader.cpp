#include "Shader.h"

#include <memory>
#include <fstream>

#include "Framework/Gl/Context.h"
#include "Framework/Exceptions/GlException.h"

namespace rf
{
namespace gl
{

Shader::Shader(ShaderType type, Context* context): GlObject(0, context),
	m_type(type)
{
	m_handle = glCreateShader(static_cast<GLenum>(type));
	CHECK_GL_ERROR(glCreateShader);
}

Shader::~Shader()
{
	if(m_handle)
	{
		glDeleteShader(m_handle);
		CHECK_GL_ERROR(glDeleteShader);
	}
}

void Shader::compileSource(const std::string& source)
{
	int size = source.size();
	const char* text = source.c_str();
	glShaderSource(m_handle, 1, &text, &size);
	CHECK_GL_ERROR(glShaderSource);
	glCompileShader(m_handle);
	CHECK_GL_ERROR(glCompileShader);
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
	CHECK_GL_ERROR(glShaderSource);
	glCompileShader(m_handle);
	CHECK_GL_ERROR(glCompileShader);
}

bool Shader::isCompiled() const
{
	GLint out = GL_FALSE;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &out);
	CHECK_GL_ERROR(glGetShaderiv);
	return out == GL_TRUE;
}

std::string Shader::getInfoLog() const
{
	int length = 0;
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	CHECK_GL_ERROR(glGetShaderiv);
	std::string logText;

	if(length > 0)
	{
		std::unique_ptr<char []> text(new char[length]);
		int charsCopied = 0;
		glGetShaderInfoLog(m_handle, length, &charsCopied, text.get());
		CHECK_GL_ERROR(glGetShaderInfoLog);
		logText = text.get();
	}
	return logText;
}

}
}
