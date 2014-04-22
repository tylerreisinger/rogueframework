#ifndef FONTFACE_H_
#define FONTFACE_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "Glyph.h"
#include "Flags.h"
#include "LruCache.h"

namespace rf
{
class FontManager;

struct BitmapFontSize
{
	short width;
	short height;

	float size;

	float xPixelsPerEm;
	float yPixelsPerEm;
};



class FontFace
{
	friend class FontManager;
public:
	enum class StyleFlags {Italic = FT_STYLE_FLAG_ITALIC, Bold = FT_STYLE_FLAG_BOLD};

	enum class FaceFlags
	{
		Scalable = FT_FACE_FLAG_SCALABLE,
		FixedSizes = FT_FACE_FLAG_FIXED_SIZES,
		FixedWidth = FT_FACE_FLAG_FIXED_WIDTH,
		SfntFormat = FT_FACE_FLAG_SFNT,
		Horizontal = FT_FACE_FLAG_HORIZONTAL,
		Vertical = FT_FACE_FLAG_VERTICAL,
		Kerning = FT_FACE_FLAG_KERNING,
		MultipleMasters = FT_FACE_FLAG_MULTIPLE_MASTERS,
		GlyphNames = FT_FACE_FLAG_GLYPH_NAMES,
		Hinter = FT_FACE_FLAG_HINTER,
		CidKeyed = FT_FACE_FLAG_CID_KEYED,
		Tricky = FT_FACE_FLAG_TRICKY,
		Color = FT_FACE_FLAG_COLOR
	};

	enum class CharMapEncoding
	{
		Unicode = FT_ENCODING_UNICODE,
		MsSymbol = FT_ENCODING_MS_SYMBOL,
		Sjis = FT_ENCODING_SJIS,
		Gb2312 = FT_ENCODING_GB2312,
		Big5 = FT_ENCODING_BIG5,
		Wansung = FT_ENCODING_WANSUNG,
		Johab = FT_ENCODING_JOHAB,
		Latin1 = FT_ENCODING_ADOBE_LATIN_1,
		AdobeStandard = FT_ENCODING_ADOBE_STANDARD,
		AdobeExpert = FT_ENCODING_ADOBE_EXPERT,
		AdobeCustom = FT_ENCODING_ADOBE_CUSTOM,
		AppleRoman = FT_ENCODING_APPLE_ROMAN
	};

	enum class GlyphLoadFlags
	{
		NoScale = FT_LOAD_NO_SCALE,
		NoHinting = FT_LOAD_NO_HINTING,
		NoBitmap = FT_LOAD_NO_BITMAP,
		Render = FT_LOAD_RENDER,
		VerticalLayout = FT_LOAD_VERTICAL_LAYOUT,
		ForceAutohint = FT_LOAD_FORCE_AUTOHINT,
		CropBitmap = FT_LOAD_CROP_BITMAP,
		Pedantic = FT_LOAD_PEDANTIC,
		Monochrome = FT_LOAD_MONOCHROME,
		LinearDesign = FT_LOAD_LINEAR_DESIGN,
		NoAutohint = FT_LOAD_NO_AUTOHINT,
		LoadColor = FT_LOAD_COLOR
	};

	enum class KerningMode
	{
		Default = FT_KERNING_DEFAULT,
		Unfitted = FT_KERNING_UNFITTED,
		Unscaled = FT_KERNING_UNSCALED
	};

	struct CharMap
	{
		CharMapEncoding encoding;
		unsigned short platformId;
		unsigned short encodingId;
	};

	~FontFace();

	FontFace(const FontFace&) = delete;
	FontFace& operator =(const FontFace&) = delete;

	FontFace(FontFace&& face) noexcept;
	FontFace& operator =(FontFace&& face) noexcept;

	FontFace cloneWithNewSize(int width, int height) const;

	std::string getFamilyName() const;
	std::string getStyleName() const;

	int getCharacterSize() const {return m_face->size->metrics.x_ppem;}
	int getFaceIndex() const {return m_face->face_index;}
	int getNumberOfFaces() const {return m_face->face_index;}

	int lineHeight() const {return m_face->size->metrics.height >> 6;}
	int maxAdvanceWidth() const {return m_face->size->metrics.max_advance >> 6;}

	int fixedSizeCount() const {return m_face->num_fixed_sizes;}
	std::vector<BitmapFontSize> availableSizes() const;

	unsigned short unitsPerEm() const {return m_face->units_per_EM;}

	bool hasCharacter(char32_t chr) const;

	float underlinePosition() const {return frac266ToFloat(FT_MulFix(m_face->underline_position, m_face->size->metrics.y_scale));}
	float underlineThickness() const {return frac266ToFloat(FT_MulFix(m_face->underline_thickness, m_face->size->metrics.y_scale));}

	float ascender() const {return m_face->size->metrics.ascender / 64.f;}
	float descender() const {return m_face->size->metrics.descender / 64.f;}

	int charMapCount() const {return m_face->num_charmaps;}
	std::vector<CharMap> charMaps() const;
	CharMap currentCharMap() const;
	bool hasCharMap(CharMapEncoding encoding) const;

	std::shared_ptr<Glyph> getGlyph(char32_t character) const;

	long glyphCount() const {return m_face->num_glyphs;}
	Flags<StyleFlags> getStyleFlags() const {return Flags<StyleFlags>(static_cast<StyleFlags>(m_face->style_flags));}
	Flags<FaceFlags> getFlags() const {return Flags<FaceFlags>(static_cast<FaceFlags>(m_face->face_flags));}
	Flags<GlyphLoadFlags> getGlyphLoadFlags() const {return m_loadFlags;}

	int getKerningOffset(char32_t leftChar, char32_t rightChar, KerningMode mode = KerningMode::Default) const;

	Rectanglei computeLayoutBox(const Glyph* glyph, const Vector2i& origin = Vector2i::zero()) const;

	void setCharacterSizeInPoints(float sizeInPoints, float dpiX = 72., float dpiY = 72.);
	void setCharacterSize(int width, int height);

	void selectFixedSize(int index);

	void selectCharMap(CharMapEncoding encoding);

	void setGlyphLoadFlag(GlyphLoadFlags flag) {m_cache.clear(); m_loadFlags.setFlag(flag);}
	void unsetGlyphLoadFlag(GlyphLoadFlags flag) {m_cache.clear(); m_loadFlags.clearFlag(flag);}
	void setGlyphLoadFlags(const Flags<GlyphLoadFlags>& flags) {m_cache.clear(); m_loadFlags = flags;}

protected:
	FontFace(FontManager* manager, std::shared_ptr<std::vector<unsigned char>>& fontData,
			int width, int height, int faceIndex = 0, const Flags<GlyphLoadFlags>& loadFlags = {});

	static float frac266ToFloat(int val) {return val / 64.f;}

	FT_Glyph loadGlyph(char32_t character) const;
	std::shared_ptr<Glyph> constructGlyphObject(FT_Glyph glyph) const;

	mutable LruCache<char32_t, std::shared_ptr<Glyph>> m_cache;

	mutable std::shared_ptr<std::vector<unsigned char>> m_fontData;

	Flags<GlyphLoadFlags> m_loadFlags;

	FT_Face m_face = nullptr;
	FontManager* m_manager = nullptr;
};

}

#endif
