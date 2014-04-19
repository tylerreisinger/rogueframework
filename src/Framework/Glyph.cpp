#include "Glyph.h"

#include <algorithm>

#include "Exceptions/FreeTypeException.h"
#include "BitmapGlyph.h"

namespace rf
{

Glyph::Glyph(FT_Glyph glyph):
	m_glyph(glyph)
{

}

Glyph::~Glyph()
{
	if(m_glyph != nullptr)
	{
		FT_Done_Glyph(m_glyph);
	}
}

Glyph::Glyph(const Glyph& glyph)
{
	int error = FT_Glyph_Copy(glyph.m_glyph, &m_glyph);
	if(error != 0)
	{
		throw FreeTypeException("FT_Glyph_Copy failed", error);
	}
}

Glyph::Glyph(Glyph&& glyph) noexcept
{
	m_glyph = glyph.m_glyph;
	glyph.m_glyph = nullptr;
}

Glyph& Glyph::operator =(const Glyph& glyph)
{
	if(&glyph != this)
	{
		if(m_glyph != nullptr)
		{
			FT_Done_Glyph(m_glyph);
		}
		int error = FT_Glyph_Copy(glyph.m_glyph, &m_glyph);
		if(error != 0)
		{
			throw FreeTypeException("FT_Glyph_Copy failed", error);
		}
	}
	return *this;
}

Glyph& Glyph::operator =(Glyph&& glyph) noexcept
{
	if(&glyph != this)
	{
		if(m_glyph != nullptr)
		{
			FT_Done_Glyph(m_glyph);
		}
		m_glyph = glyph.m_glyph;
		glyph.m_glyph = nullptr;
	}
	return *this;
}
Rectanglei Glyph::getControlBox() const
{
	FT_BBox bbox;
	FT_Glyph_Get_CBox(m_glyph, FT_GLYPH_BBOX_PIXELS, &bbox);
	return Rectanglei::fromVertices(bbox.xMin >> 6, -bbox.yMax >> 6, bbox.xMax >> 6, -bbox.yMin >> 6);
}

BitmapGlyph Glyph::makeBitmapGlyph(RenderMode mode) const
{
	FT_Glyph glyph = m_glyph;
	int error = FT_Glyph_To_Bitmap(&glyph, static_cast<FT_Render_Mode>(mode), nullptr, false);
	return BitmapGlyph(reinterpret_cast<FT_BitmapGlyph>(glyph));
}

}


