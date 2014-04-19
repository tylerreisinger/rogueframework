#ifndef GLYPH_H_
#define GLYPH_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "Rectangle.h"

namespace rf
{
class BitmapGlyph;

class Glyph
{
public:

	enum class Format
	{
		Composite = FT_GLYPH_FORMAT_COMPOSITE,
		Bitmap = FT_GLYPH_FORMAT_BITMAP,
		Outline = FT_GLYPH_FORMAT_OUTLINE,
		Plotter = FT_GLYPH_FORMAT_PLOTTER
	};

	enum class RenderMode
	{
		Normal = FT_RENDER_MODE_NORMAL,
		Mono = FT_RENDER_MODE_MONO,
		Lcd = FT_RENDER_MODE_LCD,
		LcdV = FT_RENDER_MODE_LCD_V
	};

	struct BitmapInfo
	{
		int top;
		int left;

		int rows;
		int pitch;
		int width;
		const unsigned char* buffer;
	};

	explicit Glyph(FT_Glyph glyph);
	virtual ~Glyph();

	Glyph(const Glyph& glyph);
	Glyph(Glyph&& glyph) noexcept;
	Glyph& operator =(const Glyph& glyph);
	Glyph& operator =(Glyph&& glyph) noexcept;

	int advance() const  {return m_glyph->advance.x >> 16;}
	int descent() const {return getControlBox().bottom();}

	Format format() {return static_cast<Format>(m_glyph->format);}

	BitmapGlyph makeBitmapGlyph(RenderMode mode) const;

	Rectanglei getControlBox() const;

protected:

	FT_Glyph m_glyph = nullptr;
};

}

#endif /* GLYPH_H_ */
