#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "Vector3.h"

namespace rf
{

template<typename T>
class Vector4
{
public:
	constexpr Vector4() {};
	constexpr Vector4(T xVal, T yVal, T zVal, T wVal);
	Vector4(const Vector3<T>& xyz, T wVal);
	template<typename T2>
	Vector4(const Vector4<T2>& value);
	~Vector4() = default;

	Vector4(const Vector4&) = default;
	Vector4(Vector4&&) = default;
	Vector4& operator =(const Vector4&) = default;
	Vector4& operator =(Vector4&&) = default;

	bool operator ==(const Vector4& vector) const {return (vector.x == x && vector.y == y && vector.z == z && vector.w == w);}
	bool operator !=(const Vector4& vector) const {return !(*this == vector);}

	Vector4& operator +=(const Vector4& vector);
	Vector4& operator -=(const Vector4& vector);
	Vector4& operator *=(T value);
	Vector4& operator /=(T value);

	Vector4 operator +(const Vector4& vector) const {return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);}
	Vector4 operator -(const Vector4& vector) const {return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);}
	Vector4 operator *(T value) const {return Vector4(x * value, y * value, z * value, w * value);}
	Vector4 operator /(T value) const {return Vector4(x / value, y / value, z / value, w / value);}
	Vector4 operator -() const {return Vector4(-x, -y, -z, -w);}

	friend Vector4 operator *(T value, const Vector4& vector) {return vector * value;}

	///Return a new Vector4<T> with each component negated.
	Vector4 negate() const {return -*this;}

	///Return the magnitude of the vector: @f$ \sqrt{x^2 + y^2 + z^2 + w^2} @f$
	T magnitude() const;
	///Return the magnitude of the vector, squared: @f$ x^2 + y^2 + z^2 + w^2 @f$
	T magnitude2() const;
	///Return a new vector with the same angle as the current vector and a magnitude of 1.
	Vector4 normalize() const;

	Vector3<T> positionalPart() const;
	Vector3<T> normalizedPositionalPart() const;

	///Compute the dot product between two vectors.
	static T dotProduct(const Vector4<T>& vec1, const Vector4<T>& vec2);

	static constexpr Vector4 zero() {return Vector4<T>(0, 0, 0, 0);}
	static constexpr Vector4 unitX() {return Vector4<T>(1, 0, 0, 0);}
	static constexpr Vector4 unitY() {return Vector4<T>(0, 1, 0, 0);}
	static constexpr Vector4 unitZ() {return Vector4<T>(0, 0, 1, 0);}
	static constexpr Vector4 unitW() {return Vector4<T>(0, 0, 0, 1);}

	T x = T(0);
	T y = T(0);
	T z = T(0);
	T w = T(0);
};

typedef Vector4<double> Vector4d;
typedef Vector4<float> Vector4f;

template<typename T>
inline constexpr Vector4<T>::Vector4(T xVal, T yVal, T zVal, T wVal):
	x(xVal), y(yVal), z(zVal), w(wVal)
{
}

template<typename T>
template<typename T2>
inline Vector4<T>::Vector4(const Vector4<T2>& value):
	x(value.x), y(value.y), z(value.z), w(value.w)
{
}

template<typename T>
inline Vector4<T>::Vector4(const Vector3<T>& xyz, T wVal):
	x(xyz.x), y(xyz.y), z(xyz.z), w(wVal)
{
}


template<typename T>
inline Vector4<T>& Vector4<T>::operator +=(const Vector4& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator -=(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator *=(T value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator /=(T value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

template<typename T>
inline T Vector4<T>::magnitude() const
{
	using std::sqrt;
	return sqrt(x*x + y*y + z*z + w*w);
}

template<typename T>
inline T Vector4<T>::magnitude2() const
{
	return x*x + y*y + z*z + w*w;
}

template<typename T>
inline Vector4<T> Vector4<T>::normalize() const
{
	return *this / magnitude();
}

template<typename T>
inline T Vector4<T>::dotProduct(const Vector4<T>& vec1, const Vector4<T>& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
}

template<typename T>
inline Vector3<T> Vector4<T>::positionalPart() const
{
	return Vector3<T>(x, y, z);
}

template<typename T>
inline Vector3<T> Vector4<T>::normalizedPositionalPart() const
{
	return Vector3<T>(x / w, y / w, z / w);
}

}

#endif /* VECTOR4_H_ */
