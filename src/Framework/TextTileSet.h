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
	TextTileSet(std::shared_ptr<const FontFace> fontFace, gl::Context* context,
			int maxTiles);
	~TextTileSet() = default;

	TextTileSet(const TextTileSet&) = delete;
	TextTileSet(TextTileSet&& other) noexcept;
	TextTileSet& operator =(const TextTileSet&) = delete;
	TextTileSet& operator =(TextTileSet&& other) noexcept;

	virtual int tileWidth() const override {return m_fontFace->maxAdvanceWidth();}
	virtual int tileHeight() const override {return m_fontFace->lineHeight();}

	virtual TileLocation getTileLocation(int index) override;

	int textureWidth() const {return m_textureWidth;}
	int textureHeight() const {return m_textureHeight;}
	int textureLayers() const {return m_textureLayers;}

	int tilesPerRow() const {return textureWidth() / tileWidth();}
	int rows() const {return textureHeight() / tileHeight();}


protected:

	void addGlyph(TileLocation& location, int character);
	std::unique_ptr<uint32_t []> copyGlyphBitmap(std::shared_ptr<const BitmapGlyph> glyph);
	void onCacheDrop(const int& character, const TileLocation& location);

	Vector2i computeTextureSize();
	void addInitialSlots();

	std::shared_ptr<const FontFace> m_fontFace;
	std::unique_ptr<gl::TextureArray2d> m_tilesTexture;
	LruCache<int, TileLocation> m_tiles;
	std::vector<TileLocation> m_freeSlots;
	gl::Context* m_context;

	double m_cellWidth;
	double m_cellHeight;
	int m_maxTiles;
	int m_textureWidth;
	int m_textureHeight;
	int m_textureLayers;
};

}

#endif
