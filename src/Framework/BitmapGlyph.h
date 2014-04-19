#ifndef BITMAPGLYPH_H_
#define BITMAPGLYPH_H_

#include "Framework/Glyph.h"

namespace rf
{

class BitmapGlyph: public rf::Glyph
{
public:

	enum class PixelMode
	{
		Mono = FT_PIXEL_MODE_MONO,
		Gray = FT_PIXEL_MODE_GRAY,
		Gray2 = FT_PIXEL_MODE_GRAY2,
		Gray4 = FT_PIXEL_MODE_GRAY4,
		Lcd = FT_PIXEL_MODE_LCD,
		LcdV = FT_PIXEL_MODE_LCD_V,
		Bgra = FT_PIXEL_MODE_BGRA
	};

	explicit BitmapGlyph(FT_BitmapGlyph bitmapGlyph);
	virtual ~BitmapGlyph();

	BitmapGlyph(const BitmapGlyph& other);
	BitmapGlyph(BitmapGlyph&& other);

	BitmapGlyph& operator =(const BitmapGlyph& other);
	BitmapGlyph& operator =(BitmapGlyph&& other);

	int left() const {return m_bitmapGlyph->left;}
	int top() const {return m_bitmapGlyph->top;}

	int rows() const {return m_bitmapGlyph->bitmap.rows;}
	int width() const {return m_bitmapGlyph->bitmap.width;}
	int pitch() const {return m_bitmapGlyph->bitmap.pitch;}

	short numGrays() const {return m_bitmapGlyph->bitmap.num_grays;}

	PixelMode pixelMode() const {return static_cast<PixelMode>(m_bitmapGlyph->bitmap.pixel_mode);}

	const unsigned char* buffer() const {return m_bitmapGlyph->bitmap.buffer;}


protected:
	FT_BitmapGlyph m_bitmapGlyph;
};

}

#endif
