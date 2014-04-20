#include "Framework/TileGrid.h"

namespace rf
{

TileGrid::TileGrid(int width, int height, const Vector2i& location):
	m_width(width), m_height(height), m_location(location), m_tiles(width * height)
{
}

TileGrid::TileGrid(const TileGrid& other):
	m_width(other.m_width), m_height(other.m_height), m_location(other.m_location),
	m_tiles(other.m_tiles)
{
}

TileGrid::TileGrid(TileGrid&& other) noexcept:
	m_width(other.m_width), m_height(other.m_height), m_location(other.m_location),
	m_tiles(std::move(other.m_tiles))
{
}

TileGrid& TileGrid::operator =(const TileGrid& other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_location = other.m_location;
	m_tiles = other.m_tiles;
	return *this;
}

TileGrid& TileGrid::operator =(TileGrid&& other) noexcept
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_location = other.m_location;
	m_tiles = std::move(other.m_tiles);
	return *this;
}

}