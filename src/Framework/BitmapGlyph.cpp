#include "Framework/BitmapGlyph.h"

namespace rf
{

BitmapGlyph::BitmapGlyph(FT_BitmapGlyph bitmapGlyph): Glyph(&bitmapGlyph->root),
	m_bitmapGlyph(bitmapGlyph)
{

}

BitmapGlyph::BitmapGlyph(const BitmapGlyph& other): Glyph(other),
	m_bitmapGlyph(other.m_bitmapGlyph)
{
}

BitmapGlyph::BitmapGlyph(BitmapGlyph&& other): Glyph(std::move(other)),
	m_bitmapGlyph(other.m_bitmapGlyph)
{
	other.m_bitmapGlyph = nullptr;
}

BitmapGlyph& BitmapGlyph::operator =(const BitmapGlyph& other)
{
	if(&other != this)
	{
		Glyph::operator =(other);
		m_bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(m_glyph);
	}
	return *this;
}

BitmapGlyph& BitmapGlyph::operator =(BitmapGlyph&& other)
{
	if(&other != this)
	{
		Glyph::operator =(std::move(other));
		m_bitmapGlyph = other.m_bitmapGlyph;
		other.m_bitmapGlyph = nullptr;
	}
	return *this;
}


BitmapGlyph::~BitmapGlyph()
{
}

}


