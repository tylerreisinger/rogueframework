#ifndef MATRIX2_H_
#define MATRIX2_H_

#include <cmath>

#include "Vector2.h"

namespace rf
{

template<typename T>
class Matrix2
{
public:
	constexpr Matrix2() = default;
	constexpr Matrix2(T val11, T val12, T val21, T val22);
	template<typename T2>
	Matrix2(const Matrix2<T2>& matrix);
	Matrix2(const Vector2<T>& col1, const Vector2<T>& col2);
	~Matrix2() = default;

	Matrix2(const Matrix2&) = default;
	Matrix2(Matrix2&&) = default;
	Matrix2& operator =(const Matrix2&) = default;
	Matrix2& operator =(Matrix2&&) = default;

	bool operator ==(const Matrix2& matrix) const;
	bool operator !=(const Matrix2& matrix) const;

	Matrix2 operator +(const Matrix2& matrix) const;
	Matrix2 operator -(const Matrix2& matrix) const;
	Matrix2 operator *(const Matrix2& matrix) const;
	Matrix2 operator *(T value) const;
	Matrix2 operator /(T value) const;
	Matrix2 operator -() const;

	Matrix2& operator +=(const Matrix2& matrix);
	Matrix2& operator -=(const Matrix2& matrix);
	Matrix2& operator *=(const Matrix2& matrix);
	Matrix2& operator *=(T value);
	Matrix2& operator /=(T value);

	friend Matrix2 operator *(T value, const Matrix2& matrix) {return matrix * value;}

	Matrix2 transpose() const;
	Matrix2 inverse() const;

	Vector2<T> colX() const {return Vector2<T>(m11, m12);}
	Vector2<T> colY() const {return Vector2<T>(m21, m22);}

	double determinant() const;

	template<typename T2>
	Vector2<T2> transform(const Vector2<T2>& vector);

	static Matrix2 rotation(double angle);
	static Matrix2 scaling(double scaleX, double scaleY);

	static Matrix2 fromRows(const Vector2<T>& row1, const Vector2<T>& row2);

	static constexpr Matrix2 zero();
	static constexpr Matrix2 identity();


	T m11 = 1;
	T m12 = 0;
	T m21 = 0;
	T m22 = 1;
};

typedef Matrix2<double> Matrix2d;
typedef Matrix2<float> Matrix2f;

template<typename T>
inline constexpr Matrix2<T>::Matrix2(T val11, T val12, T val21, T val22):
	m11(val11), m12(val12), m21(val21), m22(val22)
{
}

template<typename T>
template<typename T2>
inline Matrix2<T>::Matrix2(const Matrix2<T2>& matrix):
	m11(matrix.m11), m12(matrix.m12), m21(matrix.m21), m22(matrix.m22)
{
}

template<typename T>
inline Matrix2<T>::Matrix2(const Vector2<T>& col1, const Vector2<T>& col2):
	m11(col1.x), m12(col1.y), m21(col2.x), m22(col2.y)
{
}

template<typename T>
inline bool Matrix2<T>::operator ==(const Matrix2& matrix) const
{
	return m11 == matrix.m11 && m12 == matrix.m12 && m21 == matrix.m21 && m22 == matrix.m22;
}

template<typename T>
inline bool Matrix2<T>::operator !=(const Matrix2& matrix) const
{
	return !(*this == matrix);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::operator +(const Matrix2& matrix) const
{
	return Matrix2(m11 + matrix.m11,
				   m12 + matrix.m12,
				   m21 + matrix.m21,
				   m22 + matrix.m22);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::operator -(const Matrix2& matrix) const
{
	return Matrix2(m11 - matrix.m11,
				   m12 - matrix.m12,
				   m21 - matrix.m21,
				   m22 - matrix.m22);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::operator *(const Matrix2& matrix) const
{
	return Matrix2(m11 * matrix.m11 + m12 * matrix.m21,
				   m11 * matrix.m12 + m12 * matrix.m22,
				   m21 * matrix.m11 + m22 * matrix.m21,
				   m21 * matrix.m12 + m22 * matrix.m22);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::operator *(T value) const
{
	return Matrix2(m11 * value,
				   m12 * value,
				   m21 * value,
				   m22 * value);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::operator /(T value) const
{
	return Matrix2(m11 / value,
				   m12 / value,
				   m21 / value,
				   m22 / value);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::operator -() const
{
	return Matrix2(-m11, -m12, -m21, -m22);
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator +=(const Matrix2& matrix)
{
	m11 += matrix.m11;
	m12 += matrix.m12;
	m21 += matrix.m21;
	m22 += matrix.m22;
	return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator -=(const Matrix2& matrix)
{
	m11 -= matrix.m11;
	m12 -= matrix.m12;
	m21 -= matrix.m21;
	m22 -= matrix.m22;
	return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator *=(const Matrix2& matrix)
{
	m11 = m11 * matrix.m11 + m12 * matrix.m21;
	m12 = m11 * matrix.m12 + m12 * matrix.m22;
	m21 = m21 * matrix.m21 + m22 * matrix.m21;
	m22 = m21 * matrix.m22 + m22 * matrix.m22;
	return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator *=(T value)
{
	m11 *= value;
	m12 *= value;
	m21 *= value;
	m22 *= value;
	return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator /=(T value)
{
	m11 /= value;
	m12 /= value;
	m21 /= value;
	m22 /= value;
	return *this;
}

template<typename T>
inline Matrix2<T> Matrix2<T>::transpose() const
{
	return Matrix2(m11, m21, m12, m22);
}

template<typename T>
template<typename T2>
inline Vector2<T2> Matrix2<T>::transform(const Vector2<T2>& vector)
{
	return Vector2<T2>(m11 * vector.x + m21 * vector.y, m12 * vector.x + m22 * vector.y);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::rotation(double angle)
{
	const double sinValue = std::sin(angle);
	const double cosValue = std::cos(angle);

	return Matrix2(cosValue, -sinValue, sinValue, cosValue);
}

template<typename T>
inline double Matrix2<T>::determinant() const
{
	return m11 * m22 - m21 * m12;
}

template<typename T>
inline Matrix2<T> Matrix2<T>::inverse() const
{
	double invDet = 1 / determinant();
	return Matrix2(invDet * m22, invDet * -m21, invDet * -m12, invDet * m11);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::scaling(double scaleX, double scaleY)
{
	return Matrix2(scaleX, 0, 0, scaleY);
}

template<typename T>
inline Matrix2<T> Matrix2<T>::fromRows(const Vector2<T>& row1,
		const Vector2<T>& row2)
{
	return Matrix2(row1.x, row2.x, row1.y, row2.y);
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::zero()
{
	return Matrix2<T>(0, 0, 0, 0);
}

template<typename T>
inline constexpr Matrix2<T> Matrix2<T>::identity()
{
	return Matrix2<T>(1, 0, 0, 1);
}

}



#endif /* MATRIX2_H_ */
