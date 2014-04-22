#include "Framework/TileGrid.h"

namespace rf
{

TileGrid::TileGrid(int width, int height):
	m_defaultState(Tile(Color::white(), Color::black(), 0)),
	m_clearState(Tile(Color::white(), Color::black(), ' ')),
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

void TileGrid::writeString(int startX, int startY, const char* string, TextWrappingMode wrapMode)
{
	int x = startX;
	int y = startY;
	const char* stringPtr = string;
	while(true)
	{
		char ch = *stringPtr;
		if(ch == '\0')
		{
			break;
		}
		m_tiles[x + m_width * y] = m_defaultState;
		m_tiles[x + m_width * y].setTileIndex(ch);
		++stringPtr;
		++x;
		if(x >= m_width)
		{
			if(wrapMode == TextWrappingMode::Wrap)
			{
				y++;
				x = 0;
			}
			else
			{
				break;
			}
		}
	}
}



}



