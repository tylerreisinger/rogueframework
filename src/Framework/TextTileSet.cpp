#include "Framework/TextTileSet.h"

#include "Framework/Glyph.h"
#include "Framework/BitmapGlyph.h"
#include "Framework/Gl/Context.h"
#include "Framework/Gl/TextureArray2d.h"

namespace rf
{

TextTileSet::TextTileSet(std::shared_ptr<const FontFace> fontFace, gl::Context* context):
	m_fontFace(std::move(fontFace)),
	m_tiles(maxTiles, std::bind(&TextTileSet::onCacheDrop, this, std::placeholders::_1, std::placeholders::_2)),
	m_context(context)
{
	m_freeSlots.reserve(maxTiles);
	int tilesPerRow = textureWidth / tileWidth();
	int rows = textureHeight / tileHeight();

	int tilesPerTex = tilesPerRow * rows;
	int layers = std::ceil(static_cast<double>(maxTiles) / tilesPerTex);
	m_tilesTexture.reset(new gl::TextureArray2d(textureWidth, textureHeight, layers,
			1, gl::Texture::InternalPixelFormat::RGBA8, context));

	m_cellWidth = 1.0f / tilesPerRow;
	m_cellHeight = 1.0f / rows;

	for(int i = maxTiles - 1; i >= 0; --i)
	{
		int x = i % tilesPerRow;
		int y = (i / tilesPerRow) % rows;
		int z = i / tilesPerRow / rows;

		float startX = x * m_cellWidth;
		float startY = y * m_cellHeight;

		m_freeSlots.push_back(TileLocation{m_tilesTexture.get(), Vector2f(startX, startY),
			Vector2f(startX + m_cellWidth, startY + m_cellHeight), z, 0});
	}
}

TextTileSet::TileLocation TextTileSet::getTileLocation(int index)
{
	TileLocation* cell = m_tiles.getItem(index);
	if(cell != nullptr)
	{
		return *cell;
	}
	else
	{
		if(m_tiles.size() >= maxTiles - 1)
		{
			m_tiles.dropOne();
		}
		TileLocation newCell = m_freeSlots.back();
		m_freeSlots.pop_back();
		m_tiles.addItem(index, newCell);
		addGlyph(newCell, index);
		return newCell;
	}
}

void TextTileSet::addGlyph(TileLocation& location, int character)
{
	std::shared_ptr<const BitmapGlyph> glyph = std::static_pointer_cast<const BitmapGlyph>(m_fontFace->getGlyph(character));

	auto bitmapData = copyGlyphBitmap(glyph);

	Rectanglei tileLocation(location.bottomLeft * textureWidth, location.topRight * textureHeight);

	m_tilesTexture->bind();
	m_tilesTexture->setData(tileLocation, location.layer, 1, 0, gl::Texture::DataPixelFormat::BGRA,
			gl::Texture::PixelType::UByte, bitmapData.get());
}

std::unique_ptr<uint32_t[]> TextTileSet::copyGlyphBitmap(std::shared_ptr<const BitmapGlyph> glyph)
{
	int bitmapSize = tileWidth() * tileHeight();

	auto data = std::unique_ptr<uint32_t []>(new uint32_t[bitmapSize]);
	std::fill(data.get(), &data[bitmapSize], 0);

	int belowBaseline = glyph->top() - glyph->rows();
	if(belowBaseline > 0)
	{
		belowBaseline = 0;
	}

	const unsigned char* sourceBitmap = glyph->buffer();
	for(int x = 0; x < glyph->width(); ++x)
	{
		for(int y = 0; y < glyph->rows(); ++y)
		{
			int xPos = x + glyph->left();
			//Adjust upwards if the glyph extends below the baseline
			int yPos = y + tileHeight() - glyph->top() + belowBaseline;
			int index = xPos + yPos * tileWidth();
			//Set color to white and alpha to the color in the glyph bitmap.
			data[index] = (sourceBitmap[x + y * glyph->pitch()] << 24) | (sourceBitmap[x + y * glyph->pitch()] << 16)
					| (sourceBitmap[x + y * glyph->pitch()] << 8) | (sourceBitmap[x + y * glyph->pitch()] << 0);
		}
	}
	return data;
}

void TextTileSet::onCacheDrop(const int& character,
		const TileLocation& location)
{
	m_freeSlots.push_back(location);
}

}
