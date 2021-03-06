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

protected:

	Tile m_defaultState;
	Tile m_clearState;

	int m_width;
	int m_height;

	std::vector<Tile> m_tiles;
};




}



#endif
