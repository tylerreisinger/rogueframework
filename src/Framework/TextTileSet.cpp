#include "Framework/TextTileSet.h"

#include "Framework/Glyph.h"
#include "Framework/BitmapGlyph.h"
#include "Framework/Gl/Context.h"
#include "Framework/Gl/TextureArray2d.h"

namespace rf
{

TextTileSet::TextTileSet(std::shared_ptr<const FontFace> fontFace, gl::Context* context,
		int maxTiles):
	m_fontFace(std::move(fontFace)),
	m_tiles(maxTiles, std::bind(&TextTileSet::onCacheDrop, this, std::placeholders::_1, std::placeholders::_2)),
	m_context(context), m_maxTiles(maxTiles)
{
	m_freeSlots.reserve(maxTiles);

	auto gCharacter = std::static_pointer_cast<const BitmapGlyph>(m_fontFace->getGlyph('g'));
	int belowBaseline = gCharacter->top() - gCharacter->rows();
	if(belowBaseline > 0)
	{
		belowBaseline = 0;
	}
	m_tileHeight = -belowBaseline + m_fontFace->lineHeight();
	m_vertShift = -belowBaseline;

	auto size = computeTextureSize();
	m_textureWidth = size.x;
	m_textureHeight = size.y;

	int tilesPerTex = tilesPerRow() * rows();
	m_textureLayers = std::ceil(static_cast<double>(maxTiles) / tilesPerTex);
	m_tilesTexture.reset(new gl::TextureArray2d(m_textureWidth, m_textureHeight, m_textureLayers,
			1, gl::Texture::InternalPixelFormat::RGBA8, context));
	m_tilesTexture->setFilterModes(gl::Texture::FilterMode::Linear, gl::Texture::FilterMode::Linear);


	m_cellWidth = tileWidth() / static_cast<double>(m_textureWidth);
	m_cellHeight = tileHeight() / static_cast<double>(m_textureHeight);



	addInitialSlots();
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
		if(m_tiles.size() >= m_maxTiles - 1)
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

	Rectanglei tileLocation{static_cast<int>(location.bottomLeft.x * m_textureWidth),
							static_cast<int>(location.bottomLeft.y * m_textureHeight),
							tileWidth(),
							tileHeight()};

	m_tilesTexture->bind();
	m_tilesTexture->setData(tileLocation, location.layer, 1, 0, gl::Texture::DataPixelFormat::BGRA,
			gl::Texture::PixelType::UByte, bitmapData.get());
}

std::unique_ptr<uint32_t[]> TextTileSet::copyGlyphBitmap(std::shared_ptr<const BitmapGlyph> glyph)
{
	int bitmapSize = tileWidth() * tileHeight();

	auto data = std::unique_ptr<uint32_t []>(new uint32_t[bitmapSize]);
	std::fill(data.get(), &data[bitmapSize], 0);

	int maxUp = m_tileHeight - m_fontFace->lineHeight();

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
			int yPos = y + tileHeight() - glyph->top() /*+ belowBaseline*/ - m_vertShift/* - 3*/;
			int index = xPos + yPos * tileWidth();
			//Set color to white and alpha to the color in the glyph bitmap.
			if(index < bitmapSize && index >= 0)
			{
				data[index] = 0x00FFFFFF | (sourceBitmap[x + y * glyph->pitch()] << 24);
			}
		}
	}
	return data;
}

void TextTileSet::onCacheDrop(const int& character,
		const TileLocation& location)
{
	m_freeSlots.push_back(location);
}

Vector2i TextTileSet::computeTextureSize()
{
	Vector2i size = {1024, 1024};
	int area = tileWidth() * tileHeight() * m_maxTiles;
	for(int width = 8; width < 2048; width <<= 1)
	{
		bool found = false;
		for(int height = width >> 1; height < width << 2; height <<= 1)
		{
			int tilesPerRow = width / tileWidth();
			int rows = height / tileHeight();
			if(tilesPerRow * rows >= m_maxTiles)
			{
				size = {width, height};
				found = true;
				break;
			}
		}
		if(found)
		{
			break;
		}
	}

	return size;
}

TextTileSet::TextTileSet(TextTileSet&& other) noexcept:
	m_fontFace(std::move(other.m_fontFace)), m_tilesTexture(std::move(other.m_tilesTexture)),
	m_tiles(std::move(other.m_tiles)), m_freeSlots(std::move(other.m_freeSlots)),
	m_context(other.m_context), m_cellWidth(other.m_cellWidth), m_cellHeight(other.m_cellHeight),
	m_maxTiles(other.m_maxTiles), m_textureWidth(other.m_textureWidth),
	m_textureHeight(other.m_textureHeight), m_textureLayers(other.m_textureLayers)
{

}

TextTileSet& TextTileSet::operator =(TextTileSet&& other) noexcept
{
	m_fontFace = std::move(other.m_fontFace);
	m_tilesTexture = std::move(other.m_tilesTexture);
	m_tiles = std::move(other.m_tiles);
	m_freeSlots = std::move(other.m_freeSlots);
	m_context = other.m_context;
	m_cellWidth = other.m_cellWidth;
	m_cellHeight = other.m_cellHeight;
	m_maxTiles = other.m_maxTiles;
	m_textureWidth = other.m_textureWidth;
	m_textureHeight = other.m_textureHeight;
	m_textureLayers = other.m_textureLayers;
	other.m_maxTiles = 0;
	other.m_context = nullptr;
	return *this;
}

void TextTileSet::addInitialSlots()
{
	int cols = tilesPerRow();
	int rowsVal = rows();

	for(int i = static_cast<int>(m_maxTiles - 1); i >= 0; --i)
	{
		int x = i % cols;
		int y = (i / cols) % rowsVal;
		int z = i / cols / rowsVal;

		float startX = static_cast<float>(x * m_cellWidth);
		float startY = static_cast<float>(y * m_cellHeight);

		m_freeSlots.push_back(TileLocation{m_tilesTexture.get(), Vector2f(startX, startY),
			Vector2f(startX + m_cellWidth, startY + m_cellHeight), z, 0});
	}
}

}
