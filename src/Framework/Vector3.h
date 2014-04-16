#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

#include <cassert>

namespace rf
{

template <typename T>
class Vector3
{
public:
	constexpr Vector3() {};
	constexpr Vector3(T xVal, T yVal, T zVal);
	Vector3(const Vector3<T>& value) = default;
	template<typename T2>
	Vector3(const Vector3<T2>& value);
	Vector3(Vector3<T>&& value) = default;
	~Vector3() = default;

	Vector3& operator =(const Vector3<T>& value) = default;
	Vector3& operator =(Vector3<T>&& value) = default;

	bool operator ==(const Vector3& vector) const {return (vector.x == x && vector.y == y && vector.z == z);}
	bool operator !=(const Vector3& vector) const {return !(*this == vector);}

	Vector3& operator +=(const Vector3& vector);
	Vector3& operator -=(const Vector3& vector);
	Vector3& operator *=(T value);
	Vector3& operator /=(T value);

	Vector3 operator +(const Vector3& vector) const {return Vector3(x + vector.x, y + vector.y, z + vector.z);}
	Vector3 operator -(const Vector3& vector) const {return Vector3(x - vector.x, y - vector.y, z - vector.z);}
	Vector3 operator *(T value) const {return Vector3(x * value, y * value, z * value);}
	Vector3 operator /(T value) const {return Vector3(x / value, y / value, z / value);}
	Vector3 operator -() const {return Vector3(-x, -y, -z);}

	friend Vector3 operator *(T value, const Vector3& vector) {return vector * value;}

	///Return a new Vector3<T> with x and y negated.
	Vector3 negative() const {return -*this;}

	///Negate the x, y and z components of the vector.
	void negate() {x = -x; y = -y; z = -z;}

	///Return the magnitude of the vector: @f$ \sqrt{x^2 + y^2 + z^2} @f$
	T magnitude() const;
	///Return the magnitude of the vector, squared: @f$ x^2 + y^2 + z^2 @f$
	T magnitudeSquared() const;
	///Return a new vector with the same angle as the current vector and a magnitude of 1.
	Vector3 normalize() const;

	///Compute the dot product between two vectors.
	static T dotProduct(const Vector3<T>& vec1, const Vector3<T>& vec2);
	///Compute the cross product between two vectors.
	static Vector3<T> crossProduct(const Vector3<T>& vec1, const Vector3<T>& vec2);

	static Vector3<T> fromMagnitudeAndAngles(T magnitude, double yaw, double pitch);

	static constexpr Vector3<T> zero() {return Vector3<T>(0, 0, 0, 0);}
	static constexpr Vector3<T> unitX() {return Vector3<T>(0, 1, 0, 0);}
	static constexpr Vector3<T> unitY() {return Vector3<T>(0, 0, 1, 0);}
	static constexpr Vector3<T> unitZ() {return Vector3<T>(0, 0, 0, 1);}

	T x = T(0);
	T y = T(0);
	T z = T(0);
};

typedef Vector3<double> Vector3d;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector3<unsigned int> Vector3ui;

template<typename T>
inline Vector3<T>::Vector3(T xVal, T yVal, T zVal):
	x(xVal), y(yVal), z(zVal)
{
}

template<typename T>
template<typename T2>
inline Vector3<T>::Vector3(const Vector3<T2>& value):
	x(T(value.x)), y(T(value.y)), z(T(value.z))
{
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator +=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator -=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator *=(T value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator /=(T value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

template<typename T>
inline T Vector3<T>::magnitude() const
{
	using std::sqrt;
	return sqrt(x*x + y*y + z*z);
}

template<typename T>
inline T Vector3<T>::magnitudeSquared() const
{
	return x*x + y*y + z*z;
}

template<typename T>
inline Vector3<T> Vector3<T>::normalize() const
{
	assert(x != 0 || y != 0 || z != 0);
	return *this / magnitude();
}

template<typename T>
inline T Vector3<T>::dotProduct(const Vector3<T>& vec1, const Vector3<T>& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

template<typename T>
inline Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& vec1,
		const Vector3<T>& vec2)
{
	return Vector3<T>(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
}

template<typename T>
Vector3<T> Vector3<T>::fromMagnitudeAndAngles(T magnitude, double yaw,
		double pitch)
{
	using std::cos;
	using std::sin;
	return Vector3(cos(yaw) * cos(pitch), sin(yaw) * cos(pitch), sin(pitch));
}

}

#endif
