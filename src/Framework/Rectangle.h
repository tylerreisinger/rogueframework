/*
 * Rectangle.h
 *
 *  Created on: Oct 8, 2013
 *      Author: tyler
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Vector2.h"

#include <algorithm>

namespace rf
{

template <typename T>
class Rectangle
{
public:
	inline Rectangle() : m_left(0), m_bottom(0), m_right(0), m_top(0) {}

	/**
	 * @brief Construct a new Rectangle object.
	 * @param position The position of the bottom-left corner of the Rectangle.
	 * @param width The width of the Rectangle.
	 * @param height The height of the Rectangle.
	 */
	Rectangle(const Vector2<T>& position, T width, T height);

	/**
	 * @brief Construct a new Rectangle object.
	 * @param x The x coordinate of the bottom-left corner.
	 * @param y The y coordinate of the bottom-left corner.
	 * @param width The width of the Rectangle.
	 * @param height The height of the Rectangle.
	 */
	Rectangle(T x, T y, T width, T height);

	/**
	 * @brief Construct a new Rectangle object.
	 * @param topLeft The top-left point of the Rectangle.
	 * @param bottomRight The bottom-right point of the Rectangle.
	 */
	Rectangle(const Vector2<T>& topLeft, const Vector2<T>& bottomRight);

	~Rectangle() = default;

	Rectangle(const Rectangle&) = default;
	Rectangle(Rectangle&&) = default;
	Rectangle& operator =(const Rectangle&) = default;
	Rectangle& operator =(Rectangle&&) = default;

	///Compare two Rectangles
	bool operator ==(const Rectangle<T>& rectangle) const;
	///Compare two Rectangles
	bool operator !=(const Rectangle<T>& rectangle) const;

	///Return if the rectangle is null (has all verticies at (0, 0)).
	bool isNull() const {return m_left == 0 && m_right == 0 && m_top == 0 && m_bottom == 0;}

	///Return the left-most x-coordinate
	T left() const {return m_left;}
	///Return the right-most x-coordinate
	T right() const {return m_right;}
	///Return the top-most y-coordinate
	T top() const {return m_top;}
	///Return the bottom-most y-coordinate
	T bottom() const {return m_bottom;}
	///Return the height of the Rectangle.
	T height() const {return m_top - m_bottom;}
	///Return the width of the Rectangle.
	T width() const {return m_right - m_left;}

	///Return the top-left vertex of the Rectangle.
	Vector2<T> topLeft() const {return Vector2<T>(m_left, m_top);}
	///Return the top-right vertex of the Rectangle.
	Vector2<T> topRight() const {return Vector2<T>(m_right, m_top);}
	///Return the bottom-left vertex of the Rectangle.
	Vector2<T> bottomLeft() const {return Vector2<T>(m_left, m_bottom);}
	///Return the bottom-right vertex of the Rectangle.
	Vector2<T> bottomRight() const {return Vector2<T>(m_right, m_bottom);}
	///Return the center point of the Rectangle.
	Vector2<T> center() const;

	///Set the left-most x-coordinate of the Rectangle.
	void setLeft(T value) {m_left = value;}
	///Set the right-most x-coordinate of the Rectangle.
	void setRight(T value) {m_right = value;}
	///Set the top-most y-coordinate of the Rectangle.
	void setTop(T value) {m_top = value;}
	///Set the bottom-most y-coordinate of the Rectangle.
	void setBottom(T value) {m_bottom = value;}
	///Set the height of the Rectangle.
	///@details The rectangle will be expanded or contracted from the bottom,
	///the top-most coordinate will not change.
	void setHeight(T value) {m_top = m_bottom + value;}
	///Set the width of the Rectangle.
	///@details The rectangle will be expanded or contracted from the right,
	///the left-most coordinate will not change.
	void setWidth(T value) {m_right = m_left + value;}

	///Set the top-left vertex of the Rectangle.
	void setTopLeft(const Vector2<T>& value);
	///Set the top-right vertex of the Rectangle.
	void setTopRight(const Vector2<T>& value);
	///Set the bottom-left vertex of the Rectangle.
	void setBottomLeft(const Vector2<T>& value);
	///Set the bottom-right vertex of the Rectangle.
	void setBottomRight(const Vector2<T>& value);

	///Return the area of the Rectangle.
	T area() const {return width() * height();}

	///Return true if the Rectangle contains @a rectangle.
	bool contains(const Rectangle<T>& rectangle);
	///Return true if the Rectangle contains @a point.
	bool contains(const Vector2<T>& point);
	///Return true if the Rectangle contains @a (@a x, @a y).
	bool contains(T x, T y);

	///Offset the Rectangle by @a value.
	Rectangle& offset(const Vector2<T>& value);
	///Offset the Rectangle by (@a x, @a y)
	Rectangle& offset(T x, T y);

	///Inflate the Rectangle, making the right and bottom sides increase (or decrease) by the
	///given amount.
	Rectangle& inflate(T x, T y);
	///Expand the Rectangle on both sides by the given quantity.
	Rectangle& expand(T x, T y);

	///Move the top-left corner of the Rectangle to the given position.
	Rectangle& move(const Vector2<T>& bottomLeftPosition);
	///Move the top-left corner of the Rectangle to the given position.
	Rectangle& move(T x, T y);
	///Move the center of the Rectangle to the given position.
	Rectangle& moveCenter(const Vector2<T>& pos);
	///Move the center of the Rectangle to the given position.
	Rectangle& moveCenter(T x, T y);

	/**
	 * @brief Test if two Rectangles intersect each other.
	 * @param rect The Rectangle to test against.
	 */
	bool intersects(const Rectangle<T>& rect) const;

	/**
	 * @brief Calculate the intersection Rectangle between two Rectangles.
	 * @param rectangle The Rectangle to test against.
	 * @return The intersecting Rectangle. It will have all fields set to 0 if the rectangles do not intersect.
	 */
	Rectangle intersection(const Rectangle<T>& rectangle);

	/**
	 * @brief Return a new axis-aligned rectangle that bounds this Rectangle after it is rotated.
	 * @param origin The origin to rotate the Rectangle around.
	 * @param rotationAngle The angle, in radians, to rotate the Rectangle by.
	 * @return The Rectangle that bounds the rotated Rectangle.
	 */
	Rectangle axisAlignedRotatedBoundingRectangle(const Vector2<T>& origin, double rotationAngle);

	/**
	 * @brief Construct a Rectangle from its vertices.
	 * @param left Left-most x value.
	 * @param top Top-most y value.
	 * @param right Right-most x value.
	 * @param bottom Bottom-most y value.
	 * @return A new Rectangle object with the given vertices.
	 */
	static Rectangle fromVertices(double left, double top, double right, double bottom);

	/**
	 * @brief Compute the Rectangle bounding both @a rectangle1 and @a rectangle2.
	 */
	static Rectangle boundingRectangle(const Rectangle<T>& rectangle1, const Rectangle<T>& rectangle2);
	/**
	 * @brief Compute the Rectangle that bounds all rectangles in a list.
	 * @param rectangles A list of Rectangles.
	 * @return The bounding Rectangle.
	 */
	static Rectangle boundingRectangle(const std::vector<Rectangle<T>>& rectangles);

protected:

	T m_left;
	T m_bottom;
	T m_right;
	T m_top;
};

typedef Rectangle<int> Rectanglei;
typedef Rectangle<float> Rectanglef;
typedef Rectangle<double> Rectangled;

template<typename T>
inline Rectangle<T>::Rectangle(const Vector2<T>& position, T width, T height):
	m_left(position.x), m_bottom(position.y), m_right(position.x + width), m_top(position.y + height)
{
}

template<typename T>
inline Rectangle<T>::Rectangle(T x, T y, T width, T height):
	m_left(x), m_bottom(y), m_right(x + width), m_top(y + height)
{
}

template<typename T>
inline Rectangle<T>::Rectangle(const Vector2<T>& bottomLeft,
		const Vector2<T>& topRight):
	m_left(bottomLeft.x), m_bottom(bottomLeft.y), m_right(topRight.x), m_top(topRight.y)
{
}

template<typename T>
inline bool Rectangle<T>::operator ==(const Rectangle<T>& rectangle) const
{
	return (m_left == rectangle.m_left && m_right == rectangle.m_right
			&& m_top == rectangle.m_top && m_bottom == rectangle.m_bottom);
}

template<typename T>
inline bool Rectangle<T>::operator !=(const Rectangle<T>& rectangle) const
{
	return (m_left != rectangle.m_left || m_right != rectangle.m_right
			|| m_top != rectangle.m_top || m_bottom != rectangle.m_bottom);
}

template<typename T>
inline void Rectangle<T>::setTopLeft(const Vector2<T>& value)
{
	m_left = value.x;
	m_top = value.y;
}

template<typename T>
inline void Rectangle<T>::setTopRight(const Vector2<T>& value)
{
	m_right = value.x;
	m_top = value.y;
}

template<typename T>
inline void Rectangle<T>::setBottomLeft(const Vector2<T>& value)
{
	m_left = value.x;
	m_bottom = value.y;
}

template<typename T>
inline void Rectangle<T>::setBottomRight(const Vector2<T>& value)
{
	m_right = value.x;
	m_bottom = value.y;
}

template<typename T>
inline bool Rectangle<T>::contains(const Rectangle<T>& rectangle)
{
	return (rectangle.m_right <= m_right && rectangle.m_left >= m_left && rectangle.m_top <= m_top && rectangle.m_bottom >= m_bottom);
}

template<typename T>
inline bool Rectangle<T>::contains(const Vector2<T>& point)
{
	return (point.x >= m_left && point.y <= m_top && point.x <= m_right && point.y >= m_bottom);
}

template<typename T>
inline bool Rectangle<T>::contains(T x, T y)
{
	return (x >= m_left && y <= m_top && x <= m_right && y >= m_bottom);
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::offset(const Vector2<T>& value)
{
	m_left += value.x;
	m_right += value.x;
	m_top += value.y;
	m_bottom += value.y;
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::offset(T x, T y)
{
	m_left += x;
	m_right += x;
	m_top += y;
	m_bottom += y;
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::inflate(T x, T y)
{
	m_right += x;
	m_bottom += y;
	if(m_right < m_left)
	{
		m_right = m_left;
	}
	if(m_top < m_bottom)
	{
		m_top = m_bottom;
	}
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::expand(T x, T y)
{
	m_left -= x;
	m_right += x;
	m_top += y;
	m_bottom -= y;
	if(m_right < m_left)
	{
		m_right = m_left;
	}
	if(m_top < m_bottom)
	{
		m_top = m_bottom;
	}
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::move(const Vector2<T>& bottomLeftPosition)
{
	T oldWidth = width();
	T oldHeight = height();
	m_left = bottomLeftPosition.x;
	m_bottom = bottomLeftPosition.y;
	m_right = m_left + oldWidth;
	m_top = m_bottom + oldHeight;
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::move(T x, T y)
{
	T oldWidth = width();
	T oldHeight = height();
	m_left = x;
	m_bottom = y;
	m_right = m_left + oldWidth;
	m_top = m_bottom + oldHeight;
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::moveCenter(const Vector2<T>& pos)
{
	T width = width();
	T height = height();
	m_right = pos.x + width / T(2.0);
	m_bottom = pos.y - height / T(2.0);
	m_left = pos.x - width / T(2.0);
	m_top = pos.y + height / T(2.0);
	return *this;
}

template<typename T>
inline Rectangle<T>& Rectangle<T>::moveCenter(T x, T y)
{
	T width = width();
	T height = height();
	m_right = x + width / T(2.0);
	m_top = y + height / T(2.0);
	m_left = x - width / T(2.0);
	m_bottom = y - height / T(2.0);
	return *this;
}

template<typename T>
inline bool Rectangle<T>::intersects(const Rectangle<T>& rect) const
{
	return (m_right >= rect.m_left && m_left <= rect.m_right && m_bottom <= rect.m_top && m_top >= rect.m_bottom);
}

template<typename T>
inline Rectangle<T> Rectangle<T>::intersection(const Rectangle<T>& rectangle)
{
	if(!intersects(rectangle))
	{
		return Rectangle<T>();
	}
	int left = std::max(m_left, rectangle.m_left);
	int right = std::min(m_right, rectangle.m_right);
	int top = std::max(m_top, rectangle.m_top);
	int bottom = std::min(m_bottom, rectangle.m_bottom);
	return Rectangle<T>::fromVertices(left, bottom, right, top);
}

template<typename T>
inline Rectangle<T> Rectangle<T>::axisAlignedRotatedBoundingRectangle(const Vector2<T>& origin, double rotationAngle)
{
	T relativeLeft = -origin.x;
	T relativeTop = -origin.y + height();
	T relativeRight = -origin.x + width();
	T relativeBottom = -origin.y;

	double cosAngle = std::cos(rotationAngle);
	double sinAngle = std::sin(rotationAngle);

	T newXCoords[] = {relativeLeft*cosAngle + relativeTop*sinAngle, relativeRight*cosAngle + relativeTop*sinAngle,
			relativeLeft*cosAngle + relativeBottom*sinAngle, relativeRight*cosAngle + relativeBottom*sinAngle};

	T newYCoords[] = {-relativeLeft*sinAngle + relativeTop*cosAngle, -relativeRight*sinAngle + relativeTop*cosAngle,
			-relativeLeft*sinAngle + relativeBottom*cosAngle, -relativeRight*sinAngle + relativeBottom*cosAngle};

	T newTop = *std::max_element(newYCoords, newYCoords + 4) + m_bottom + origin.y;
	T newBottom = *std::min_element(newYCoords, newYCoords + 4) + m_bottom + origin.y;
	T newLeft = *std::min_element(newXCoords, newXCoords + 4) + m_left + origin.x;
	T newRight = *std::max_element(newXCoords, newXCoords + 4) +  m_left + origin.x;

	return Rectangle<T>::fromVertices(newLeft, newBottom, newRight, newTop);
}

template<typename T>
inline Rectangle<T> Rectangle<T>::fromVertices(double left, double bottom,
		double right, double top)
{
	return Rectangle<T>(left, bottom, right - left, top - bottom);
}

template<typename T>
inline Vector2<T> Rectangle<T>::center() const
{
	return Vector2<T>(m_left + width() / 2., m_bottom + height() / 2.);
}

template<typename T>
inline Rectangle<T> Rectangle<T>::boundingRectangle(const Rectangle<T>& rectangle1, const Rectangle<T>& rectangle2)
{
	return Rectangle<T>::fromVertices(std::min(rectangle1.left(), rectangle2.left()),
			std::min(rectangle1.bottom(), rectangle2.bottom()),
			std::max(rectangle1.right(), rectangle2.right()),
			std::max(rectangle1.top(), rectangle2.top()));
}

template<typename T>
inline Rectangle<T> Rectangle<T>::boundingRectangle(const std::vector<Rectangle<T>>& rectangles)
{
	if(rectangles.size() == 0)
	{
		return Rectangle<T>();
	}
	Rectangle<T> outRect = rectangles[0];
	for(int i = 1; i < rectangles.size(); ++i)
	{
		outRect = boundingRectangle(outRect, rectangles[i]);
	}
	return outRect;
}

}

#endif /* RECTANGLE_H_ */
