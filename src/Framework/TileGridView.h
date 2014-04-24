#ifndef TILEGRIDVIEW_H_
#define TILEGRIDVIEW_H_

#include <cassert>

#include "Framework/TileGrid.h"

namespace rf
{

class TileGridView
{
public:
	TileGridView(TileGrid* grid);
	TileGridView(int x, int y, int width, int height, TileGrid* grid);
	~TileGridView() = default;

	TileGridView(const TileGridView& other);
	TileGridView(TileGridView&& other) noexcept;
	TileGridView& operator =(const TileGridView& other);
	TileGridView& operator =(TileGridView&& other) noexcept;

	Tile& operator [](size_t index) {return getTile(index);}
	const Tile& operator [](size_t index) const {return getTile(index);}

	const Vector2i& position() const {return m_position;}
	int width() const {return m_size.x;}
	int height() const {return m_size.y;}

	Tile& getTile(int x, int y);
	const Tile& getTile(int x, int y) const {return const_cast<TileGridView*>(this)->getTile(x, y);}
	Tile& getTile(size_t index);
	const Tile& getTile(size_t index) const {return const_cast<TileGridView*>(this)->getTile(index);}

	void setTile(int x, int y, const Tile& value) {m_grid->setTile(x + m_position.x, y + m_position.y, value);}
	void setTile(size_t index, const Tile& value);

	TileGrid* getBaseGrid() const {return m_grid;}

	void fill(const Tile& newTile);
	void fillForegroundColor(const Color& color);
	void fillBackgroundColor(const Color& color);
	void fillTileIndex(unsigned int newIndex);

	void setLine(int x1, int y1, int x2, int y2, const Tile& newTile);
	void setLine(const Vector2i& p1, const Vector2i& p2, const Tile& newTile)
		{ setLine(p1.x, p1.y, p2.x, p2.y, newTile);}
	void setLineBackgroundColor(int x1, int y1, int x2, int y2, const Color& color);
	void setLineBackgroundColor(const Vector2i& p1, const Vector2i& p2, const Color& color)
		{ setLineBackgroundColor(p1.x, p1.y, p2.x, p2.y, color);}
	void setLineForegroundColor(int x1, int y1, int x2, int y2, const Color& color);
	void setLineForegroundColor(const Vector2i& p1, const Vector2i& p2, const Color& color)
		{ setLineForegroundColor(p1.x, p1.y, p2.x, p2.y, color);}
	void setLineTileIndex(int x1, int y1, int x2, int y2, unsigned int tileIndex);
	void setLineTileIndex(const Vector2i& p1, const Vector2i& p2, unsigned int tileIndex)
		{ setLineTileIndex(p1.x, p1.y, p2.x, p2.y, tileIndex);}

	void setBox(int x, int y, int width, int height, const Tile& newTile);
	void setBox(const Rectanglei& box, const Tile& newTile)
		{ setBox(box.left(), box.bottom(), box.width(), box.height(), newTile);}
	void setBoxBackgroundColor(int x, int y, int width, int height, const Color& color);
	void setBoxBackgroundColor(const Rectanglei& box, const Color& color)
		{ setBoxBackgroundColor(box.left(), box.bottom(), box.width(), box.height(), color);}
	void setBoxForegroundColor(int x, int y, int width, int height, const Color& color);
	void setBoxForegroundColor(const Rectanglei& box, const Color& color)
		{ setBoxForegroundColor(box.left(), box.bottom(), box.width(), box.height(), color);}
	void setBoxTileIndex(int x, int y, int width, int height, unsigned int index);
	void setBoxTileIndex(const Rectanglei& box, unsigned int index)
		{ setBoxTileIndex(box.left(), box.bottom(), box.width(), box.height(), index);}

	template<typename FnType>
	void applyToAll(const FnType& fn);

	template<typename FnType>
	void applyToLine(int x1, int y1, int x2, int y2, const FnType& fn);
	template<typename FnType>
	void applyToLine(const Vector2i& p1, const Vector2i& p2, const FnType& fn)
	{
		applyToLine(p1.x, p1.y, p2.x, p2.y, fn);
	}

	template<typename FnType>
	void applyToBox(int x, int y, int width, int height, const FnType& fn);
	template<typename FnType>
	void applyToBox(const Rectanglei& box, const FnType& fn)
	{
		applyToBox(box.left(), box.bottom(), box.width(), box.height(), fn);
	}

protected:
	TileGrid* m_grid;

	Vector2i m_position;
	Vector2i m_size;
};

inline Tile& TileGridView::getTile(int x, int y)
{
	assert(x >= 0 && x < m_size.x);
	assert(y >= 0 && y < m_size.y);
	return m_grid->getTile(x + m_position.x, y + m_position.y);
}

inline Tile& TileGridView::getTile(size_t index)
{
	assert(index >= 0 && index < m_size.x * m_size.y);
	int x = index % m_size.x;
	int y = index / m_size.x;
	return m_grid->getTile(x + m_position.x, y + m_position.y);
}

inline void TileGridView::setTile(size_t index, const Tile& value)
{
	assert(index >= 0 && index < m_size.x * m_size.y);
	int x = index % m_size.x;
	int y = index / m_size.x;
	m_grid->setTile(x + m_position.x, y + m_position.y, value);
}

inline void TileGridView::fill(const Tile& newTile)
{
	applyToAll(
		[newTile](Tile& tile)
		{
			tile = newTile;
		});
}

inline void TileGridView::fillForegroundColor(const Color& color)
{
	applyToAll(
		[color](Tile& tile)
		{
			tile.setForegroundColor(color);
		});
}

inline void TileGridView::fillBackgroundColor(const Color& color)
{
	applyToAll(
		[color](Tile& tile)
		{
			tile.setBackgroundColor(color);
		});
}

inline void TileGridView::fillTileIndex(unsigned int newIndex)
{
	applyToAll(
		[newIndex](Tile& tile)
		{
			tile.setTileIndex(newIndex);
		}
	);
}

inline void TileGridView::setLine(int x1, int y1, int x2, int y2, const Tile& newTile)
{
	applyToLine(x1, y1, x2, y2,
		[newTile](Tile& tile)
		{
			tile = newTile;
		});
}

inline void TileGridView::setLineBackgroundColor(int x1, int y1, int x2, int y2,
		const Color& color)
{
	applyToLine(x1, y1, x2, y2,
		[color](Tile& tile)
		{
			tile.setBackgroundColor(color);
		});
}

inline void TileGridView::setLineForegroundColor(int x1, int y1, int x2, int y2,
		const Color& color)
{
	applyToLine(x1, y1, x2, y2,
		[color](Tile& tile)
		{
			tile.setForegroundColor(color);
		});
}

inline void TileGridView::setLineTileIndex(int x1, int y1, int x2, int y2,
		unsigned int tileIndex)
{
	applyToLine(x1, y1, x2, y2,
		[tileIndex](Tile& tile)
		{
			tile.setTileIndex(tileIndex);
		});
}

inline void TileGridView::setBox(int x, int y, int width, int height, const Tile& newTile)
{
	applyToBox(x, y, width, height,
		[newTile](Tile& tile)
		{
			tile = newTile;
		});
}

inline void TileGridView::setBoxBackgroundColor(int x, int y, int width, int height,
		const Color& color)
{
	applyToBox(x, y, width, height,
		[color](Tile& tile)
		{
			tile.setBackgroundColor(color);
		});
}

inline void TileGridView::setBoxForegroundColor(int x, int y, int width, int height,
		const Color& color)
{
	applyToBox(x, y, width, height,
		[color](Tile& tile)
		{
			tile.setForegroundColor(color);
		});
}

inline void TileGridView::setBoxTileIndex(int x, int y, int width, int height,
		unsigned int index)
{
	applyToBox(x, y, width, height,
		[index](Tile& tile)
		{
			tile.setTileIndex(index);
		});
}

template<typename FnType>
inline void TileGridView::applyToAll(const FnType& fn)
{
	for(int y = 0; y < m_size.y; ++y)
	{
		for(int x = 0; x < m_size.x; ++x)
		{
			fn(getTile(x, y));
		}
	}
}

template<typename FnType>
void TileGridView::applyToLine(int x1, int y1, int x2, int y2, const FnType& fn)
{
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int sx = (x1 < x2 ? 1 : -1);
	int sy = (y1 < y2 ? 1 : -1);

	int error = dx - dy;

	while(x1 > 0 && x1 < m_size.x && y1 > 0 && y1 < m_size.y)
	{
		fn(getTile(x1, y1));
		if(x1 == x2 && y1 == y2)
		{
			break;
		}
		int e2 = 2 * error;
		if(e2 > -dy)
		{
			error -= dy;
			x1 += sx;
		}
		if(e2 < dx)
		{
			error += dx;
			y1 += sy;
		}
	}
}

template<typename FnType>
inline void TileGridView::applyToBox(int x, int y, int width, int height,
		const FnType& fn)
{
	assert(x >= 0);
	assert(y >= 0);

	for(int yPos = 0; yPos < height; ++yPos)
	{
		if(y + yPos >= m_size.y)
		{
			break;
		}
		for(int xPos = 0; xPos < width; ++xPos)
		{
			if(x + xPos >= m_size.x)
			{
				break;
			}
			fn(getTile(x + xPos, y + yPos));
		}
	}
}

}

#endif
