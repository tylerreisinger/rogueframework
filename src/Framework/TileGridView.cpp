#include "Framework/TileGridView.h"

namespace rf
{

TileGridView::TileGridView(TileGrid* grid):
	m_position(0, 0), m_size(grid->width(), grid->height()), m_grid(grid)
{
}

TileGridView::TileGridView(int x, int y, int width, int height, TileGrid* grid):
	m_position(x, y), m_size(width, height), m_grid(grid)
{

}

TileGridView::TileGridView(const TileGridView& other):
	m_position(other.m_position), m_size(other.m_size), m_grid(other.m_grid)
{
}

TileGridView::TileGridView(TileGridView&& other) noexcept:
	m_position(other.m_position), m_size(other.m_size), m_grid(other.m_grid)
{
	other.m_grid = nullptr;
	other.m_position = Vector2i::zero();
	other.m_size = Vector2i::zero();
}

TileGridView& TileGridView::operator =(const TileGridView& other)
{
	m_position = other.m_position;
	m_size = other.m_size;
	m_grid = other.m_grid;
	return *this;
}

TileGridView& TileGridView::operator =(TileGridView&& other) noexcept
{
	if(&other != this)
	{
		m_position = other.m_position;
		m_size = other.m_size;
		m_grid = other.m_grid;
		other.m_grid = nullptr;
		other.m_position = Vector2i::zero();
		other.m_size = Vector2i::zero();
	}
	return *this;
}

}
