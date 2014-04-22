#include "Framework/TileGrid.h"

namespace rf
{

TileGrid::TileGrid(int width, int height):
	m_width(width), m_height(height), m_tiles(width * height)
{
}

TileGrid::TileGrid(const TileGrid& other):
	m_width(other.m_width), m_height(other.m_height), m_tiles(other.m_tiles)
{
}

TileGrid::TileGrid(TileGrid&& other) noexcept:
	m_width(other.m_width), m_height(other.m_height), m_tiles(std::move(other.m_tiles))
{
}

TileGrid& TileGrid::operator =(const TileGrid& other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_tiles = other.m_tiles;
	return *this;
}

TileGrid& TileGrid::operator =(TileGrid&& other) noexcept
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_tiles = std::move(other.m_tiles);
	return *this;
}

void TileGrid::writeString(int startX, int startY, const char* string)
{
	int x = startX;
	const char* stringPtr = string;
	while(x < m_width)
	{
		char ch = *stringPtr;
		if(ch == '\0')
		{
			return;
		}
		m_tiles[x + m_width * startY].setTileIndex(ch);
		++stringPtr;
		++x;
	}
}

}



