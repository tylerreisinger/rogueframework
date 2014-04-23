#ifndef TILEGRID_H_
#define TILEGRID_H_

#include "Tile.h"

#include <vector>
#include <cstring>
#include <string>
#include <cassert>

#include "Framework/Vector2.h"
#include "Framework/Rectangle.h"

namespace rf
{

namespace gl
{
class VertexBuffer;
class IndexBuffer;
class VertexArrayObject;
}

class TileGrid
{
public:

	enum TextWrappingMode
	{
		NoWrap,
		Wrap
	};

	TileGrid(int width, int height);
	virtual ~TileGrid() = default;

	TileGrid(const TileGrid& other);
	TileGrid(TileGrid&& other) noexcept;
	TileGrid& operator =(const TileGrid& other);
	TileGrid& operator =(TileGrid&& other) noexcept;

	Tile& operator [](size_t index) {return getTile(index);}
	const Tile& operator [](size_t index) const {return getTile(index);}

	int width() const {return m_width;}
	int height() const {return m_height;}

	Tile& getTile(size_t index) {return m_tiles[index];}
	Tile& getTile(int x, int y) {return m_tiles[x + m_width * y];}
	const Tile& getTile(size_t index) const {return m_tiles[index];}
	const Tile& getTile(int x, int y) const {return m_tiles[x + m_width * y];}

	void setTile(size_t index, const Tile& tile) {m_tiles[index] = tile;}
	void setTile(int x, int y, const Tile& tile) {m_tiles[x + m_width * y] = tile;}

	void writeString(int startX, int startY, const char* string, TextWrappingMode wrapMode = TextWrappingMode::NoWrap);
	void writeString(int startX, int startY, const std::string& string, TextWrappingMode wrapMode = TextWrappingMode::NoWrap)
	{
		writeString(startX, startY, string.c_str(), wrapMode);
	}

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

	Tile m_defaultState;
	Tile m_clearState;

	int m_width;
	int m_height;

	std::vector<Tile> m_tiles;
};

inline void TileGrid::fill(const Tile& newTile)
{
	applyToAll(
		[newTile](Tile& tile)
		{
			tile = newTile;
		});
}

inline void TileGrid::fillForegroundColor(const Color& color)
{
	applyToAll(
		[color](Tile& tile)
		{
			tile.setForegroundColor(color);
		});
}

inline void TileGrid::fillBackgroundColor(const Color& color)
{
	applyToAll(
		[color](Tile& tile)
		{
			tile.setBackgroundColor(color);
		});
}

inline void TileGrid::fillTileIndex(unsigned int newIndex)
{
	applyToAll(
		[newIndex](Tile& tile)
		{
			tile.setTileIndex(newIndex);
		}
	);
}

inline void TileGrid::setLine(int x1, int y1, int x2, int y2, const Tile& newTile)
{
	applyToLine(x1, y1, x2, y2,
		[newTile](Tile& tile)
		{
			tile = newTile;
		});
}

inline void TileGrid::setLineBackgroundColor(int x1, int y1, int x2, int y2,
		const Color& color)
{
	applyToLine(x1, y1, x2, y2,
		[color](Tile& tile)
		{
			tile.setBackgroundColor(color);
		});
}

inline void TileGrid::setLineForegroundColor(int x1, int y1, int x2, int y2,
		const Color& color)
{
	applyToLine(x1, y1, x2, y2,
		[color](Tile& tile)
		{
			tile.setForegroundColor(color);
		});
}

inline void TileGrid::setLineTileIndex(int x1, int y1, int x2, int y2,
		unsigned int tileIndex)
{
	applyToLine(x1, y1, x2, y2,
		[tileIndex](Tile& tile)
		{
			tile.setTileIndex(tileIndex);
		});
}

inline void TileGrid::setBox(int x, int y, int width, int height, const Tile& newTile)
{
	applyToBox(x, y, width, height,
		[newTile](Tile& tile)
		{
			tile = newTile;
		});
}

inline void TileGrid::setBoxBackgroundColor(int x, int y, int width, int height,
		const Color& color)
{
	applyToBox(x, y, width, height,
		[color](Tile& tile)
		{
			tile.setBackgroundColor(color);
		});
}

inline void TileGrid::setBoxForegroundColor(int x, int y, int width, int height,
		const Color& color)
{
	applyToBox(x, y, width, height,
		[color](Tile& tile)
		{
			tile.setForegroundColor(color);
		});
}

inline void TileGrid::setBoxTileIndex(int x, int y, int width, int height,
		unsigned int index)
{
	applyToBox(x, y, width, height,
		[index](Tile& tile)
		{
			tile.setTileIndex(index);
		});
}

template<typename FnType>
inline void TileGrid::applyToAll(const FnType& fn)
{
	for(int y = 0; y < m_height; ++y)
	{
		for(int x = 0; x < m_width; ++x)
		{
			fn(m_tiles[x + y * m_width]);
		}
	}
}

template<typename FnType>
void TileGrid::applyToLine(int x1, int y1, int x2, int y2, const FnType& fn)
{
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int sx = (x1 < x2 ? 1 : -1);
	int sy = (y1 < y2 ? 1 : -1);

	int error = dx - dy;

	while(x1 > 0 && x1 < m_width && y1 > 0 && y1 < m_height)
	{
		fn(m_tiles[x1 + y1 * m_width]);
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
inline void TileGrid::applyToBox(int x, int y, int width, int height,
		const FnType& fn)
{
	assert(x >= 0);
	assert(y >= 0);

	for(int yPos = 0; yPos < height; ++yPos)
	{
		if(y + yPos >= m_height)
		{
			break;
		}
		for(int xPos = 0; xPos < width; ++xPos)
		{
			if(x + xPos >= m_width)
			{
				break;
			}
			fn(m_tiles[x + xPos + (y + yPos) * m_width]);
		}
	}
}


}



#endif
