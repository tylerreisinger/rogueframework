#include "Tile.h"

namespace rf
{

Tile::Tile(const Color& foregroundColor, const Color& backgroundColor,
		int tileIndex):
		m_foregroundColor(foregroundColor), m_backgroundColor(backgroundColor),
	m_tileIndex(tileIndex)
{
}

}
