#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Matrix3.h"
#include "Vector4.h"

namespace rf
{

template<typename T>
class Matrix4
{
public:
	constexpr Matrix4();
	template<typename T2>
	Matrix4(const Matrix3<T2>& matrix);
	template<typename T2>
	Matrix4(const Matrix4<T2>& matrix);
	constexpr Matrix4(T m11Val, T m12Val, T m13Val, T m14Val, T m21Val, T m22Val, T m23Val, T m24Val,
			T m31Val, T m32Val, T m33Val, T m34Val, T m41Val, T m42Val, T m43Val, T m44Val);
	Matrix4(const Vector4<T>& col1, const Vector4<T>& col2, const Vector4<T>& col3, const Vector4<T>& col4);
	~Matrix4() = default;

	Matrix4(const Matrix4&) = default;
	Matrix4(Matrix4&&) = default;
	Matrix4& operator =(const Matrix4&) = default;
	Matrix4& operator =(Matrix4&&) = default;

	bool operator ==(const Matrix4& matrix) const;
	bool operator !=(const Matrix4& matrix) const;

	Matrix4 operator +(const Matrix4& matrix) const;
	Matrix4 operator -(const Matrix4& matrix) const;
	Matrix4 operator *(const Matrix4& matrix) const;
	Matrix4 operator *(T value) const;
	Matrix4 operator /(T value) const;
	Matrix4 operator -() const;

	Matrix4& operator +=(const Matrix4& matrix);
	Matrix4& operator -=(const Matrix4& matrix);
	Matrix4& operator *=(const Matrix4& matrix);
	Matrix4& operator *=(T value);
	Matrix4& operator /=(T value);

	friend Matrix4 operator *(T value, const Matrix4& matrix) {return matrix * value;}

	void setTranslationPart(T x, T y, T z) {m41 = x; m42 = y; m43 = z;}
	Vector3<T> getTranslationPart() const {return Vector3<T>(m41, m42, m43);}

	double determinant() const;
	Matrix4 inverse() const;
	Matrix4 transpose() const;

	Vector4<T> colX() const {return Vector4<T>(m11, m12, m13, m14);}
	Vector4<T> colY() const {return Vector4<T>(m21, m22, m23, m24);}
	Vector4<T> colZ() const {return Vector4<T>(m31, m32, m33, m34);}
	Vector4<T> colW() const {return Vector4<T>(m41, m42, m43, m44);}

	template<typename T2>
	Vector3<T2> transform(const Vector3<T2>& vector);
	template<typename T2>
	Vector4<T2> transform(const Vector4<T2>& vector);
	template<typename T2>
	Vector3<T2> transformDirection(const Vector3<T2>& vector);

	static Matrix4 orthographicProjection(T left, T right, T bottom, T top, T near, T far);

	static Matrix4 translation(T x, T y, T z);
	static Matrix4 scaling(T x, T y, T z);
	static Matrix4 rotationX(T value);
	static Matrix4 rotationY(T value);
	static Matrix4 rotationZ(T value);
	static Matrix4 rotation(T value, const Vector3<T>& axis);

	static Matrix4 fromRows(const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3, const Vector4<T>& row4);

	static constexpr Matrix4 zero() {return Matrix4<T>(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);}
	static constexpr Matrix4 identity() {return Matrix4<T>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);}

	T m11, m12, m13, m14;
	T m21, m22, m23, m24;
	T m31, m32, m33, m34;
	T m41, m42, m43, m44;
};

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;

template<typename T>
inline constexpr Matrix4<T>::Matrix4():
	m11(1), m12(0), m13(0), m14(0), m21(0), m22(1), m23(0), m24(0), m31(0), m32(0), m33(1),
	m34(0), m41(0), m42(0), m43(0), m44(1)
{
}

template<typename T>
template<typename T2>
inline Matrix4<T>::Matrix4(const Matrix4<T2>& matrix):
	m11(matrix.m11), m12(matrix.m12), m13(matrix.m13), m14(matrix.m14),
	m21(matrix.m21), m22(matrix.m22), m23(matrix.m23), m24(matrix.m24),
	m31(matrix.m31), m32(matrix.m32), m33(matrix.m33), m34(matrix.m34),
	m41(matrix.m41), m42(matrix.m42), m43(matrix.m43), m44(matrix.m44)
{
}

template<typename T>
inline constexpr Matrix4<T>::Matrix4(T m11Val, T m12Val, T m13Val, T m14Val, T m21Val,
		T m22Val, T m23Val, T m24Val, T m31Val, T m32Val, T m33Val, T m34Val,
		T m41Val, T m42Val, T m43Val, T m44Val):
	m11(m11Val), m12(m12Val), m13(m13Val), m14(m14Val), m21(m21Val), m22(m22Val), m23(m23Val), m24(m24Val),
	m31(m31Val), m32(m32Val), m33(m33Val), m34(m34Val), m41(m41Val), m42(m42Val), m43(m43Val), m44(m44Val)
{
}

template<typename T>
template<typename T2>
inline Matrix4<T>::Matrix4(const Matrix3<T2>& matrix):
	m11(matrix.m11), m12(matrix.m12), m13(matrix.m13), m14(0),
	m21(matrix.m21), m22(matrix.m22), m23(matrix.m23), m24(0),
	m31(matrix.m31), m32(matrix.m32), m33(matrix.m33), m34(0),
	m41(0), m42(0), m43(0), m44(1)
{
}

template<typename T>
inline Matrix4<T>::Matrix4(const Vector4<T>& col1, const Vector4<T>& col2,
		const Vector4<T>& col3, const Vector4<T>& col4):
	m11(col1.x), m12(col1.y), m13(col1.z), m14(col1.w),
	m21(col2.x), m22(col2.y), m23(col2.z), m24(col2.w),
	m31(col3.x), m32(col3.y), m33(col3.z), m34(col3.w),
	m41(col4.x), m42(col4.y), m43(col4.z), m44(col4.w)
{
}

template<typename T>
inline bool Matrix4<T>::operator ==(const Matrix4& matrix) const
{
	return m11 == matrix.m11 && m12 == matrix.m12 && m13 == matrix.m13 && m14 == matrix.m14 &&
		   m21 == matrix.m21 && m22 == matrix.m22 && m23 == matrix.m23 && m24 == matrix.m24 &&
		   m31 == matrix.m31 && m32 == matrix.m32 && m33 == matrix.m33 && m34 == matrix.m34 &&
		   m41 == matrix.m41 && m42 == matrix.m42 && m43 == matrix.m43 && m44 == matrix.m44;
}

template<typename T>
inline bool Matrix4<T>::operator !=(const Matrix4& matrix) const
{
	return !(*this == matrix);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator +(const Matrix4& matrix) const
{
	return Matrix4<T>(m11 + matrix.m11, m12 + matrix.m12, m13 + matrix.m13, m14 + matrix.m14,
				   m21 + matrix.m21, m22 + matrix.m22, m23 + matrix.m23, m24 + matrix.m24,
				   m31 + matrix.m31, m32 + matrix.m32, m33 + matrix.m33, m34 + matrix.m34,
				   m41 + matrix.m41, m42 + matrix.m42, m43 + matrix.m43, m44 + matrix.m44);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator -(const Matrix4& matrix) const
{
	return Matrix4<T>(m11 - matrix.m11, m12 - matrix.m12, m13 - matrix.m13, m14 - matrix.m14,
				   m21 - matrix.m21, m22 - matrix.m22, m23 - matrix.m23, m24 - matrix.m24,
				   m31 - matrix.m31, m32 - matrix.m32, m33 - matrix.m33, m34 - matrix.m34,
				   m41 - matrix.m41, m42 - matrix.m42, m43 - matrix.m43, m44 - matrix.m44);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator *(const Matrix4& matrix) const
{
	return Matrix4<T>(m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31 + m14 * matrix.m41,
				   m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32 + m14 * matrix.m42,
				   m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33 + m14 * matrix.m43,
				   m11 * matrix.m14 + m12 * matrix.m24 + m13 * matrix.m34 + m14 * matrix.m44,
				   m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31 + m24 * matrix.m41,
				   m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32 + m24 * matrix.m42,
				   m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33 + m24 * matrix.m43,
				   m21 * matrix.m14 + m22 * matrix.m24 + m23 * matrix.m34 + m24 * matrix.m44,
				   m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31 + m34 * matrix.m41,
				   m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32 + m34 * matrix.m42,
				   m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33 + m34 * matrix.m43,
				   m31 * matrix.m14 + m32 * matrix.m24 + m33 * matrix.m34 + m34 * matrix.m44,
				   m41 * matrix.m11 + m42 * matrix.m21 + m43 * matrix.m31 + m44 * matrix.m41,
				   m41 * matrix.m12 + m42 * matrix.m22 + m43 * matrix.m32 + m44 * matrix.m42,
				   m41 * matrix.m13 + m42 * matrix.m23 + m43 * matrix.m33 + m44 * matrix.m43,
				   m41 * matrix.m14 + m42 * matrix.m24 + m43 * matrix.m34 + m44 * matrix.m44);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator *(T value) const
{
	return Matrix4<T>(m11 * value, m12 * value, m13 * value, m14 * value,
				   m21 * value, m22 * value, m23 * value, m24 * value,
				   m31 * value, m32 * value, m33 * value, m34 * value,
				   m41 * value, m42 * value, m43 * value, m44 * value);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator /(T value) const
{
	return Matrix4<T>(m11 / value, m12 / value, m13 / value, m14 / value,
				   m21 / value, m22 / value, m23 / value, m24 / value,
				   m31 / value, m32 / value, m33 / value, m34 / value,
				   m41 / value, m42 / value, m43 / value, m44 / value);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator -() const
{
	return Matrix4<T>(-m11, -m12, -m13, -m14, -m21, -m22, -m23, -m24, -m31, -m32,
			-m33, -m34, -m41, -m42, -m43, -m44);
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator +=(const Matrix4& matrix)
{
	m11 += matrix.m11;
	m12 += matrix.m12;
	m13 += matrix.m13;
	m14 += matrix.m14;
	m21 += matrix.m21;
	m22 += matrix.m22;
	m23 += matrix.m23;
	m24 += matrix.m24;
	m31 += matrix.m31;
	m32 += matrix.m32;
	m33 += matrix.m33;
	m34 += matrix.m34;
	m41 += matrix.m41;
	m42 += matrix.m42;
	m43 += matrix.m43;
	m44 += matrix.m44;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator -=(const Matrix4& matrix)
{
	m11 -= matrix.m11;
	m12 -= matrix.m12;
	m13 -= matrix.m13;
	m14 -= matrix.m14;
	m21 -= matrix.m21;
	m22 -= matrix.m22;
	m23 -= matrix.m23;
	m24 -= matrix.m24;
	m31 -= matrix.m31;
	m32 -= matrix.m32;
	m33 -= matrix.m33;
	m34 -= matrix.m34;
	m41 -= matrix.m41;
	m42 -= matrix.m42;
	m43 -= matrix.m43;
	m44 -= matrix.m44;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator *=(const Matrix4& matrix)
{
	m11 = m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31 + m14 * matrix.m41;
	m12 = m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32 + m14 * matrix.m42;
	m13 = m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33 + m14 * matrix.m43;
	m14 = m11 * matrix.m14 + m12 * matrix.m24 + m13 * matrix.m34 + m14 * matrix.m44;
	m21 = m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31 + m24 * matrix.m41;
	m22 = m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32 + m24 * matrix.m42;
	m23 = m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33 + m24 * matrix.m43;
	m24 = m21 * matrix.m14 + m22 * matrix.m24 + m23 * matrix.m34 + m24 * matrix.m44;
	m31 = m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31 + m34 * matrix.m41;
	m32 = m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32 + m34 * matrix.m42;
	m33 = m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33 + m34 * matrix.m43;
	m34 = m31 * matrix.m14 + m32 * matrix.m24 + m33 * matrix.m34 + m34 * matrix.m44;
	m41 = m41 * matrix.m11 + m42 * matrix.m21 + m43 * matrix.m31 + m44 * matrix.m41;
	m42 = m41 * matrix.m12 + m42 * matrix.m22 + m43 * matrix.m32 + m44 * matrix.m42;
	m43 = m41 * matrix.m13 + m42 * matrix.m23 + m43 * matrix.m33 + m44 * matrix.m43;
	m44 = m41 * matrix.m14 + m42 * matrix.m24 + m43 * matrix.m34 + m44 * matrix.m44;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator *=(T value)
{
	m11 *= value;
	m12 *= value;
	m13 *= value;
	m14 *= value;
	m21 *= value;
	m22 *= value;
	m23 *= value;
	m24 *= value;
	m31 *= value;
	m32 *= value;
	m33 *= value;
	m34 *= value;
	m41 *= value;
	m42 *= value;
	m43 *= value;
	m44 *= value;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator /=(T value)
{
	m11 /= value;
	m12 /= value;
	m13 /= value;
	m14 /= value;
	m21 /= value;
	m22 /= value;
	m23 /= value;
	m24 /= value;
	m31 /= value;
	m32 /= value;
	m33 /= value;
	m34 /= value;
	m41 /= value;
	m42 /= value;
	m43 /= value;
	m44 /= value;
	return *this;
}

template<typename T>
inline double Matrix4<T>::determinant() const
{
	return (m11 * m22 - m12 * m21) * (m33 * m44 - m34 * m43) - (m13 * m24 - m14 * m23) * (m31 * m42 - m32 * m41);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::inverse() const
{
	T s0 = m11 * m22 - m12 * m12;
	T s1 = m11 * m23 - m12 * m13;
	T s2 = m11 * m24 - m12 * m14;
	T s3 = m12 * m23 - m22 * m12;
	T s4 = m12 * m24 - m22 * m13;
	T s5 = m13 * m24 - m23 * m14;

	T c5 = m33 * m44 - m34 * m34;
	T c4 = m23 * m44 - m24 * m34;
	T c3 = m23 * m34 - m24 * m33;
	T c2 = m13 * m44 - m14 * m34;
	T c1 = m13 * m34 - m14 * m33;
	T c0 = m13 * m24 - m14 * m23;

	double invDet = 1. / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

	return Matrix4<T>((m22 * c5 - m32 * c4 + m42 * c3) * invDet,
				   (-m12 * c5 + m32 * c2 - m42 * c1) * invDet,
				   (m12 * c4 - m22 * c2 + m42 * c0) * invDet,
				   (-m12 * c3 + m22 * c1 - m32 * c0) * invDet,
				   (-m21 * c5 + m31 * c4 - m41 * c3) * invDet,
				   (m11 * c5 - m31 * c2 + m41 * c1) * invDet,
				   (-m11 * c4 + m21 * c2 - m41 * c0) * invDet,
				   (m11 * c3 - m21 * c1 + m31 * c0) * invDet,
				   (m24 * s5 - m34 * s4 + m44 * s3) * invDet,
				   (-m14 * s5 + m34 * s2 - m44 * s1) * invDet,
				   (m14 * s4 - m24 * s2 + m44 * s0) * invDet,
				   (-m14 * s3 + m24 * s1 - m34 * s0) * invDet,
				   (-m23 * s5 + m33 * s4 - m43 * s3) * invDet,
				   (m13 * s5 - m33 * s2 + m43 * s1) * invDet,
				   (-m13 * s4 + m23 * s2 - m43 * s0) * invDet,
				   (m13 * s3 - m23 * s1 + m33 * s0) * invDet);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::transpose() const
{
	return Matrix4<T>(m11, m21, m31, m41, m12, m22, m32, m42, m13, m23, m33, m43, m14, m24, m34, m44);
}
template<typename T>
inline Matrix4<T> Matrix4<T>::fromRows(const Vector4<T>& row1,
		const Vector4<T>& row2, const Vector4<T>& row3, const Vector4<T>& row4)
{
	return Matrix4<T>(row1.x, row2.x, row3.x, row4.x, row1.y, row2.y, row3.y, row4.y,
				   row1.z, row2.z, row3.z, row4.z, row1.w, row2.w, row3.w, row4.w);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::translation(T x, T y, T z)
{
	return Matrix4<T>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::scaling(T x, T y, T z)
{
	return Matrix4<T>(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::rotationX(T value)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	return Matrix4<T>(1, 0, 0, 0, 0, cosVal, sinVal, 0, 0, -sinVal, cosVal, 0, 0, 0, 0, 1);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::rotationY(T value)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	return Matrix4<T>(cosVal, 0, -sinVal, 0, 0, 1, 0, 0, sinVal, 0, cosVal, 0, 0, 0, 0, 1);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::rotationZ(T value)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	return Matrix4<T>(cosVal, sinVal, 0, 0, -sinVal, cosVal, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::rotation(T value, const Vector3<T>& axis)
{
	T cosVal = std::cos(value);
	T sinVal = std::sin(value);
	T cosSub1 = 1 - cosVal;
	return Matrix4<T>(cosVal + axis.x * axis.x * cosSub1,
					  axis.y * axis.x * cosSub1 + axis.z * sinVal,
					  axis.z * axis.x * cosSub1 - axis.y * sinVal,
					  0,
					  axis.x * axis.y * cosSub1 - axis.z * sinVal,
					  cosVal + axis.y * axis.y * cosSub1,
					  axis.z * axis.y * cosSub1 + axis.x * sinVal,
					  0,
					  axis.x * axis.z * cosSub1 + axis.y * sinVal,
					  axis.y * axis.z * cosSub1 - axis.x * sinVal,
					  cosVal + axis.z * axis.z * cosSub1,
					  0,
					  0,
					  0,
					  0,
					  1);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::orthographicProjection(T left, T right, T bottom,
		T top, T near, T far)
{
	return Matrix4<T>(2 / (right - left), 0, 0, 0, 0, 2 / (top - bottom), 0, 0, 0, 0, -2 (far - near), 0,
			-(right + left) / (right - left), - (top + bottom) / (top - bottom), - (far + near) / (far - near), 1);
}


template<typename T>
template<typename T2>
inline Vector3<T2> Matrix4<T>::transform(const Vector3<T2>& vector)
{
	return Vector3<T2>(vector.x * m11 + vector.y * m21 + vector.z * m31 + m41,
					   vector.x * m12 + vector.y * m22 + vector.z * m32 + m42,
					   vector.x * m13 + vector.y * m23 + vector.z * m33 + m43);
}


template<typename T>
template<typename T2>
inline Vector4<T2> Matrix4<T>::transform(const Vector4<T2>& vector)
{
	return Vector4<T2>(vector.x * m11 + vector.y * m21 + vector.z * m31 + vector.w * m41,
					   vector.x * m12 + vector.y * m22 + vector.z * m32 + vector.w * m42,
					   vector.x * m13 + vector.y * m23 + vector.z * m33 + vector.w * m43,
					   vector.x * m14 + vector.y * m24 + vector.z * m34 + vector.w * m44);
}

template<typename T>
template<typename T2>
inline Vector3<T2> Matrix4<T>::transformDirection(const Vector3<T2>& vector)
{
	return Vector3<T2>(vector.x * m11 + vector.y * m21 + vector.z * m31,
					   vector.x * m12 + vector.y * m22 + vector.z * m32,
					   vector.x * m13 + vector.y * m23 + vector.z * m33);
}


}
#endif /* MATRIX4_H_ */
