#ifndef TEXTTILESET_H_
#define TEXTTILESET_H_

#include "TileSet.h"

#include <vector>
#include <memory>

#include "Framework/Gl/TextureArray2d.h"
#include "Framework/FontFace.h"
#include "Framework/LruCache.h"

namespace rf
{
class BitmapGlyph;

namespace gl
{
class Context;
class TextureArray2d;
}

class TextTileSet : public TileSet
{
public:
	TextTileSet(std::shared_ptr<const FontFace> fontFace, gl::Context* context);
	~TextTileSet() = default;

	virtual int tileWidth() const override {return m_fontFace->maxAdvanceWidth();}
	virtual int tileHeight() const override {return m_fontFace->lineHeight();}

	virtual TileLocation getTileLocation(int index) override;

	static constexpr int maxTiles = 2500;
	static constexpr int textureWidth = 1024;
	static constexpr int textureHeight = 1024;

protected:

	void addGlyph(TileLocation& location, int character);
	std::unique_ptr<uint32_t []> copyGlyphBitmap(std::shared_ptr<const BitmapGlyph> glyph);
	void onCacheDrop(const int& character, const TileLocation& location);

	std::shared_ptr<const FontFace> m_fontFace;
	std::unique_ptr<gl::TextureArray2d> m_tilesTexture;
	LruCache<int, TileLocation> m_tiles;
	std::vector<TileLocation> m_freeSlots;
	gl::Context* m_context;

	float m_cellWidth;
	float m_cellHeight;
};

}

#endif
