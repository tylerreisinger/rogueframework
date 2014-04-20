#ifndef TILE_H_
#define TILE_H_

#include "Framework/Color.h"

namespace rf
{

class Tile
{
public:
	Tile() {};
	Tile(const Color& foregroundColor, const Color& backgroundColor, int tileIndex);
	~Tile() = default;

	const Color& foregroundColor() const {return m_foregroundColor;}
	const Color& backgroundColor() const {return m_backgroundColor;}
	int tileIndex() const {return m_tileIndex;}

	void setForegroundColor(const Color& color) {m_foregroundColor = color;}
	void setBackgroundColor(const Color& color) {m_backgroundColor = color;}
	void setTileIndex(int index) {m_tileIndex = index;}

protected:
	Color m_foregroundColor = Color::white();
	Color m_backgroundColor = Color::black();
	int m_tileIndex = 0;
};

}

#endif
