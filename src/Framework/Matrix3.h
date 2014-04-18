#ifndef MATRIX3_H_
#define MATRIX3_H_

#include "Vector3.h"
#include "Matrix2.h"

namespace rf
{

template<typename T>
class Matrix3
{
public:
	constexpr Matrix3();
	constexpr Matrix3(T m11Val, T m12Val, T m13Val, T m21Val, T m22Val, T m23Val, T m31Val, T m32Val, T m33Val);
	template<typename T2>
	Matrix3(const Matrix3<T2>& matrix);
	template<typename T2>
	Matrix3(const Matrix2<T2>& matrix);
	Matrix3(const Vector3<T>& col1, const Vector3<T>& col2, const Vector3<T>& col3);
	~Matrix3() = default;

	Matrix3(const Matrix3&) = default;
	Matrix3(Matrix3&&) = default;
	Matrix3& operator =(const Matrix3&) = default;
	Matrix3& operator =(Matrix3&&) = default;

	bool operator ==(const Matrix3& matrix) const;
	bool operator !=(const Matrix3& matrix) const;

	Matrix3 operator +(const Matrix3& matrix) const;
	Matrix3 operator -(const Matrix3& matrix) const;
	Matrix3 operator *(const Matrix3& matrix) const;
	Matrix3 operator *(T value) const;
	Matrix3 operator /(T value) const;
	Matrix3 operator -() const;

	Matrix3& operator +=(const Matrix3& matrix);
	Matrix3& operator -=(const Matrix3& matrix);
	Matrix3& operator *=(const Matrix3& matrix);
	Matrix3& operator *=(T value);
	Matrix3& operator /=(T value);

	friend Matrix3 operator *(T value, const Matrix3& matrix) {return matrix * value;}

	void setTranslationPart(T x, T y) {m31 = x; m32 = y;}
	Vector2<T> getTranslationPart() const {return Vector2<T>(m31, m32);}

	double determinant() const;
	Matrix3 inverse() const;
	Matrix3 transpose() const;

	Vector3<T> colX() const {return Vector3<T>(m11, m12, m13);}
	Vector3<T> colY() const {return Vector3<T>(m21, m22, m23);}
	Vector3<T> colZ() const {return Vector3<T>(m31, m32, m33);}

	template<typename T2>
	Vector2<T2> transform(const Vector2<T2>& vector);
	template<typename T2>
	Vector3<T2> transform(const Vector3<T2>& vector);
	template<typename T2>
	Vector2<T2> transformDirection(const Vector2<T2>& vector);

	static Matrix3 orthographicProjection(T left, T right, T bottom, T top);

	static Matrix3 translation(T x, T y);
	static Matrix3 scaling(T x, T y, T z);
	static Matrix3 rotationX(T value);
	static Matrix3 rotationY(T value);
	static Matrix3 rotationZ(T value);
	static Matrix3 rotation(T value, const Vector3<T>& axis);

	static Matrix3 fromRows(const Vector3<T>& row1, const Vector3<T>& row2, const Vector3<T>& row3);

	static constexpr Matrix3 zero();
	static constexpr Matrix3 identity();

	T m11, m12, m13;
	T m21, m22, m23;
	T m31, m32, m33;
};

typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;

template<typename T>
inline constexpr Matrix3<T>::Matrix3():
	m11(1), m12(0), m13(0), m21(0), m22(1), m23(0), m31(0), m32(0), m33(1)
{
}

template<typename T>
inline constexpr Matrix3<T>::Matrix3(T m11Val, T m12Val, T m13Val, T m21Val, T m22Val, T m23Val, T m31Val,
		T m32Val, T m33Val):
	m11(m11Val), m12(m12Val), m13(m13Val), m21(m21Val), m22(m22Val), m23(m23Val),
	m31(m31Val), m32(m32Val), m33(m33Val)
{
}

template<typename T>
template<typename T2>
inline Matrix3<T>::Matrix3(const Matrix3<T2>& matrix):
	m11(matrix.m11), m12(matrix.m12), m13(matrix.m13), m21(matrix.m21), m22(matrix.m22),
	m23(matrix.m23), m31(matrix.m31), m32(matrix.m32), m33(matrix.m33)
{
}

template<typename T>
template<typename T2>
inline Matrix3<T>::Matrix3(const Matrix2<T2>& matrix):
	m11(matrix.m11), m12(matrix.m12), m13(0), m21(matrix.m21), m22(matrix.m22), m23(0),
	m31(0), m32(0), m33(1)
{
}

template<typename T>
inline Matrix3<T>::Matrix3(const Vector3<T>& col1, const Vector3<T>& col2,
		const Vector3<T>& col3):
	m11(col1.x), m12(col1.y), m13(col1.z), m21(col2.x), m22(col2.y), m23(col2.z),
	m31(col3.x), m32(col3.y), m33(col3.z)
{
}

template<typename T>
inline bool Matrix3<T>::operator ==(const Matrix3& matrix) const
{
	return m11 == matrix.m11 && m12 == matrix.m12 && m13 == matrix.m13 && m21 == matrix.m21 &&
				m22 == matrix.m22 && m23 == matrix.m23 && m31 == matrix.m31 && m32 == matrix.m32 &&
				m33 == matrix.m33;
}

template<typename T>
inline bool Matrix3<T>::operator !=(const Matrix3& matrix) const
{
	return m11 != matrix.m11 || m12 != matrix.m12 || m13 != matrix.m13 || m21 != matrix.m21 ||
				m22 != matrix.m22 || m23 != matrix.m23 || m31 != matrix.m31 || m32 != matrix.m32 ||
				m33 != matrix.m33;
}

template<typename T>
inline Matrix3<T> Matrix3<T>::operator +(const Matrix3& matrix) const
{
	return Matrix3(m11 + matrix.m11, m12 + matrix.m12, m13 + matrix.m13,
				   m21 + matrix.m21, m22 + matrix.m22, m23 + matrix.m23,
				   m31 + matrix.m31, m32 + matrix.m32, m33 + matrix.m33);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::operator -(const Matrix3& matrix) const
{
	return Matrix3(m11 - matrix.m11, m12 - matrix.m12, m13 - matrix.m13,
				   m21 - matrix.m21, m22 - matrix.m22, m23 - matrix.m23,
				   m31 - matrix.m31, m32 - matrix.m32, m33 - matrix.m33);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::operator *(const Matrix3& matrix) const
{
	return Matrix3(m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31,
				   m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32,
				   m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33,
				   m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31,
				   m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32,
				   m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33,
				   m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31,
				   m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32,
				   m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::operator *(T value) const
{
	return Matrix3(m11 * value, m12 * value, m13 * value,
				   m21 * value, m22 * value, m23 * value,
				   m31 * value, m32 * value, m33 * value);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::operator /(T value) const
{
	return Matrix3(m11 / value, m12 / value, m13 / value,
				   m21 / value, m22 / value, m23 / value,
				   m31 / value, m32 / value, m33 / value);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::operator -() const
{
	return Matrix3(-m11, -m12, -m13, -m21, -m22, -m23, -m31, -m32, -m33);
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator +=(const Matrix3& matrix)
{
	m11 += matrix.m11;
	m12 += matrix.m12;
	m13 += matrix.m13;
	m21 += matrix.m21;
	m22 += matrix.m22;
	m23 += matrix.m23;
	m31 += matrix.m31;
	m32 += matrix.m32;
	m33 += matrix.m33;
	return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator -=(const Matrix3& matrix)
{
	m11 -= matrix.m11;
	m12 -= matrix.m12;
	m13 -= matrix.m13;
	m21 -= matrix.m21;
	m22 -= matrix.m22;
	m23 -= matrix.m23;
	m31 -= matrix.m31;
	m32 -= matrix.m32;
	m33 -= matrix.m33;
	return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator *=(const Matrix3& matrix)
{
	 m11 = m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31;
	 m12 = m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32;
	 m13 = m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33;
	 m21 = m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31;
	 m22 = m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32;
	 m23 = m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33;
	 m31 = m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31;
	 m32 = m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32;
	 m33 = m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33;
	return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator *=(T value)
{
	m11 *= value;
	m12 *= value;
	m13 *= value;
	m21 *= value;
	m22 *= value;
	m23 *= value;
	m31 *= value;
	m32 *= value;
	m33 *= value;
	return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator /=(T value)
{
	m11 /= value;
	m12 /= value;
	m13 /= value;
	m21 /= value;
	m22 /= value;
	m23 /= value;
	m31 /= value;
	m32 /= value;
	m33 /= value;
	return *this;
}

template<typename T>
inline double Matrix3<T>::determinant() const
{
	return m11 * (m22 * m33 - m32 * m23) - m21 * (m33 * m12 - m32 * m13) + m31 * (m12 * m23 - m22 * m13);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::inverse() const
{
	Matrix3<T> matrix(m22 * m33 - m32 * m23, m32 * m13 - m12 * m33, m12 * m23 - m22 * m13,
				m31 * m23 - m21* m33, m11 * m33 - m31 * m13, m21 * m13 - m11 * m23,
				m21 * m32 - m31 * m22, m31 * m12 - m11 * m32, m11 * m22 - m21 * m12);
	matrix *= (1.0 / determinant());
	return matrix;
}

template<typename T>
inline Matrix3<T> Matrix3<T>::orthographicProjection(T left, T right,
		T bottom, T top)
{
	return Matrix3<T>(2. / (right - left), 0, 0, 0, 2. / (top - bottom), 0, - (right + left) / (right - left), - (top + bottom) / (top - bottom), 1);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::translation(T x, T y)
{
	return Matrix3<T>(1, 0, 0, 0, 1, 0, x, y, 1);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::scaling(T x, T y, T z)
{
	return Matrix3<T>(x, 0, 0, 0, y, 0, 0, 0, z);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::rotationX(T value)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	return Matrix3<T>(1, 0, 0, 0, cosVal, sinVal, 0, -sinVal, cosVal);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::rotationY(T value)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	return Matrix3<T>(cosVal, 0, -sinVal, 0, 1, 0, sinVal, 0, cosVal);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::rotationZ(T value)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	return Matrix3<T>(cosVal, sinVal, 0, -sinVal, cosVal, 0, 0, 0, 1);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::rotation(T value, const Vector3<T>& axis)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	T cosSub1 = 1 - cosVal;
	return Matrix3<T>(cosVal + axis.x * axis.x * cosSub1,
					  axis.y * axis.x * cosSub1 + axis.z * sinVal,
					  axis.z * axis.x * cosSub1 - axis.y * sinVal,
					  axis.x * axis.y * cosSub1 - axis.z * sinVal,
					  cosVal + axis.y * axis.y * cosSub1,
					  axis.z * axis.y * cosSub1 + axis.x * sinVal,
					  axis.x * axis.z * cosSub1 + axis.y * sinVal,
					  axis.y * axis.z * cosSub1 - axis.x * sinVal,
					  cosVal + axis.z * axis.z * cosSub1);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::transpose() const
{
	return Matrix3<T>(m11, m21, m31, m12, m22, m32, m31, m32, m33);
}

template<typename T>
inline Matrix3<T> Matrix3<T>::fromRows(const Vector3<T>& row1,
		const Vector3<T>& row2, const Vector3<T>& row3)

{
	return Matrix3(row1.x, row2.x, row3.x, row1.y, row2.y, row3.y,
			row1.z, row2.z, row3.z);
}

template<typename T>
template<typename T2>
inline Vector2<T2> Matrix3<T>::transform(const Vector2<T2>& vector)
{
	return Vector2<T2>(vector.x * m11 + vector.y * m21 + m31, vector.x * m12 + vector.y * m22 + m32);
}

template<typename T>
template<typename T2>
inline Vector3<T2> Matrix3<T>::transform(const Vector3<T2>& vector)
{
	return Vector2<T2>(vector.x * m11 + vector.y * m21 + vector.z * m31,
					   vector.x * m12 + vector.y * m22 + vector.z * m32,
					   vector.x * m13 + vector.y * m23 + vector.z * m33);
}

template<typename T>
template<typename T2>
inline Vector2<T2> Matrix3<T>::transformDirection(const Vector2<T2>& vector)
{
	return Vector2<T2>(vector.x * m11 + vector.y * m21, vector.x * m12 + vector.y * m22);
}

template<typename T>
inline constexpr Matrix3<T> rf::Matrix3<T>::zero()
{
	return Matrix3<T>(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

template<typename T>
inline constexpr Matrix3<T> rf::Matrix3<T>::identity()
{
	return Matrix3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
}


}


#endif /* MATRIX3_H_ */
