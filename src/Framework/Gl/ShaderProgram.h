#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "GlObject.h"

#include "Framework/GlHeaders.h"

#include <vector>
#include <memory>
#include <string>
#include <array>

#include "Framework/Vector2.h"
#include "Framework/Vector3.h"
#include "Framework/Vector4.h"
#include "Framework/Matrix2.h"
#include "Framework/Matrix3.h"
#include "Framework/Matrix4.h"

namespace rf
{
namespace gl
{
class Shader;
class Context;

class ShaderProgram : public GlObject
{
public:
	ShaderProgram(Context* context);
	virtual ~ShaderProgram();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator =(const ShaderProgram&) = delete;

	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator =(ShaderProgram&& other) noexcept;

	void attachShader(std::shared_ptr<Shader> shader);
	void link();

	int getAttributeLocation(const char* name);
	int getAttributeLocation(const std::string& name) {return getAttributeLocation(name.c_str());}

	void bindAttributeLocation(const char* name, int location);
	void bindAttributeLocation(const std::string& name, int location) {return bindAttributeLocation(name.c_str(), location);}

	void enableAttributeArray(int index);
	void disableAttributeArray(int index);

	int getUniformLocation(const char* name);
	int getUniformLocation(const std::string& name) {return getUniformLocation(name.c_str());}

	void bind() const;

	void setUniformValue(int location, int value);
	void setUniformValue(int location, unsigned int value);
	void setUniformValue(int location, float value);
	void setUniformValue(int location, int value1, int value2);
	void setUniformValue(int location, unsigned int value1, unsigned int value2);
	void setUniformValue(int location, float value1, float value2);
	void setUniformValue(int location, int value1, int value2, int value3);
	void setUniformValue(int location, unsigned int value1, unsigned int value2, unsigned int value3);
	void setUniformValue(int location, float value1, float value2, float value3);
	void setUniformValue(int location, int value1, int value2, int value3, int value4);
	void setUniformValue(int location, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4);
	void setUniformValue(int location, float value1, float value2, float value3, float value4);
	void setUniformValue(int location, const Vector2i& value);
	void setUniformValue(int location, const Vector2ui& value);
	void setUniformValue(int location, const Vector2d& value);
	void setUniformValue(int location, const Vector2f& value);
	void setUniformValue(int location, const Vector3i& value);
	void setUniformValue(int location, const Vector3ui& value);
	void setUniformValue(int location, const Vector3d& value);
	void setUniformValue(int location, const Vector3f& value);
	void setUniformValue(int location, const Vector4d& value);
	void setUniformValue(int location, const Vector4f& value);
	void setUniformValue(int location, const Matrix2f& value);
	void setUniformValue(int location, const Matrix2d& value);
	void setUniformValue(int location, const Matrix3f& value);
	void setUniformValue(int location, const Matrix3d& value);
	void setUniformValue(int location, const Matrix4f& value);
	void setUniformValue(int location, const Matrix4d& value);
	void setUniformValue(const char* name, int value);
	void setUniformValue(const char* name, unsigned int value);
	void setUniformValue(const char* name, float value);
	void setUniformValue(const char* name, int value1, int value2);
	void setUniformValue(const char* name, unsigned int value1, unsigned int value2);
	void setUniformValue(const char* name, float value1, float value2);
	void setUniformValue(const char* name, int value1, int value2, int value3);
	void setUniformValue(const char* name, unsigned int value1, unsigned int value2, unsigned int value3);
	void setUniformValue(const char* name, float value1, float value2, float value3);
	void setUniformValue(const char* name, int value1, int value2, int value3, int value4);
	void setUniformValue(const char* name, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4);
	void setUniformValue(const char* name, float value1, float value2, float value3, float value4);
	void setUniformValue(const char* name, const Vector2i& value);
	void setUniformValue(const char* name, const Vector2ui& value);
	void setUniformValue(const char* name, const Vector2d& value);
	void setUniformValue(const char* name, const Vector2f& value);
	void setUniformValue(const char* name, const Vector3i& value);
	void setUniformValue(const char* name, const Vector3ui& value);
	void setUniformValue(const char* name, const Vector3d& value);
	void setUniformValue(const char* name, const Vector3f& value);
	void setUniformValue(const char* name, const Vector4d& value);
	void setUniformValue(const char* name, const Vector4f& value);
	void setUniformValue(const char* name, const Matrix2f& value);
	void setUniformValue(const char* name, const Matrix2d& value);
	void setUniformValue(const char* name, const Matrix3f& value);
	void setUniformValue(const char* name, const Matrix3d& value);
	void setUniformValue(const char* name, const Matrix4f& value);
	void setUniformValue(const char* name, const Matrix4d& value);
	void setUniformValueMatrix2(int location, const float* matrixValues, bool transpose = false);
	void setUniformValueMatrix2(int location, const std::array<float, 4>& matrixValues, bool transpose = false);
	void setUniformValueMatrix3(int location, const float* matrixValues, bool transpose = false);
	void setUniformValueMatrix3(int location, const std::array<float, 9>& matrixValues, bool transpose = false);
	void setUniformValueMatrix4(int location, const float* matrixValues, bool transpose = false);
	void setUniformValueMatrix4(int location, const std::array<float, 16>& matrixValues, bool transpose = false);
	void setUniformValueMatrix2(const char* name, const float* matrixValues, bool transpose = false);
	void setUniformValueMatrix2(const char* name, const std::array<float, 4>& matrixValues, bool transpose = false);
	void setUniformValueMatrix3(const char* name, const float* matrixValues, bool transpose = false);
	void setUniformValueMatrix3(const char* name, const std::array<float, 9>& matrixValues, bool transpose = false);
	void setUniformValueMatrix4(const char* name, const float* matrixValues, bool transpose = false);
	void setUniformValueMatrix4(const char* name, const std::array<float, 16>& matrixValues, bool transpose = false);
	void setUniformValueArray(int location, int components, const int* values, int count);
	template<size_t N>
	void setUniformValueArray(int location, int components, const std::array<int, N>& values);
	void setUniformValueArray(int location, int components, const unsigned int* values, int count);
	template<size_t N>
	void setUniformValueArray(int location, int components, const std::array<unsigned int, N>& values);
	void setUniformValueArray(int location, int components, const float* values, int count);
	template<size_t N>
	void setUniformValueArray(int location, int components, const std::array<float, N>& values);
	void setUniformValueArray(const char* name, int components, const int* values, int count);
	template<size_t N>
	void setUniformValueArray(const char* name, int components, const std::array<int, N>& values);
	void setUniformValueArray(const char* name, int components, const unsigned int* values, int count);
	template<size_t N>
	void setUniformValueArray(const char* name, int components, const std::array<unsigned int, N>& values);
	void setUniformValueArray(const char* name, int components, const float* values, int count);
	template<size_t N>
	void setUniformValueArray(const char* name, int components, const std::array<float, N>& values);

	std::string getInfoLog() const;

	virtual void destroy() override;

protected:
	std::vector<std::shared_ptr<Shader>> m_shaders;
};

inline void ShaderProgram::setUniformValue(const char* name, int value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, unsigned int value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, float value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, int value1, int value2)
{
	setUniformValue(getUniformLocation(name), value1, value2);
}

inline void ShaderProgram::setUniformValue(const char* name, unsigned int value1, unsigned int value2)
{
	setUniformValue(getUniformLocation(name), value1, value2);
}

inline void ShaderProgram::setUniformValue(const char* name, float value1, float value2)
{
	setUniformValue(getUniformLocation(name), value1, value2);
}

inline void ShaderProgram::setUniformValue(const char* name, int value1, int value2, int value3)
{
	setUniformValue(getUniformLocation(name), value1, value2, value3);
}

inline void ShaderProgram::setUniformValue(const char* name, unsigned int value1, unsigned int value2, unsigned int value3)
{
	setUniformValue(getUniformLocation(name), value1, value2, value3);
}

inline void ShaderProgram::setUniformValue(const char* name, float value1, float value2, float value3)
{
	setUniformValue(getUniformLocation(name), value1, value2, value3);
}

inline void ShaderProgram::setUniformValue(const char* name, int value1, int value2, int value3, int value4)
{
	setUniformValue(getUniformLocation(name), value1, value2, value3, value4);
}

inline void ShaderProgram::setUniformValue(const char* name, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4)
{
	setUniformValue(getUniformLocation(name), value1, value2, value3, value4);
}

inline void ShaderProgram::setUniformValue(const char* name, float value1, float value2, float value3, float value4)
{
	setUniformValue(getUniformLocation(name), value1, value2, value3, value4);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector2i& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector2ui& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector2d& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector2<float>& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector3i& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector3ui& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector3d& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector3<float>& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector4d& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Vector4f& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Matrix2f& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Matrix2d& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Matrix3f& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Matrix3d& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Matrix4f& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValue(const char* name, const Matrix4d& value)
{
	setUniformValue(getUniformLocation(name), value);
}

inline void ShaderProgram::setUniformValueMatrix2(int location, const std::array<float, 4>& matrixValues, bool transpose)
{
	setUniformValueMatrix2(location, matrixValues.data(), transpose);
}

inline void ShaderProgram::setUniformValueMatrix3(int location, const std::array<float, 9>& matrixValues, bool transpose)
{
	setUniformValueMatrix3(location, matrixValues.data(), transpose);
}

inline void ShaderProgram::setUniformValueMatrix4(int location, const std::array<float, 16>& matrixValues, bool transpose)
{
	setUniformValueMatrix4(location, matrixValues.data(), transpose);
}

inline void ShaderProgram::setUniformValueMatrix2(const char* name, const float* matrixValues, bool transpose)
{
	setUniformValueMatrix2(getUniformLocation(name), matrixValues, transpose);
}

inline void ShaderProgram::setUniformValueMatrix2(const char* name,
		const std::array<float, 4>& matrixValues, bool transpose)
{
	setUniformValueMatrix2(getUniformLocation(name), matrixValues, transpose);
}

inline void ShaderProgram::setUniformValueMatrix3(const char* name,
		const float* matrixValues, bool transpose)
{
	setUniformValueMatrix3(getUniformLocation(name), matrixValues, transpose);
}

inline void ShaderProgram::setUniformValueMatrix3(const char* name,
		const std::array<float, 9>& matrixValues, bool transpose)
{
	setUniformValueMatrix3(getUniformLocation(name), matrixValues, transpose);
}

inline void ShaderProgram::setUniformValueMatrix4(const char* name,
		const float* matrixValues, bool transpose)
{
	setUniformValueMatrix4(getUniformLocation(name), matrixValues, transpose);
}

inline void ShaderProgram::setUniformValueMatrix4(const char* name,
		const std::array<float, 16>& matrixValues, bool transpose)
{
	setUniformValueMatrix4(getUniformLocation(name), matrixValues, transpose);
}

template<size_t N>
inline void ShaderProgram::setUniformValueArray(int location, int components,
		const std::array<int, N>& values)
{
	setUniformValueArray(location, components, values.data(), N / components);
}

template<size_t N>
inline void ShaderProgram::setUniformValueArray(int location, int components,
		const std::array<unsigned int, N>& values)
{
	setUniformValueArray(location, components, values.data(), N / components);
}

template<size_t N>
inline void ShaderProgram::setUniformValueArray(int location, int components,
		const std::array<float, N>& values)
{
	setUniformValueArray(location, components, values.data(), N / components);
}
/*
void ShaderProgram::setUniformValueArray(const char* name, int components,
		const int* values, int count)
{
	setUniformValueArray(getAttributeLocation(name), components, values, count);
}

void ShaderProgram::setUniformValueArray(const char* name, int components,
		const unsigned int* values, int count)
{
	setUniformValueArray(getAttributeLocation(name), components, values, count);
}

void ShaderProgram::setUniformValueArray(const char* name, int components,
		const float* values, int count)
{
	setUniformValueArray(getAttributeLocation(name), components, values, count);
}
*/
template<size_t N>
inline void ShaderProgram::setUniformValueArray(const char* name,
		int components, const std::array<int, N>& values)
{
	setUniformValueArray(getAttributeLocation(name), components, values);
}

template<size_t N>
inline void ShaderProgram::setUniformValueArray(const char* name,
		int components, const std::array<unsigned int, N>& values)
{
	setUniformValueArray(getAttributeLocation(name), components, values);
}

template<size_t N>
inline void ShaderProgram::setUniformValueArray(const char* name,
		int components, const std::array<float, N>& values)
{
	setUniformValueArray(getAttributeLocation(name), components, values);
}



}
}

#endif
