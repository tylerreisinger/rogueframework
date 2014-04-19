#include "Color.h"

namespace rf
{

uint32_t Color::toRGB() const
{
	return (static_cast<uint8_t>((red * 255)) << 16) | (static_cast<uint8_t>((green * 255)) << 8) | static_cast<uint8_t>((blue * 255));
}

uint32_t Color::toRGBA() const
{
	return ((static_cast<uint8_t>((red * 255)) << 24) | (static_cast<uint8_t>((green * 255)) << 16) | (static_cast<uint8_t>((blue * 255)) << 8) | (static_cast<uint8_t>((alpha * 255))));
}

uint32_t Color::toABGR() const
{
	return ((static_cast<uint8_t>((red * 255))) | (static_cast<uint8_t>((green * 255)) << 8) | (static_cast<uint8_t>((blue * 255)) << 16) | (static_cast<uint8_t>((alpha * 255)) << 24));
}

bool Color::operator ==(const Color& color) const
{
	return (red == color.red && green == color.green && blue == color.blue && alpha == color.alpha);
}

bool Color::operator !=(const Color& color) const
{
	return (red != color.red || green != color.green || blue != color.blue || alpha != color.alpha);
}

Color Color::alphaBlend(const Color& color1, const Color& color2)
{
	return Color::fromByteChannels(color1.red * color1.alpha + color2.red * color2.alpha * (1. - color1.alpha),
				   color1.green * color1.alpha + color2.green * color2.alpha * (1. - color1.alpha),
				   color1.blue * color1.alpha + color2.blue * color2.alpha * (1. - color1.alpha),
				   color1.alpha + color2.alpha * (1. - color1.alpha));
}

Color Color::fromByteChannels(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return Color(red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f);

}

}
