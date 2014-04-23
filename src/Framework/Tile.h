#ifndef TILE_H_
#define TILE_H_

#include "Framework/Color.h"

namespace rf
{

class Tile
{
public:
	Tile() {};
	Tile(const Color& foregroundColor, const Color& backgroundColor, unsigned int tileIndex);
	~Tile() = default;

	Tile(const Tile& other);
	Tile(Tile&& other) noexcept;
	Tile& operator =(const Tile& other);
	Tile& operator =(Tile&& other) noexcept;

	const Color& foregroundColor() const {return m_foregroundColor;}
	const Color& backgroundColor() const {return m_backgroundColor;}
	unsigned int tileIndex() const {return m_tileIndex;}

	Tile& setForegroundColor(const Color& color) {m_foregroundColor = color; return *this;}
	Tile& setBackgroundColor(const Color& color) {m_backgroundColor = color; return *this;}
	Tile& setTileIndex(unsigned int index) {m_tileIndex = index; return *this;}

protected:
	Color m_foregroundColor = Color::white();
	Color m_backgroundColor = Color::black();
	unsigned int m_tileIndex = ' ';
};

inline Tile::Tile(const Tile& other):
	m_foregroundColor(other.m_foregroundColor), m_backgroundColor(other.m_backgroundColor),
	m_tileIndex(other.m_tileIndex)
{
}

inline Tile::Tile(Tile&& other) noexcept:
	m_foregroundColor(other.m_foregroundColor), m_backgroundColor(other.m_backgroundColor),
	m_tileIndex(other.m_tileIndex)
{
}

inline Tile& Tile::operator =(const Tile& other)
{
	m_foregroundColor = other.m_foregroundColor;
	m_backgroundColor = other.m_backgroundColor;
	m_tileIndex = other.m_tileIndex;
	return *this;
}

inline Tile& Tile::operator =(Tile&& other) noexcept
{
	m_foregroundColor = other.m_foregroundColor;
	m_backgroundColor = other.m_backgroundColor;
	m_tileIndex = other.m_tileIndex;
	return *this;
}


}

#endif
