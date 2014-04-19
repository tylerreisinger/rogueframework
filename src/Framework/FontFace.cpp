#include "FontFace.h"

#include "Exceptions/FreeTypeException.h"
#include "make_unique.h"
#include "FontManager.h"

namespace rf
{

FontFace::FontFace(FontManager* manager, std::shared_ptr<std::vector<unsigned char>>& fontData,
		int width, int height, int faceIndex, const Flags<GlyphLoadFlags>& loadFlags):
	m_fontData(fontData), m_cache(1000), m_manager(manager), m_loadFlags(loadFlags)
{
	int error = FT_New_Memory_Face(manager->getFreeTypeLibrary(),
			fontData.get()->data(), fontData.get()->size(), faceIndex, &m_face);
	if(error)
	{
		throw FreeTypeException("FT_New_Memory_Face failed", error);
	}
	setCharacterSize(width, height);
}

FontFace::~FontFace()
{
	if(m_face != nullptr)
	{
		FT_Done_Face(m_face);
	}
}

FontFace::FontFace(FontFace&& face) noexcept:
	m_face(face.m_face), m_fontData(std::move(face.m_fontData)), m_cache(std::move(face.m_cache)),
	m_loadFlags(face.m_loadFlags)
{
	face.m_face = nullptr;
}

FontFace& FontFace::operator =(FontFace&& face) noexcept
{
	if(&face != this)
	{
		if(m_face != nullptr)
		{
			FT_Done_Face(m_face);
		}
		m_face = face.m_face;
		m_fontData = std::move(face.m_fontData);
		m_cache = std::move(face.m_cache);
		m_loadFlags = face.m_loadFlags;
		face.m_face = nullptr;
	}
	return *this;
}

std::string FontFace::getFamilyName() const
{
	if(m_face->family_name)
	{
		return std::string(m_face->family_name);
	}
	return std::string("");
}

std::string FontFace::getStyleName() const
{
	if(m_face->style_name)
	{
		return std::string(m_face->style_name);
	}
	return std::string("");
}

void FontFace::setCharacterSizeInPoints(float sizeInPoints, float dpiX, float dpiY)
{
	m_cache.clear();
	int error = FT_Set_Char_Size(m_face, 0, static_cast<int>(sizeInPoints / 64.), dpiX, dpiY);
	if(error)
	{
		throw FreeTypeException("FT_Set_Char_Size failed", error);
	}

}

FontFace FontFace::cloneWithNewSize(int width, int height) const
{
	return FontFace(m_manager, m_fontData, width, height, 0, m_loadFlags);
}

std::vector<BitmapFontSize> FontFace::availableSizes() const
{
	std::vector<BitmapFontSize> sizes(fixedSizeCount());
	for(int i = 0; i < fixedSizeCount(); ++i)
	{
		auto& sizeData = m_face->available_sizes[i];
		sizes[i].height = sizeData.height;
		sizes[i].width = sizeData.width;
		sizes[i].size = frac266ToFloat(sizeData.size);
		sizes[i].xPixelsPerEm = frac266ToFloat(sizeData.x_ppem);
		sizes[i].yPixelsPerEm = frac266ToFloat(sizeData.x_ppem);
	}
	return sizes;
}

std::vector<FontFace::CharMap> FontFace::charMaps() const
{
	std::vector<FontFace::CharMap> maps(charMapCount());

	for(int i = 0; i < charMapCount(); ++i)
	{
		auto charData = m_face->charmaps[i];
		maps[i].encoding = static_cast<CharMapEncoding>(charData->encoding);
		maps[i].encodingId = charData->encoding_id;
		maps[i].platformId = charData->platform_id;
	}
	return maps;
}

bool FontFace::hasCharMap(CharMapEncoding encoding) const
{
	for(int i = 0; i < charMapCount(); ++i)
	{
		if(static_cast<CharMapEncoding>(m_face->charmaps[i]->encoding) == encoding)
		{
			return true;
		}
	}
	return false;
}

FontFace::CharMap FontFace::currentCharMap() const
{
	CharMap map;
	map.encoding = static_cast<CharMapEncoding>(m_face->charmap->encoding);
	map.encodingId = m_face->charmap->encoding_id;
	map.platformId = m_face->charmap->platform_id;
	return map;
}

void FontFace::setCharacterSize(int width, int height)
{
	m_cache.clear();
	int error = FT_Set_Pixel_Sizes(m_face, width, height);
	if(error)
	{
		throw FreeTypeException("FT_Set_Pixel_Sizes failed", error);
	}
}

FT_Glyph FontFace::getGlyph(char32_t character) const
{
	FT_Glyph ftGlyph;

	auto glyphIndex = FT_Get_Char_Index(m_face, character);
	int error = FT_Load_Glyph(m_face, glyphIndex, m_loadFlags.getRawValue());
	if(error)
	{
		throw FreeTypeException("FT_Set_Pixel_Sizes failed", error);
	}
	error = FT_Get_Glyph(m_face->glyph, &ftGlyph);
	if(error)
	{
		throw FreeTypeException("FT_Get_Glyph failed", error);
	}

	return ftGlyph;
}

std::shared_ptr<Glyph> FontFace::constructGlyphObject(FT_Glyph glyph) const
{
	if(glyph->format == FT_GLYPH_FORMAT_BITMAP)
	{
		return std::make_shared<BitmapGlyph>(glyph);
	}
	else
	{
		return std::make_shared<Glyph>(glyph);
	}
}

std::shared_ptr<Glyph> FontFace::loadGlyph(char32_t character) const
{
	std::shared_ptr<Glyph>* glyphPtr = m_cache.getItem(character);
	if(glyphPtr == nullptr)
	{
		FT_Glyph ftGlyph = getGlyph(character);

		auto glyph = constructGlyphObject(ftGlyph);
		m_cache.addItem(character, glyph);
		return glyph;
	}
	else
	{
		return *glyphPtr;
	}
}

int FontFace::getKerningOffset(char32_t leftChar, char32_t rightChar, KerningMode mode) const
{
	FT_Vector kerning;
	int error = FT_Get_Kerning(m_face, leftChar, rightChar, static_cast<FT_Kerning_Mode>(mode), &kerning);
	if(error != 0)
	{
		throw FreeTypeException("FT_Get_Kerning failed", error);
	}
	return kerning.x >> 8;
}

Rectanglei FontFace::computeLayoutBox(const Glyph* glyph, const Vector2i& origin) const
{
	Rectanglei controlBox = glyph->getControlBox();
	return Rectanglei(origin.x, origin.y + lineHeight(), origin.x + glyph->advance(), origin.y - controlBox.bottom());
}

bool FontFace::hasCharacter(char32_t chr) const
{
	return FT_Get_Char_Index(m_face, chr) != 0;
}

void FontFace::selectFixedSize(int index)
{
	m_cache.clear();
	int error = FT_Select_Size(m_face, index);
	if(error)
	{
		throw FreeTypeException("FT_Select_Size failed", error);
	}
}

void FontFace::selectCharMap(CharMapEncoding encoding)
{
	m_cache.clear();
	int error = FT_Select_Charmap(m_face, static_cast<FT_Encoding>(encoding));
	if(error)
	{
		throw FreeTypeException("FT_Select_Charmap failed", error);
	}
}

}
