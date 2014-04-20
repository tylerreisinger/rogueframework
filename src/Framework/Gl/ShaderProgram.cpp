#include "ShaderProgram.h"

#include "Shader.h"
#include "Context.h"

#include "Framework/Exceptions/GlException.h"

namespace rf
{
namespace gl
{


ShaderProgram::ShaderProgram(Context* context) : GlObject(0, context)
{
	m_handle = glCreateProgram();
	CHECK_GL_ERROR(glCreateProgram);
}

ShaderProgram::~ShaderProgram()
{
	if(m_handle != 0)
	{
		glDeleteProgram(m_handle);
		CHECK_GL_ERROR(glDeleteProgram);
	}
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept: GlObject(std::move(other)),
	m_shaders(std::move(other.m_shaders))
{
}

ShaderProgram& ShaderProgram::operator =(ShaderProgram&& other) noexcept
{
	if(&other != this)
	{
		GlObject::operator =(std::move(other));
		m_shaders = std::move(other.m_shaders);
	}
	return *this;
}

void ShaderProgram::attachShader(std::shared_ptr<Shader>& shader)
{
	glAttachShader(m_handle, shader->handle());
	CHECK_GL_ERROR(glAttachShader);
	m_shaders.push_back(shader);
}

void ShaderProgram::link()
{
	glLinkProgram(m_handle);
	CHECK_GL_ERROR(glLinkProgram);
}

int ShaderProgram::getAttributeLocation(const char* name)
{
	auto ret = glGetAttribLocation(m_handle, name);
	CHECK_GL_ERROR(glGetAttribLocation);
	return ret;
}

void ShaderProgram::bindAttributeLocation(const char* name, int location)
{
	glBindAttribLocation(m_handle, location, name);
	CHECK_GL_ERROR(glBindAttribLocation);
}

void ShaderProgram::enableAttributeArray(int index)
{
	glEnableVertexAttribArray(index);
	CHECK_GL_ERROR(glEnableVertexAttribArray);
}

void ShaderProgram::disableAttributeArray(int index)
{
	glDisableVertexAttribArray(index);
	CHECK_GL_ERROR(glDisableVertexAttribArray);
}

int ShaderProgram::getUniformLocation(const char* name)
{
	auto ret = glGetUniformLocation(m_handle, name);
	CHECK_GL_ERROR(glGetUniformLocation);
	return ret;
}

void ShaderProgram::setUniformValue(int location, int value)
{
	glUniform1i(location, value);
	CHECK_GL_ERROR(glUniform1i);
}

void ShaderProgram::setUniformValue(int location, unsigned int value)
{
	glUniform1ui(location, value);
	CHECK_GL_ERROR(glUniform1ui);
}

void ShaderProgram::setUniformValue(int location, float value)
{
	glUniform1f(location, value);
	CHECK_GL_ERROR(glUniform1f);
}

void ShaderProgram::setUniformValue(int location, int value1, int value2)
{
	glUniform2i(location, value1, value2);
	CHECK_GL_ERROR(glUniform2i);
}

void ShaderProgram::setUniformValue(int location, unsigned int value1,
		unsigned int value2)
{
	glUniform2ui(location, value1, value2);
	CHECK_GL_ERROR(glUniform2ui);
}

void ShaderProgram::setUniformValue(int location, float value1, float value2)
{
	glUniform2f(location, value1, value2);
	CHECK_GL_ERROR(glUniform2f);
}

void ShaderProgram::setUniformValue(int location, int value1, int value2,
		int value3)
{
	glUniform3i(location, value1, value2, value3);
	CHECK_GL_ERROR(glUniform3i);
}

void ShaderProgram::setUniformValue(int location, unsigned int value1,
		unsigned int value2, unsigned int value3)
{
	glUniform3ui(location, value1, value2, value3);
	CHECK_GL_ERROR(glUniform3ui);
}

void ShaderProgram::setUniformValue(int location, float value1, float value2,
		float value3)
{
	glUniform3f(location, value1, value2, value3);
	CHECK_GL_ERROR(glUniform3f);
}

void ShaderProgram::setUniformValue(int location, int value1, int value2,
		int value3, int value4)
{
	glUniform4i(location, value1, value2, value3, value4);
	CHECK_GL_ERROR(glUniform4i);
}

void ShaderProgram::setUniformValue(int location, unsigned int value1,
		unsigned int value2, unsigned int value3, unsigned int value4)
{
	glUniform4ui(location, value1, value2, value3, value4);
	CHECK_GL_ERROR(glUniform4ui);
}

void ShaderProgram::setUniformValue(int location, float value1, float value2,
		float value3, float value4)
{
	glUniform4f(location, value1, value2, value3, value4);
	CHECK_GL_ERROR(glUniform4f);
}

void ShaderProgram::setUniformValue(int location, const Vector2i& value)
{
	glUniform2i(location, value.x, value.y);
	CHECK_GL_ERROR(glUniform2i);
}

void ShaderProgram::setUniformValue(int location, const Vector2ui& value)
{
	glUniform2ui(location, value.x, value.y);
	CHECK_GL_ERROR(glUniform2ui);
}

void ShaderProgram::setUniformValue(int location, const Vector2d& value)
{
	glUniform2f(location, value.x, value.y);
	CHECK_GL_ERROR(glUniform2f);
}

void ShaderProgram::setUniformValue(int location, const Vector2<float>& value)
{
	glUniform2f(location, value.x, value.y);
	CHECK_GL_ERROR(glUniform2f);
}

void ShaderProgram::setUniformValue(int location, const Vector3i& value)
{
	glUniform3i(location, value.x, value.y, value.z);
	CHECK_GL_ERROR(glUniform3i);
}

void ShaderProgram::setUniformValue(int location, const Vector3ui& value)
{
	glUniform3ui(location, value.x, value.y, value.z);
	CHECK_GL_ERROR(glUniform3ui);
}

void ShaderProgram::setUniformValue(int location, const Vector3d& value)
{
	glUniform3f(location, value.x, value.y, value.z);
	CHECK_GL_ERROR(glUniform3f);
}

void ShaderProgram::setUniformValue(int location, const Vector3<float>& value)
{
	glUniform3f(location, value.x, value.y, value.z);
	CHECK_GL_ERROR(glUniform3f);
}

void ShaderProgram::setUniformValue(int location, const Vector4d& value)
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
	CHECK_GL_ERROR(glUniform4f);
}

void ShaderProgram::setUniformValue(int location, const Vector4f& value)
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
	CHECK_GL_ERROR(glUniform4f);
}

void ShaderProgram::setUniformValueMatrix2(int location, const float* matrixValues, bool transpose)
{
	glUniformMatrix2fv(location, 1, transpose, matrixValues);
	CHECK_GL_ERROR(glUniformMatrix2fv);
}

void ShaderProgram::setUniformValueMatrix3(int location,
		const float* matrixValues, bool transpose)
{
	glUniformMatrix3fv(location, 1, transpose, matrixValues);
	CHECK_GL_ERROR(glUniformMatrix3fv);
}

void ShaderProgram::setUniformValueMatrix4(int location,
		const float* matrixValues, bool transpose)
{
	glUniformMatrix4fv(location, 1, transpose, matrixValues);
	CHECK_GL_ERROR(glUniformMatrix4fv);
}

void ShaderProgram::setUniformValueArray(int location, int components,
		const int* values, int count)
{
	switch(components)
	{
	case 1:
		{
			glUniform1iv(location, count, values);
			CHECK_GL_ERROR(glUniform1iv);
			break;
		}
	case 2:
		{
			glUniform2iv(location, count, values);
			CHECK_GL_ERROR(glUniform2iv);
			break;
		}
	case 3:
		{
			glUniform3iv(location, count, values);
			CHECK_GL_ERROR(glUniform3iv);
			break;
		}
	case 4:
		{
			glUniform4iv(location, count, values);
			CHECK_GL_ERROR(glUniform4iv);
			break;
		}
	}
}

void ShaderProgram::setUniformValueArray(int location, int components,
		const unsigned int* values, int count)
{
	switch(components)
	{
	case 1:
		{
			glUniform1uiv(location, count, values);
			CHECK_GL_ERROR(glUniform1uiv);
			break;
		}
	case 2:
		{
			glUniform2uiv(location, count, values);
			CHECK_GL_ERROR(glUniform2uiv);
			break;
		}
	case 3:
		{
			glUniform3uiv(location, count, values);
			CHECK_GL_ERROR(glUniform3uiv);
			break;
		}
	case 4:
		{
			glUniform4uiv(location, count, values);
			CHECK_GL_ERROR(glUniform4uiv);
			break;
		}
	}
}

void ShaderProgram::setUniformValueArray(int location, int components,
		const float* values, int count)
{
	switch(components)
	{
	case 1:
		{
			glUniform1fv(location, count, values);
			CHECK_GL_ERROR(glUniform1fv);
			break;
		}
	case 2:
		{
			glUniform2fv(location, count, values);
			CHECK_GL_ERROR(glUniform2fv);
			break;
		}
	case 3:
		{
			glUniform3fv(location, count, values);
			CHECK_GL_ERROR(glUniform3fv);
			break;
		}
	case 4:
		{
			glUniform4fv(location, count, values);
			CHECK_GL_ERROR(glUniform4fv);
			break;
		}
	}
}

void ShaderProgram::setUniformValue(int location, const Matrix2f& value)
{
	glUniformMatrix2fv(location, 1, false, reinterpret_cast<const float*>(&value));
	CHECK_GL_ERROR(glUniformMatrix2fv);
}

void ShaderProgram::setUniformValue(int location, const Matrix2d& value)
{
	std::array<float, 4> matrixVals = {static_cast<float>(value.m11), static_cast<float>(value.m12),
			static_cast<float>(value.m21), static_cast<float>(value.m22)};
	glUniformMatrix2fv(location, 1, false, matrixVals.data());
	CHECK_GL_ERROR(glUniformMatrix2fv);
}

void ShaderProgram::setUniformValue(int location, const Matrix3f& value)
{
	glUniformMatrix3fv(location, 1, false, reinterpret_cast<const float*>(&value));
	CHECK_GL_ERROR(glUniformMatrix3fv);
}

void ShaderProgram::setUniformValue(int location, const Matrix3d& value)
{
	std::array<float, 9> matrixVals = {
			static_cast<float>(value.m11), static_cast<float>(value.m12), static_cast<float>(value.m13),
			static_cast<float>(value.m21), static_cast<float>(value.m22), static_cast<float>(value.m23),
			static_cast<float>(value.m31), static_cast<float>(value.m32), static_cast<float>(value.m33),
	};
	glUniformMatrix3fv(location, 1, false, matrixVals.data());
	CHECK_GL_ERROR(glUniformMatrix3fv);
}

void ShaderProgram::setUniformValue(int location, const Matrix4f& value)
{
	glUniformMatrix4fv(location, 1, false, reinterpret_cast<const float*>(&value));
	CHECK_GL_ERROR(glUniformMatrix4fv);
}

void ShaderProgram::setUniformValue(int location, const Matrix4d& value)
{
	std::array<float, 16> matrixVals = {
			static_cast<float>(value.m11), static_cast<float>(value.m12), static_cast<float>(value.m13), static_cast<float>(value.m14),
			static_cast<float>(value.m21), static_cast<float>(value.m22), static_cast<float>(value.m23), static_cast<float>(value.m24),
			static_cast<float>(value.m31), static_cast<float>(value.m32), static_cast<float>(value.m33), static_cast<float>(value.m34),
			static_cast<float>(value.m41), static_cast<float>(value.m42), static_cast<float>(value.m43), static_cast<float>(value.m44)
	};
	glUniformMatrix4fv(location, 1, false, matrixVals.data());
	CHECK_GL_ERROR(glUniformMatrix3fv);
}

std::string ShaderProgram::getInfoLog() const
{
	int length = 0;
	glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	CHECK_GL_ERROR(glGetProgramiv);
	std::string logText;

	if(length > 0)
	{
		std::unique_ptr<char []> text(new char[length]);
		int charsCopied = 0;
		glGetProgramInfoLog(m_handle, length, &charsCopied, text.get());
		CHECK_GL_ERROR(glGetProgramInfoLog);
		logText = text.get();
	}
	return logText;
}

}
}
