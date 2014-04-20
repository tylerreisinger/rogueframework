#ifndef TILEGRID_H_
#define TILEGRID_H_

#include "Tile.h"

#include <vector>
#include <cstring>

#include "Vector2.h"

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

	TileGrid(int width, int height, const Vector2i& location);
	virtual ~TileGrid() = default;

	TileGrid(const TileGrid& other);
	TileGrid(TileGrid&& other) noexcept;
	TileGrid& operator =(const TileGrid& other);
	TileGrid& operator =(TileGrid&& other) noexcept;

	Tile& operator [](size_t index) {return getTile(index);}

	int width() const {return m_width;}
	int height() const {return m_height;}
	const Vector2i location() const {return m_location;}

	Tile& getTile(size_t index) {return m_tiles[index];}
	Tile& getTile(int x, int y) {return m_tiles[x + m_width * y];}

	void setTile(size_t index, const Tile& tile) {m_tiles[index] = tile;}
	void setTile(int x, int y, const Tile& tile) {m_tiles[x + m_width * y] = tile;}

protected:

	int m_width;
	int m_height;
	Vector2i m_location;

	std::vector<Tile> m_tiles;
};

}

#endif
