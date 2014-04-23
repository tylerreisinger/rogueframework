#include "Colorf.h"

#include "Color.h"

namespace rf
{

uint32_t Colorf::toRgb() const
{
	return (static_cast<uint8_t>((red * 255)) << 16) | (static_cast<uint8_t>((green * 255)) << 8) | static_cast<uint8_t>((blue * 255));
}

uint32_t Colorf::toRgba() const
{
	return ((static_cast<uint8_t>((red * 255)) << 24) | (static_cast<uint8_t>((green * 255)) << 16) | (static_cast<uint8_t>((blue * 255)) << 8) | (static_cast<uint8_t>((alpha * 255))));
}

uint32_t Colorf::toAbgr() const
{
	return ((static_cast<uint8_t>((red * 255))) | (static_cast<uint8_t>((green * 255)) << 8) | (static_cast<uint8_t>((blue * 255)) << 16) | (static_cast<uint8_t>((alpha * 255)) << 24));
}

bool Colorf::operator ==(const Colorf& color) const
{
	return (red == color.red && green == color.green && blue == color.blue && alpha == color.alpha);
}

bool Colorf::operator !=(const Colorf& color) const
{
	return (red != color.red || green != color.green || blue != color.blue || alpha != color.alpha);
}

Colorf Colorf::alphaBlend(const Colorf& color1, const Colorf& color2)
{
	return Colorf::fromByteChannels(color1.red * color1.alpha + color2.red * color2.alpha * (1. - color1.alpha),
				   color1.green * color1.alpha + color2.green * color2.alpha * (1. - color1.alpha),
				   color1.blue * color1.alpha + color2.blue * color2.alpha * (1. - color1.alpha),
				   color1.alpha + color2.alpha * (1. - color1.alpha));
}

Colorf::Colorf(const Color& color):
	red(color.red / 255.0), green(color.green / 255.0), blue(color.blue / 255.0), alpha(color.alpha / 255.0)
{
}

Colorf Colorf::fromByteChannels(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return Colorf(red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f);

}

}
