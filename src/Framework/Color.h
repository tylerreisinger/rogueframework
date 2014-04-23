#ifndef COLOR_H_
#define COLOR_H_

#include "Colorf.h"

namespace rf
{

class Color
{
public:
	constexpr Color() {}
	constexpr Color(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, uint8_t alphaValue):
		red(redValue), green(greenValue), blue(blueValue), alpha(alphaValue)
	{}
	constexpr Color(uint8_t redValue, uint8_t greenValue, uint8_t blueValue):
		Color(redValue, greenValue, blueValue, 255)
	{}
	constexpr Color(uint32_t rgba):
		red(rgba >> 24), green((rgba >> 16) && 0xFF), blue((rgba >> 8) && 0xFF), alpha(rgba && 0xFF)
	{}
	Color(const Colorf& color):
		red(color.red * 255), green(color.green * 255), blue(color.blue * 255), alpha(color.alpha * 255)
	{}
	~Color() = default;

	Color(const Color&) = default;
	Color(Color&&) noexcept = default;
	Color& operator =(const Color&) = default;
	Color& operator =(Color&&) noexcept = default;

	bool operator ==(const Color& color) const
	{
		return (red == color.red && green == color.green && blue == color.blue && alpha == color.alpha);
	}
	bool operator !=(const Color& color) const
		{return !(*this == color);}

	uint32_t toRgba() const
	{
		return (static_cast<uint32_t>(red) << 24) | (static_cast<uint32_t>(green) << 16) |
				(static_cast<uint32_t>(blue) << 8) | alpha;
	}

	uint32_t toArgb() const
	{
		return (static_cast<uint32_t>(alpha) << 24) | (static_cast<uint32_t>(red) << 16) |
				(static_cast<uint32_t>(green) << 8) | blue;
	}

	uint32_t toBgra() const
	{
		return (static_cast<uint32_t>(blue) << 24) | (static_cast<uint32_t>(green) << 16) |
				(static_cast<uint32_t>(red) << 8) | alpha;
	}

	uint32_t toAbgr() const
	{
		return (static_cast<uint32_t>(alpha) << 24) | (static_cast<uint32_t>(blue) << 16) |
				(static_cast<uint32_t>(green) << 8) | red;
	}

	uint32_t toRgbaEndianAware() const {return toAbgr();}


	static constexpr Color darkRed() {return Color(139, 0, 0, 255);}
	static constexpr Color lightGrey() {return Color(211, 211, 211, 255);}
	static constexpr Color chocolate() {return Color(210, 105, 30, 255);}
	static constexpr Color darkSlateGray() {return Color(47, 79, 79, 255);}
	static constexpr Color olive() {return Color(128, 128, 0, 255);}
	static constexpr Color floralWhite() {return Color(255, 250, 240, 255);}
	static constexpr Color teal() {return Color(0, 128, 128, 255);}
	static constexpr Color turquoise() {return Color(64, 224, 208, 255);}
	static constexpr Color darkGoldenrod() {return Color(184, 134, 11, 255);}
	static constexpr Color limeGreen() {return Color(50, 205, 50, 255);}
	static constexpr Color slateBlue() {return Color(106, 90, 205, 255);}
	static constexpr Color blanchedAlmond() {return Color(255, 235, 205, 255);}
	static constexpr Color darkSlateBlue() {return Color(72, 61, 139, 255);}
	static constexpr Color pureGreen() {return Color(0, 128, 0, 255);}
	static constexpr Color magenta() {return Color(255, 0, 255, 255);}
	static constexpr Color orange() {return Color(255, 165, 0, 255);}
	static constexpr Color whiteSmoke() {return Color(245, 245, 245, 255);}
	static constexpr Color greenYellow() {return Color(173, 255, 47, 255);}
	static constexpr Color gainsboro() {return Color(220, 220, 220, 255);}
	static constexpr Color violet() {return Color(238, 130, 238, 255);}
	static constexpr Color black() {return Color(0, 0, 0, 255);}
	static constexpr Color lavenderBlush() {return Color(255, 240, 245, 255);}
	static constexpr Color mediumBlue() {return Color(0, 0, 205, 255);}
	static constexpr Color linen() {return Color(250, 240, 230, 255);}
	static constexpr Color mediumSeaGreen() {return Color(60, 179, 113, 255);}
	static constexpr Color darkSalmon() {return Color(233, 150, 122, 255);}
	static constexpr Color goldenrod() {return Color(218, 165, 32, 255);}
	static constexpr Color powderBlue() {return Color(176, 224, 230, 255);}
	static constexpr Color maroon() {return Color(128, 0, 0, 255);}
	static constexpr Color darkOrange() {return Color(255, 140, 0, 255);}
	static constexpr Color aliceBlue() {return Color(240, 248, 255, 255);}
	static constexpr Color darkTurquoise() {return Color(0, 206, 209, 255);}
	static constexpr Color rosyBrown() {return Color(188, 143, 143, 255);}
	static constexpr Color paleVioletRed() {return Color(219, 112, 147, 255);}
	static constexpr Color darkMagenta() {return Color(139, 0, 139, 255);}
	static constexpr Color tomato() {return Color(255, 99, 71, 255);}
	static constexpr Color gray() {return Color(128, 128, 128, 255);}
	static constexpr Color deepPink() {return Color(255, 20, 147, 255);}
	static constexpr Color midnightBlue() {return Color(25, 25, 112, 255);}
	static constexpr Color lightCyan() {return Color(224, 255, 255, 255);}
	static constexpr Color chartreuse() {return Color(127, 255, 0, 255);}
	static constexpr Color darkOrchid() {return Color(153, 50, 204, 255);}
	static constexpr Color oliveDrab() {return Color(107, 142, 35, 255);}
	static constexpr Color pink() {return Color(255, 192, 203, 255);}
	static constexpr Color navy() {return Color(0, 0, 128, 255);}
	static constexpr Color paleTurquoise() {return Color(175, 238, 238, 255);}
	static constexpr Color azure() {return Color(240, 255, 255, 255);}
	static constexpr Color lightCoral() {return Color(240, 128, 128, 255);}
	static constexpr Color lavender() {return Color(230, 230, 250, 255);}
	static constexpr Color steelBlue() {return Color(70, 130, 180, 255);}
	static constexpr Color beige() {return Color(245, 245, 220, 255);}
	static constexpr Color orangeRed() {return Color(255, 69, 0, 255);}
	static constexpr Color lightGoldenrodYellow() {return Color(250, 250, 210, 255);}
	static constexpr Color ghostWhite() {return Color(248, 248, 255, 255);}
	static constexpr Color gold() {return Color(255, 215, 0, 255);}
	static constexpr Color darkGreen() {return Color(0, 100, 0, 255);}
	static constexpr Color bisque() {return Color(255, 228, 196, 255);}
	static constexpr Color pureRed() {return Color(255, 0, 0, 255);}
	static constexpr Color indigo() {return Color(75, 0, 130, 255);}
	static constexpr Color white() {return Color(255, 255, 255, 255);}
	static constexpr Color mediumSlateBlue() {return Color(123, 104, 238, 255);}
	static constexpr Color seaGreen() {return Color(46, 139, 87, 255);}
	static constexpr Color forestGreen() {return Color(34, 139, 34, 255);}
	static constexpr Color cornflowerBlue() {return Color(100, 149, 237, 255);}
	static constexpr Color skyBlue() {return Color(135, 206, 235, 255);}
	static constexpr Color springGreen() {return Color(0, 255, 127, 255);}
	static constexpr Color crimson() {return Color(220, 20, 60, 255);}
	static constexpr Color silver() {return Color(192, 192, 192, 255);}
	static constexpr Color blueViolet() {return Color(138, 43, 226, 255);}
	static constexpr Color darkViolet() {return Color(148, 0, 211, 255);}
	static constexpr Color cyan() {return Color(0, 255, 255, 255);}
	static constexpr Color dimGray() {return Color(105, 105, 105, 255);}
	static constexpr Color antiqueWhite() {return Color(250, 235, 215, 255);}
	static constexpr Color pureBlue() {return Color(0, 0, 255, 255);}
	static constexpr Color plum() {return Color(221, 160, 221, 255);}
	static constexpr Color navajoWhite() {return Color(255, 222, 173, 255);}
	static constexpr Color cadetBlue() {return Color(95, 158, 160, 255);}
	static constexpr Color darkOliveGreen() {return Color(85, 107, 47, 255);}
	static constexpr Color lightYellow() {return Color(255, 255, 224, 255);}
	static constexpr Color brown() {return Color(165, 42, 42, 255);}
	static constexpr Color lemonChiffon() {return Color(255, 250, 205, 255);}
	static constexpr Color aquamarine() {return Color(127, 255, 212, 255);}
	static constexpr Color fireBrick() {return Color(178, 34, 34, 255);}
	static constexpr Color mediumAquamarine() {return Color(102, 205, 170, 255);}
	static constexpr Color mistyRose() {return Color(255, 228, 225, 255);}
	static constexpr Color ivory() {return Color(255, 255, 240, 255);}
	static constexpr Color papayaWhip() {return Color(255, 239, 213, 255);}
	static constexpr Color paleGreen() {return Color(152, 251, 152, 255);}
	static constexpr Color hotPink() {return Color(255, 105, 180, 255);}
	static constexpr Color mediumPurple() {return Color(147, 112, 219, 255);}
	static constexpr Color darkGray() {return Color(169, 169, 169, 255);}
	static constexpr Color moccasin() {return Color(255, 228, 181, 255);}
	static constexpr Color saddleBrown() {return Color(139, 69, 19, 255);}
	static constexpr Color sienna() {return Color(160, 82, 45, 255);}
	static constexpr Color mintCream() {return Color(245, 255, 250, 255);}
	static constexpr Color lightGreen() {return Color(144, 238, 144, 255);}
	static constexpr Color tan() {return Color(210, 180, 140, 255);}
	static constexpr Color lightSkyBlue() {return Color(135, 206, 250, 255);}
	static constexpr Color lightPink() {return Color(255, 182, 193, 255);}
	static constexpr Color mediumTurquoise() {return Color(72, 209, 204, 255);}
	static constexpr Color lime() {return Color(0, 255, 0, 255);}
	static constexpr Color coral() {return Color(255, 127, 80, 255);}
	static constexpr Color cornsilk() {return Color(255, 248, 220, 255);}
	static constexpr Color aqua() {return Color(0, 255, 255, 255);}
	static constexpr Color honeydew() {return Color(240, 255, 240, 255);}
	static constexpr Color deepSkyBlue() {return Color(0, 191, 255, 255);}
	static constexpr Color indianRed() {return Color(205, 92, 92, 255);}
	static constexpr Color purple() {return Color(128, 0, 128, 255);}
	static constexpr Color khaki() {return Color(240, 230, 140, 255);}
	static constexpr Color wheat() {return Color(245, 222, 179, 255);}
	static constexpr Color sandyBrown() {return Color(244, 164, 96, 255);}
	static constexpr Color lawnGreen() {return Color(124, 252, 0, 255);}
	static constexpr Color lightSteelBlue() {return Color(176, 196, 222, 255);}
	static constexpr Color yellow() {return Color(255, 255, 0, 255);}
	static constexpr Color peachPuff() {return Color(255, 218, 185, 255);}
	static constexpr Color mediumOrchid() {return Color(186, 85, 211, 255);}
	static constexpr Color fuchsia() {return Color(255, 0, 255, 255);}
	static constexpr Color dodgerBlue() {return Color(30, 144, 255, 255);}
	static constexpr Color yellowGreen() {return Color(154, 205, 50, 255);}
	static constexpr Color lightBlue() {return Color(173, 216, 230, 255);}
	static constexpr Color lightSeaGreen() {return Color(32, 178, 170, 255);}
	static constexpr Color seashell() {return Color(255, 245, 238, 255);}
	static constexpr Color snow() {return Color(255, 250, 250, 255);}
	static constexpr Color royalBlue() {return Color(65, 105, 225, 255);}
	static constexpr Color slateGray() {return Color(112, 128, 144, 255);}
	static constexpr Color paleGoldenrod() {return Color(238, 232, 170, 255);}
	static constexpr Color peru() {return Color(205, 133, 63, 255);}
	static constexpr Color mediumVioletRed() {return Color(199, 21, 133, 255);}
	static constexpr Color mediumSpringGreen() {return Color(0, 250, 154, 255);}
	static constexpr Color darkKhaki() {return Color(189, 183, 107, 255);}
	static constexpr Color salmon() {return Color(250, 128, 114, 255);}
	static constexpr Color darkCyan() {return Color(0, 139, 139, 255);}
	static constexpr Color darkBlue() {return Color(0, 0, 139, 255);}
	static constexpr Color darkSeaGreen() {return Color(143, 188, 143, 255);}
	static constexpr Color thistle() {return Color(216, 191, 216, 255);}
	static constexpr Color lightSlateGray() {return Color(119, 136, 153, 255);}
	static constexpr Color oldLace() {return Color(253, 245, 230, 255);}
	static constexpr Color orchid() {return Color(218, 112, 214, 255);}
	static constexpr Color burlyWood() {return Color(222, 184, 135, 255);}
	static constexpr Color lightSalmon() {return Color(255, 160, 122, 255);}


	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	uint8_t alpha = 1;
};

}

#endif
