#include "Tile.h"

namespace rf
{

Tile::Tile(const Colorf& foregroundColor, const Colorf& backgroundColor,
		unsigned int tileIndex):
	m_foregroundColor(foregroundColor), m_backgroundColor(backgroundColor),
	m_tileIndex(tileIndex)
{
}

}

