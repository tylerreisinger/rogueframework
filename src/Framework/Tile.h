#ifndef TILE_H_
#define TILE_H_

#include "Framework/Color.h"

namespace rf
{

class Tile
{
public:
	Tile() {};
	Tile(const Colorf& foregroundColor, const Colorf& backgroundColor, unsigned int tileIndex);
	~Tile() = default;

	Tile(const Tile& other);
	Tile(Tile&& other) noexcept;
	Tile& operator =(const Tile& other);
	Tile& operator =(Tile&& other) noexcept;

	const Colorf& foregroundColor() const {return m_foregroundColor;}
	const Colorf& backgroundColor() const {return m_backgroundColor;}
	unsigned int tileIndex() const {return m_tileIndex;}

	Tile& setForegroundColor(const Colorf& color) {m_foregroundColor = color; return *this;}
	Tile& setBackgroundColor(const Colorf& color) {m_backgroundColor = color; return *this;}
	Tile& setTileIndex(unsigned int index) {m_tileIndex = index; return *this;}

protected:
	Colorf m_foregroundColor = Colorf::white();
	Colorf m_backgroundColor = Colorf::black();
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
