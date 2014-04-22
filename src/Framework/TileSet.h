#ifndef TILESET_H_
#define TILESET_H_

#include "Framework/Vector2.h"

namespace rf
{
namespace gl
{
class Texture;
}

class TileSet
{
public:

	struct TileLocation
	{
		gl::Texture* texture;

		Vector2f bottomLeft;
		Vector2f topRight;

		int layer;
		int verticalOffset;
	};

	TileSet();
	virtual ~TileSet();

	virtual int tileWidth() const = 0;
	virtual int tileHeight() const = 0;
	virtual TileLocation getTileLocation(int index) = 0;

protected:

};

}

#endif
