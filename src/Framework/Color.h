#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>
#include <cmath>

namespace rf
{

/**
 * @brief Represents a RGB color with floating point components between 0 and 1.
 */
class Color
{
public:

	constexpr Color();
	explicit constexpr Color(unsigned int color);
	constexpr Color(float red, float green, float blue);
	constexpr Color(float red, float green, float blue, float alpha);
	Color(const Color& color) = default;
	Color(Color&& color) = default;
	~Color() = default;

	Color& operator =(const Color& color) = default;
	Color& operator =(Color&& color) = default;

	bool operator ==(const Color& color) const;
	bool operator !=(const Color& color) const;

	inline uint8_t redByte() const {return red * 255 + 0.5;}
	inline uint8_t greenByte() const {return green * 255 + 0.5;}
	inline uint8_t blueByte() const {return blue * 255 + 0.5;}
	inline uint8_t alphaByte() const {return alpha * 255 + 0.5;}

	uint32_t toRGB() const;
	uint32_t toRGBA() const;
	uint32_t toABGR() const;

	uint32_t toRGBAEndianAware() const {return toABGR();}

	static Color alphaBlend(const Color& color1, const Color& color2);
	static Color fromByteChannels(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

	static constexpr Color darkRed() {return Color(0.5450980392156862f, 0.0f, 0.0f, 1.0f);}
	static constexpr Color lightGrey() {return Color(0.8274509803921568f, 0.8274509803921568f, 0.8274509803921568f, 1.0f);}
	static constexpr Color chocolate() {return Color(0.8235294117647058f, 0.4117647058823529f, 0.11764705882352941f, 1.0f);}
	static constexpr Color darkSlateGray() {return Color(0.1843137254901961f, 0.30980392156862746f, 0.30980392156862746f, 1.0f);}
	static constexpr Color olive() {return Color(0.5019607843137255f, 0.5019607843137255f, 0.0f, 1.0f);}
	static constexpr Color floralWhite() {return Color(1.0f, 0.9803921568627451f, 0.9411764705882353f, 1.0f);}
	static constexpr Color teal() {return Color(0.0f, 0.5019607843137255f, 0.5019607843137255f, 1.0f);}
	static constexpr Color turquoise() {return Color(0.25098039215686274f, 0.8784313725490196f, 0.8156862745098039f, 1.0f);}
	static constexpr Color darkGoldenrod() {return Color(0.7215686274509804f, 0.5254901960784314f, 0.043137254901960784f, 1.0f);}
	static constexpr Color limeGreen() {return Color(0.19607843137254902f, 0.803921568627451f, 0.19607843137254902f, 1.0f);}
	static constexpr Color slateBlue() {return Color(0.41568627450980394f, 0.35294117647058826f, 0.803921568627451f, 1.0f);}
	static constexpr Color blanchedAlmond() {return Color(1.0f, 0.9215686274509803f, 0.803921568627451f, 1.0f);}
	static constexpr Color darkSlateBlue() {return Color(0.2823529411764706f, 0.23921568627450981f, 0.5450980392156862f, 1.0f);}
	static constexpr Color pureGreen() {return Color(0.0f, 0.5019607843137255f, 0.0f, 1.0f);}
	static constexpr Color magenta() {return Color(1.0f, 0.0f, 1.0f, 1.0f);}
	static constexpr Color orange() {return Color(1.0f, 0.6470588235294118f, 0.0f, 1.0f);}
	static constexpr Color whiteSmoke() {return Color(0.9607843137254902f, 0.9607843137254902f, 0.9607843137254902f, 1.0f);}
	static constexpr Color greenYellow() {return Color(0.6784313725490196f, 1.0f, 0.1843137254901961f, 1.0f);}
	static constexpr Color gainsboro() {return Color(0.8627450980392157f, 0.8627450980392157f, 0.8627450980392157f, 1.0f);}
	static constexpr Color violet() {return Color(0.9333333333333333f, 0.5098039215686274f, 0.9333333333333333f, 1.0f);}
	static constexpr Color black() {return Color(0.0f, 0.0f, 0.0f, 1.0f);}
	static constexpr Color lavenderBlush() {return Color(1.0f, 0.9411764705882353f, 0.9607843137254902f, 1.0f);}
	static constexpr Color mediumBlue() {return Color(0.0f, 0.0f, 0.803921568627451f, 1.0f);}
	static constexpr Color linen() {return Color(0.9803921568627451f, 0.9411764705882353f, 0.9019607843137255f, 1.0f);}
	static constexpr Color mediumSeaGreen() {return Color(0.23529411764705882f, 0.7019607843137254f, 0.44313725490196076f, 1.0f);}
	static constexpr Color darkSalmon() {return Color(0.9137254901960784f, 0.5882352941176471f, 0.47843137254901963f, 1.0f);}
	static constexpr Color goldenrod() {return Color(0.8549019607843137f, 0.6470588235294118f, 0.12549019607843137f, 1.0f);}
	static constexpr Color powderBlue() {return Color(0.6901960784313725f, 0.8784313725490196f, 0.9019607843137255f, 1.0f);}
	static constexpr Color maroon() {return Color(0.5019607843137255f, 0.0f, 0.0f, 1.0f);}
	static constexpr Color darkOrange() {return Color(1.0f, 0.5490196078431373f, 0.0f, 1.0f);}
	static constexpr Color aliceBlue() {return Color(0.9411764705882353f, 0.9725490196078431f, 1.0f, 1.0f);}
	static constexpr Color darkTurquoise() {return Color(0.0f, 0.807843137254902f, 0.8196078431372549f, 1.0f);}
	static constexpr Color rosyBrown() {return Color(0.7372549019607844f, 0.5607843137254902f, 0.5607843137254902f, 1.0f);}
	static constexpr Color paleVioletRed() {return Color(0.8588235294117647f, 0.4392156862745098f, 0.5764705882352941f, 1.0f);}
	static constexpr Color darkMagenta() {return Color(0.5450980392156862f, 0.0f, 0.5450980392156862f, 1.0f);}
	static constexpr Color tomato() {return Color(1.0f, 0.38823529411764707f, 0.2784313725490196f, 1.0f);}
	static constexpr Color gray() {return Color(0.5019607843137255f, 0.5019607843137255f, 0.5019607843137255f, 1.0f);}
	static constexpr Color deepPink() {return Color(1.0f, 0.0784313725490196f, 0.5764705882352941f, 1.0f);}
	static constexpr Color midnightBlue() {return Color(0.09803921568627451f, 0.09803921568627451f, 0.4392156862745098f, 1.0f);}
	static constexpr Color lightCyan() {return Color(0.8784313725490196f, 1.0f, 1.0f, 1.0f);}
	static constexpr Color chartreuse() {return Color(0.4980392156862745f, 1.0f, 0.0f, 1.0f);}
	static constexpr Color darkOrchid() {return Color(0.6f, 0.19607843137254902f, 0.8f, 1.0f);}
	static constexpr Color oliveDrab() {return Color(0.4196078431372549f, 0.5568627450980392f, 0.13725490196078433f, 1.0f);}
	static constexpr Color pink() {return Color(1.0f, 0.7529411764705882f, 0.796078431372549f, 1.0f);}
	static constexpr Color navy() {return Color(0.0f, 0.0f, 0.5019607843137255f, 1.0f);}
	static constexpr Color paleTurquoise() {return Color(0.6862745098039216f, 0.9333333333333333f, 0.9333333333333333f, 1.0f);}
	static constexpr Color azure() {return Color(0.9411764705882353f, 1.0f, 1.0f, 1.0f);}
	static constexpr Color lightCoral() {return Color(0.9411764705882353f, 0.5019607843137255f, 0.5019607843137255f, 1.0f);}
	static constexpr Color lavender() {return Color(0.9019607843137255f, 0.9019607843137255f, 0.9803921568627451f, 1.0f);}
	static constexpr Color steelBlue() {return Color(0.27450980392156865f, 0.5098039215686274f, 0.7058823529411765f, 1.0f);}
	static constexpr Color beige() {return Color(0.9607843137254902f, 0.9607843137254902f, 0.8627450980392157f, 1.0f);}
	static constexpr Color orangeRed() {return Color(1.0f, 0.27058823529411763f, 0.0f, 1.0f);}
	static constexpr Color lightGoldenrodYellow() {return Color(0.9803921568627451f, 0.9803921568627451f, 0.8235294117647058f, 1.0f);}
	static constexpr Color ghostWhite() {return Color(0.9725490196078431f, 0.9725490196078431f, 1.0f, 1.0f);}
	static constexpr Color gold() {return Color(1.0f, 0.8431372549019608f, 0.0f, 1.0f);}
	static constexpr Color darkGreen() {return Color(0.0f, 0.39215686274509803f, 0.0f, 1.0f);}
	static constexpr Color bisque() {return Color(1.0f, 0.8941176470588236f, 0.7686274509803922f, 1.0f);}
	static constexpr Color pureRed() {return Color(1.0f, 0.0f, 0.0f, 1.0f);}
	static constexpr Color indigo() {return Color(0.29411764705882354f, 0.0f, 0.5098039215686274f, 1.0f);}
	static constexpr Color white() {return Color(1.0f, 1.0f, 1.0f, 1.0f);}
	static constexpr Color mediumSlateBlue() {return Color(0.4823529411764706f, 0.40784313725490196f, 0.9333333333333333f, 1.0f);}
	static constexpr Color seaGreen() {return Color(0.1803921568627451f, 0.5450980392156862f, 0.3411764705882353f, 1.0f);}
	static constexpr Color forestGreen() {return Color(0.13333333333333333f, 0.5450980392156862f, 0.13333333333333333f, 1.0f);}
	static constexpr Color cornflowerBlue() {return Color(0.39215686274509803f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);}
	static constexpr Color skyBlue() {return Color(0.5294117647058824f, 0.807843137254902f, 0.9215686274509803f, 1.0f);}
	static constexpr Color springGreen() {return Color(0.0f, 1.0f, 0.4980392156862745f, 1.0f);}
	static constexpr Color crimson() {return Color(0.8627450980392157f, 0.0784313725490196f, 0.23529411764705882f, 1.0f);}
	static constexpr Color silver() {return Color(0.7529411764705882f, 0.7529411764705882f, 0.7529411764705882f, 1.0f);}
	static constexpr Color blueViolet() {return Color(0.5411764705882353f, 0.16862745098039217f, 0.8862745098039215f, 1.0f);}
	static constexpr Color darkViolet() {return Color(0.5803921568627451f, 0.0f, 0.8274509803921568f, 1.0f);}
	static constexpr Color cyan() {return Color(0.0f, 1.0f, 1.0f, 1.0f);}
	static constexpr Color dimGray() {return Color(0.4117647058823529f, 0.4117647058823529f, 0.4117647058823529f, 1.0f);}
	static constexpr Color antiqueWhite() {return Color(0.9803921568627451f, 0.9215686274509803f, 0.8431372549019608f, 1.0f);}
	static constexpr Color pureBlue() {return Color(0.0f, 0.0f, 1.0f, 1.0f);}
	static constexpr Color plum() {return Color(0.8666666666666667f, 0.6274509803921569f, 0.8666666666666667f, 1.0f);}
	static constexpr Color navajoWhite() {return Color(1.0f, 0.8705882352941177f, 0.6784313725490196f, 1.0f);}
	static constexpr Color cadetBlue() {return Color(0.37254901960784315f, 0.6196078431372549f, 0.6274509803921569f, 1.0f);}
	static constexpr Color darkOliveGreen() {return Color(0.3333333333333333f, 0.4196078431372549f, 0.1843137254901961f, 1.0f);}
	static constexpr Color lightYellow() {return Color(1.0f, 1.0f, 0.8784313725490196f, 1.0f);}
	static constexpr Color brown() {return Color(0.6470588235294118f, 0.16470588235294117f, 0.16470588235294117f, 1.0f);}
	static constexpr Color lemonChiffon() {return Color(1.0f, 0.9803921568627451f, 0.803921568627451f, 1.0f);}
	static constexpr Color aquamarine() {return Color(0.4980392156862745f, 1.0f, 0.8313725490196079f, 1.0f);}
	static constexpr Color fireBrick() {return Color(0.6980392156862745f, 0.13333333333333333f, 0.13333333333333333f, 1.0f);}
	static constexpr Color mediumAquamarine() {return Color(0.4f, 0.803921568627451f, 0.6666666666666666f, 1.0f);}
	static constexpr Color mistyRose() {return Color(1.0f, 0.8941176470588236f, 0.8823529411764706f, 1.0f);}
	static constexpr Color ivory() {return Color(1.0f, 1.0f, 0.9411764705882353f, 1.0f);}
	static constexpr Color papayaWhip() {return Color(1.0f, 0.9372549019607843f, 0.8352941176470589f, 1.0f);}
	static constexpr Color paleGreen() {return Color(0.596078431372549f, 0.984313725490196f, 0.596078431372549f, 1.0f);}
	static constexpr Color hotPink() {return Color(1.0f, 0.4117647058823529f, 0.7058823529411765f, 1.0f);}
	static constexpr Color mediumPurple() {return Color(0.5764705882352941f, 0.4392156862745098f, 0.8588235294117647f, 1.0f);}
	static constexpr Color darkGray() {return Color(0.6627450980392157f, 0.6627450980392157f, 0.6627450980392157f, 1.0f);}
	static constexpr Color moccasin() {return Color(1.0f, 0.8941176470588236f, 0.7098039215686275f, 1.0f);}
	static constexpr Color saddleBrown() {return Color(0.5450980392156862f, 0.27058823529411763f, 0.07450980392156863f, 1.0f);}
	static constexpr Color sienna() {return Color(0.6274509803921569f, 0.3215686274509804f, 0.17647058823529413f, 1.0f);}
	static constexpr Color mintCream() {return Color(0.9607843137254902f, 1.0f, 0.9803921568627451f, 1.0f);}
	static constexpr Color lightGreen() {return Color(0.5647058823529412f, 0.9333333333333333f, 0.5647058823529412f, 1.0f);}
	static constexpr Color tan() {return Color(0.8235294117647058f, 0.7058823529411765f, 0.5490196078431373f, 1.0f);}
	static constexpr Color lightSkyBlue() {return Color(0.5294117647058824f, 0.807843137254902f, 0.9803921568627451f, 1.0f);}
	static constexpr Color lightPink() {return Color(1.0f, 0.7137254901960784f, 0.7568627450980392f, 1.0f);}
	static constexpr Color mediumTurquoise() {return Color(0.2823529411764706f, 0.8196078431372549f, 0.8f, 1.0f);}
	static constexpr Color lime() {return Color(0.0f, 1.0f, 0.0f, 1.0f);}
	static constexpr Color coral() {return Color(1.0f, 0.4980392156862745f, 0.3137254901960784f, 1.0f);}
	static constexpr Color cornsilk() {return Color(1.0f, 0.9725490196078431f, 0.8627450980392157f, 1.0f);}
	static constexpr Color aqua() {return Color(0.0f, 1.0f, 1.0f, 1.0f);}
	static constexpr Color honeydew() {return Color(0.9411764705882353f, 1.0f, 0.9411764705882353f, 1.0f);}
	static constexpr Color deepSkyBlue() {return Color(0.0f, 0.7490196078431373f, 1.0f, 1.0f);}
	static constexpr Color indianRed() {return Color(0.803921568627451f, 0.3607843137254902f, 0.3607843137254902f, 1.0f);}
	static constexpr Color purple() {return Color(0.5019607843137255f, 0.0f, 0.5019607843137255f, 1.0f);}
	static constexpr Color khaki() {return Color(0.9411764705882353f, 0.9019607843137255f, 0.5490196078431373f, 1.0f);}
	static constexpr Color wheat() {return Color(0.9607843137254902f, 0.8705882352941177f, 0.7019607843137254f, 1.0f);}
	static constexpr Color sandyBrown() {return Color(0.9568627450980393f, 0.6431372549019608f, 0.3764705882352941f, 1.0f);}
	static constexpr Color lawnGreen() {return Color(0.48627450980392156f, 0.9882352941176471f, 0.0f, 1.0f);}
	static constexpr Color lightSteelBlue() {return Color(0.6901960784313725f, 0.7686274509803922f, 0.8705882352941177f, 1.0f);}
	static constexpr Color yellow() {return Color(1.0f, 1.0f, 0.0f, 1.0f);}
	static constexpr Color peachPuff() {return Color(1.0f, 0.8549019607843137f, 0.7254901960784313f, 1.0f);}
	static constexpr Color mediumOrchid() {return Color(0.7294117647058823f, 0.3333333333333333f, 0.8274509803921568f, 1.0f);}
	static constexpr Color fuchsia() {return Color(1.0f, 0.0f, 1.0f, 1.0f);}
	static constexpr Color dodgerBlue() {return Color(0.11764705882352941f, 0.5647058823529412f, 1.0f, 1.0f);}
	static constexpr Color yellowGreen() {return Color(0.6039215686274509f, 0.803921568627451f, 0.19607843137254902f, 1.0f);}
	static constexpr Color lightBlue() {return Color(0.6784313725490196f, 0.8470588235294118f, 0.9019607843137255f, 1.0f);}
	static constexpr Color lightSeaGreen() {return Color(0.12549019607843137f, 0.6980392156862745f, 0.6666666666666666f, 1.0f);}
	static constexpr Color seashell() {return Color(1.0f, 0.9607843137254902f, 0.9333333333333333f, 1.0f);}
	static constexpr Color snow() {return Color(1.0f, 0.9803921568627451f, 0.9803921568627451f, 1.0f);}
	static constexpr Color royalBlue() {return Color(0.2549019607843137f, 0.4117647058823529f, 0.8823529411764706f, 1.0f);}
	static constexpr Color slateGray() {return Color(0.4392156862745098f, 0.5019607843137255f, 0.5647058823529412f, 1.0f);}
	static constexpr Color paleGoldenrod() {return Color(0.9333333333333333f, 0.9098039215686274f, 0.6666666666666666f, 1.0f);}
	static constexpr Color peru() {return Color(0.803921568627451f, 0.5215686274509804f, 0.24705882352941178f, 1.0f);}
	static constexpr Color mediumVioletRed() {return Color(0.7803921568627451f, 0.08235294117647059f, 0.5215686274509804f, 1.0f);}
	static constexpr Color mediumSpringGreen() {return Color(0.0f, 0.9803921568627451f, 0.6039215686274509f, 1.0f);}
	static constexpr Color darkKhaki() {return Color(0.7411764705882353f, 0.7176470588235294f, 0.4196078431372549f, 1.0f);}
	static constexpr Color salmon() {return Color(0.9803921568627451f, 0.5019607843137255f, 0.4470588235294118f, 1.0f);}
	static constexpr Color darkCyan() {return Color(0.0f, 0.5450980392156862f, 0.5450980392156862f, 1.0f);}
	static constexpr Color darkBlue() {return Color(0.0f, 0.0f, 0.5450980392156862f, 1.0f);}
	static constexpr Color darkSeaGreen() {return Color(0.5607843137254902f, 0.7372549019607844f, 0.5607843137254902f, 1.0f);}
	static constexpr Color thistle() {return Color(0.8470588235294118f, 0.7490196078431373f, 0.8470588235294118f, 1.0f);}
	static constexpr Color lightSlateGray() {return Color(0.4666666666666667f, 0.5333333333333333f, 0.6f, 1.0f);}
	static constexpr Color oldLace() {return Color(0.9921568627450981f, 0.9607843137254902f, 0.9019607843137255f, 1.0f);}
	static constexpr Color orchid() {return Color(0.8549019607843137f, 0.4392156862745098f, 0.8392156862745098f, 1.0f);}
	static constexpr Color burlyWood() {return Color(0.8705882352941177f, 0.7215686274509804f, 0.5294117647058824f, 1.0f);}
	static constexpr Color lightSalmon() {return Color(1.0f, 0.6274509803921569f, 0.47843137254901963f, 1.0f);}

	float red;
	float green;
	float blue;
	float alpha;
};

inline constexpr Color::Color():
	red(0.f), green(0.f), blue(0.f), alpha(0.f)
{

}

inline constexpr Color::Color(unsigned int color):
	red(((color & 0x00FF0000U) >> 16) / 255.f), green(((color & 0x0000FF00U) >> 8) / 255.f), blue(((color & 0x000000FFU)) / 255.f), alpha(((color & 0xFF000000U) >> 24) / 255.f)
{
}

inline constexpr Color::Color(float redValue, float greenValue, float blueValue):
	red(redValue), green(greenValue), blue(blueValue), alpha(1.0)
{

}

inline constexpr Color::Color(float redValue, float greenValue, float blueValue, float alphaValue):
	red(redValue), green(greenValue), blue(blueValue), alpha(alphaValue)
{

}

}

#endif /* COLOR_H_ */
