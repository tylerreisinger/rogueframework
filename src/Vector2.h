#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cmath>

template <typename T>
class Vector2
{
public:
	constexpr Vector2() {};
	constexpr Vector2(T xVal, T yVal);
	template<typename T2>
	Vector2(const Vector2<T2>& value);
	Vector2(const Vector2<T>& value) = default;
	Vector2(Vector2<T>&& value) = default;
	~Vector2() = default;

	Vector2& operator =(const Vector2<T>& value) = default;
	Vector2& operator =(Vector2<T>&& value) = default;

	bool operator ==(const Vector2& vector) const {return (vector.x == x && vector.y == y);}
	bool operator !=(const Vector2& vector) const {return !(*this == vector);}

	Vector2& operator +=(const Vector2& vector);
	Vector2& operator -=(const Vector2& vector);
	Vector2& operator *=(T value);
	Vector2& operator /=(T value);

	Vector2 operator +(const Vector2& vector) const {return Vector2(x + vector.x, y + vector.y);}
	Vector2 operator -(const Vector2& vector) const {return Vector2(x - vector.x, y - vector.y);}
	Vector2 operator *(T value) const {return Vector2(x * value, y * value);}
	Vector2 operator /(T value) const {return Vector2(x / value, y / value);}
	Vector2 operator -() const {return Vector2(-x, -y);}

	friend Vector2 operator *(T value, const Vector2& vector) {return vector * value;}

	///Return a new Vector2<T> with x and y negated.
	Vector2 negative() const {return -*this;}

	///Negate the x and y components of the vector
	void negate() {x = -x; y = -y;}


	///Return the magnitude of the vector: @f$ \sqrt{x^2 + y^2} @f$
	T magnitude() const;
	///Return the magnitude of the vector, squared: @f$ x^2 + y^2 @f$
	T magnitudeSquared() const;
	///Return the angle made between the vector and the x axis
	T angle() const;
	///Return a new vector with the same angle as the current vector and a magnitude of 1.
	Vector2 normalize() const;

	///Compute the dot product between two vectors.
	static T dotProduct(const Vector2<T>& vec1, const Vector2<T>& vec2);

	static Vector2<T> fromMagnitudeAndAngle(T magnitude, T angle);

	static constexpr Vector2<T> zero() {return Vector2<T>(0, 0);}
	static constexpr Vector2<T> unitX() {return Vector2<T>(1, 0);}
	static constexpr Vector2<T> unitY() {return Vector2<T>(0, 1);}

	T x = T(0);
	T y = T(0);
};

typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2ui;

template<typename T>
inline constexpr Vector2<T>::Vector2(T xVal, T yVal):
	x(xVal), y(yVal)
{

}

template<typename T>
template<typename T2>
inline Vector2<T>::Vector2(const Vector2<T2>& value):
	x(T(value.x)), y(T(value.y))
{
}


template<typename T>
inline Vector2<T>& Vector2<T>::operator +=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator -=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator *=(T value)
{
	x *= value;
	y *= value;
	return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator /=(T value)
{
	x /= value;
	y /= value;
	return *this;
}

template<typename T>
inline T Vector2<T>::magnitude() const
{
	using std::sqrt;
	return sqrt(x * x + y * y);
}

template<typename T>
inline T Vector2<T>::magnitudeSquared() const
{
	return x * x + y * y;
}

template<typename T>
inline T Vector2<T>::angle() const
{
	using std::atan2;
	return atan2(-y, x);
}

template<typename T>
inline Vector2<T> Vector2<T>::normalize() const
{
	assert(x != 0 || y != 0);
	return *this / magnitude();
}

template<typename T>
inline T Vector2<T>::dotProduct(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return vec1.x * vec2.x + vec1.y + vec2.y;
}

template<typename T>
inline Vector2<T> Vector2<T>::fromMagnitudeAndAngle(T magnitude, T angle)
{
	using std::sin;
	using std::cos;

	return Vector2<T>(magnitude * cos(angle), magnitude * sin(angle));
}
#endif /* VECTOR2_H_ */
