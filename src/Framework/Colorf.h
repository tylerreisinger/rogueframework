#ifndef COLORF_H_
#define COLORF_H_

#include <cstdint>
#include <cmath>


namespace rf
{
class Color;
/**
 * @brief Represents a RGB color with floating point components between 0 and 1.
 */
class Colorf
{
public:

	constexpr Colorf();
	explicit constexpr Colorf(unsigned int color);
	constexpr Colorf(float red, float green, float blue);
	constexpr Colorf(float red, float green, float blue, float alpha);
	Colorf(const Color& color);
	Colorf(const Colorf& color) = default;
	Colorf(Colorf&& color) = default;
	~Colorf() = default;

	Colorf& operator =(const Colorf& color) = default;
	Colorf& operator =(Colorf&& color) = default;

	bool operator ==(const Colorf& color) const;
	bool operator !=(const Colorf& color) const;

	inline uint8_t redByte() const {return red * 255 + 0.5;}
	inline uint8_t greenByte() const {return green * 255 + 0.5;}
	inline uint8_t blueByte() const {return blue * 255 + 0.5;}
	inline uint8_t alphaByte() const {return alpha * 255 + 0.5;}

	uint32_t toRgb() const;
	uint32_t toRgba() const;
	uint32_t toAbgr() const;

	uint32_t toRGBAEndianAware() const {return toAbgr();}

	static Colorf alphaBlend(const Colorf& color1, const Colorf& color2);
	static Colorf fromByteChannels(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

	static constexpr Colorf darkRed() {return Colorf(0.5450980392156862f, 0.0f, 0.0f, 1.0f);}
	static constexpr Colorf lightGrey() {return Colorf(0.8274509803921568f, 0.8274509803921568f, 0.8274509803921568f, 1.0f);}
	static constexpr Colorf chocolate() {return Colorf(0.8235294117647058f, 0.4117647058823529f, 0.11764705882352941f, 1.0f);}
	static constexpr Colorf darkSlateGray() {return Colorf(0.1843137254901961f, 0.30980392156862746f, 0.30980392156862746f, 1.0f);}
	static constexpr Colorf olive() {return Colorf(0.5019607843137255f, 0.5019607843137255f, 0.0f, 1.0f);}
	static constexpr Colorf floralWhite() {return Colorf(1.0f, 0.9803921568627451f, 0.9411764705882353f, 1.0f);}
	static constexpr Colorf teal() {return Colorf(0.0f, 0.5019607843137255f, 0.5019607843137255f, 1.0f);}
	static constexpr Colorf turquoise() {return Colorf(0.25098039215686274f, 0.8784313725490196f, 0.8156862745098039f, 1.0f);}
	static constexpr Colorf darkGoldenrod() {return Colorf(0.7215686274509804f, 0.5254901960784314f, 0.043137254901960784f, 1.0f);}
	static constexpr Colorf limeGreen() {return Colorf(0.19607843137254902f, 0.803921568627451f, 0.19607843137254902f, 1.0f);}
	static constexpr Colorf slateBlue() {return Colorf(0.41568627450980394f, 0.35294117647058826f, 0.803921568627451f, 1.0f);}
	static constexpr Colorf blanchedAlmond() {return Colorf(1.0f, 0.9215686274509803f, 0.803921568627451f, 1.0f);}
	static constexpr Colorf darkSlateBlue() {return Colorf(0.2823529411764706f, 0.23921568627450981f, 0.5450980392156862f, 1.0f);}
	static constexpr Colorf pureGreen() {return Colorf(0.0f, 0.5019607843137255f, 0.0f, 1.0f);}
	static constexpr Colorf magenta() {return Colorf(1.0f, 0.0f, 1.0f, 1.0f);}
	static constexpr Colorf orange() {return Colorf(1.0f, 0.6470588235294118f, 0.0f, 1.0f);}
	static constexpr Colorf whiteSmoke() {return Colorf(0.9607843137254902f, 0.9607843137254902f, 0.9607843137254902f, 1.0f);}
	static constexpr Colorf greenYellow() {return Colorf(0.6784313725490196f, 1.0f, 0.1843137254901961f, 1.0f);}
	static constexpr Colorf gainsboro() {return Colorf(0.8627450980392157f, 0.8627450980392157f, 0.8627450980392157f, 1.0f);}
	static constexpr Colorf violet() {return Colorf(0.9333333333333333f, 0.5098039215686274f, 0.9333333333333333f, 1.0f);}
	static constexpr Colorf black() {return Colorf(0.0f, 0.0f, 0.0f, 1.0f);}
	static constexpr Colorf lavenderBlush() {return Colorf(1.0f, 0.9411764705882353f, 0.9607843137254902f, 1.0f);}
	static constexpr Colorf mediumBlue() {return Colorf(0.0f, 0.0f, 0.803921568627451f, 1.0f);}
	static constexpr Colorf linen() {return Colorf(0.9803921568627451f, 0.9411764705882353f, 0.9019607843137255f, 1.0f);}
	static constexpr Colorf mediumSeaGreen() {return Colorf(0.23529411764705882f, 0.7019607843137254f, 0.44313725490196076f, 1.0f);}
	static constexpr Colorf darkSalmon() {return Colorf(0.9137254901960784f, 0.5882352941176471f, 0.47843137254901963f, 1.0f);}
	static constexpr Colorf goldenrod() {return Colorf(0.8549019607843137f, 0.6470588235294118f, 0.12549019607843137f, 1.0f);}
	static constexpr Colorf powderBlue() {return Colorf(0.6901960784313725f, 0.8784313725490196f, 0.9019607843137255f, 1.0f);}
	static constexpr Colorf maroon() {return Colorf(0.5019607843137255f, 0.0f, 0.0f, 1.0f);}
	static constexpr Colorf darkOrange() {return Colorf(1.0f, 0.5490196078431373f, 0.0f, 1.0f);}
	static constexpr Colorf aliceBlue() {return Colorf(0.9411764705882353f, 0.9725490196078431f, 1.0f, 1.0f);}
	static constexpr Colorf darkTurquoise() {return Colorf(0.0f, 0.807843137254902f, 0.8196078431372549f, 1.0f);}
	static constexpr Colorf rosyBrown() {return Colorf(0.7372549019607844f, 0.5607843137254902f, 0.5607843137254902f, 1.0f);}
	static constexpr Colorf paleVioletRed() {return Colorf(0.8588235294117647f, 0.4392156862745098f, 0.5764705882352941f, 1.0f);}
	static constexpr Colorf darkMagenta() {return Colorf(0.5450980392156862f, 0.0f, 0.5450980392156862f, 1.0f);}
	static constexpr Colorf tomato() {return Colorf(1.0f, 0.38823529411764707f, 0.2784313725490196f, 1.0f);}
	static constexpr Colorf gray() {return Colorf(0.5019607843137255f, 0.5019607843137255f, 0.5019607843137255f, 1.0f);}
	static constexpr Colorf deepPink() {return Colorf(1.0f, 0.0784313725490196f, 0.5764705882352941f, 1.0f);}
	static constexpr Colorf midnightBlue() {return Colorf(0.09803921568627451f, 0.09803921568627451f, 0.4392156862745098f, 1.0f);}
	static constexpr Colorf lightCyan() {return Colorf(0.8784313725490196f, 1.0f, 1.0f, 1.0f);}
	static constexpr Colorf chartreuse() {return Colorf(0.4980392156862745f, 1.0f, 0.0f, 1.0f);}
	static constexpr Colorf darkOrchid() {return Colorf(0.6f, 0.19607843137254902f, 0.8f, 1.0f);}
	static constexpr Colorf oliveDrab() {return Colorf(0.4196078431372549f, 0.5568627450980392f, 0.13725490196078433f, 1.0f);}
	static constexpr Colorf pink() {return Colorf(1.0f, 0.7529411764705882f, 0.796078431372549f, 1.0f);}
	static constexpr Colorf navy() {return Colorf(0.0f, 0.0f, 0.5019607843137255f, 1.0f);}
	static constexpr Colorf paleTurquoise() {return Colorf(0.6862745098039216f, 0.9333333333333333f, 0.9333333333333333f, 1.0f);}
	static constexpr Colorf azure() {return Colorf(0.9411764705882353f, 1.0f, 1.0f, 1.0f);}
	static constexpr Colorf lightCoral() {return Colorf(0.9411764705882353f, 0.5019607843137255f, 0.5019607843137255f, 1.0f);}
	static constexpr Colorf lavender() {return Colorf(0.9019607843137255f, 0.9019607843137255f, 0.9803921568627451f, 1.0f);}
	static constexpr Colorf steelBlue() {return Colorf(0.27450980392156865f, 0.5098039215686274f, 0.7058823529411765f, 1.0f);}
	static constexpr Colorf beige() {return Colorf(0.9607843137254902f, 0.9607843137254902f, 0.8627450980392157f, 1.0f);}
	static constexpr Colorf orangeRed() {return Colorf(1.0f, 0.27058823529411763f, 0.0f, 1.0f);}
	static constexpr Colorf lightGoldenrodYellow() {return Colorf(0.9803921568627451f, 0.9803921568627451f, 0.8235294117647058f, 1.0f);}
	static constexpr Colorf ghostWhite() {return Colorf(0.9725490196078431f, 0.9725490196078431f, 1.0f, 1.0f);}
	static constexpr Colorf gold() {return Colorf(1.0f, 0.8431372549019608f, 0.0f, 1.0f);}
	static constexpr Colorf darkGreen() {return Colorf(0.0f, 0.39215686274509803f, 0.0f, 1.0f);}
	static constexpr Colorf bisque() {return Colorf(1.0f, 0.8941176470588236f, 0.7686274509803922f, 1.0f);}
	static constexpr Colorf pureRed() {return Colorf(1.0f, 0.0f, 0.0f, 1.0f);}
	static constexpr Colorf indigo() {return Colorf(0.29411764705882354f, 0.0f, 0.5098039215686274f, 1.0f);}
	static constexpr Colorf white() {return Colorf(1.0f, 1.0f, 1.0f, 1.0f);}
	static constexpr Colorf mediumSlateBlue() {return Colorf(0.4823529411764706f, 0.40784313725490196f, 0.9333333333333333f, 1.0f);}
	static constexpr Colorf seaGreen() {return Colorf(0.1803921568627451f, 0.5450980392156862f, 0.3411764705882353f, 1.0f);}
	static constexpr Colorf forestGreen() {return Colorf(0.13333333333333333f, 0.5450980392156862f, 0.13333333333333333f, 1.0f);}
	static constexpr Colorf cornflowerBlue() {return Colorf(0.39215686274509803f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);}
	static constexpr Colorf skyBlue() {return Colorf(0.5294117647058824f, 0.807843137254902f, 0.9215686274509803f, 1.0f);}
	static constexpr Colorf springGreen() {return Colorf(0.0f, 1.0f, 0.4980392156862745f, 1.0f);}
	static constexpr Colorf crimson() {return Colorf(0.8627450980392157f, 0.0784313725490196f, 0.23529411764705882f, 1.0f);}
	static constexpr Colorf silver() {return Colorf(0.7529411764705882f, 0.7529411764705882f, 0.7529411764705882f, 1.0f);}
	static constexpr Colorf blueViolet() {return Colorf(0.5411764705882353f, 0.16862745098039217f, 0.8862745098039215f, 1.0f);}
	static constexpr Colorf darkViolet() {return Colorf(0.5803921568627451f, 0.0f, 0.8274509803921568f, 1.0f);}
	static constexpr Colorf cyan() {return Colorf(0.0f, 1.0f, 1.0f, 1.0f);}
	static constexpr Colorf dimGray() {return Colorf(0.4117647058823529f, 0.4117647058823529f, 0.4117647058823529f, 1.0f);}
	static constexpr Colorf antiqueWhite() {return Colorf(0.9803921568627451f, 0.9215686274509803f, 0.8431372549019608f, 1.0f);}
	static constexpr Colorf pureBlue() {return Colorf(0.0f, 0.0f, 1.0f, 1.0f);}
	static constexpr Colorf plum() {return Colorf(0.8666666666666667f, 0.6274509803921569f, 0.8666666666666667f, 1.0f);}
	static constexpr Colorf navajoWhite() {return Colorf(1.0f, 0.8705882352941177f, 0.6784313725490196f, 1.0f);}
	static constexpr Colorf cadetBlue() {return Colorf(0.37254901960784315f, 0.6196078431372549f, 0.6274509803921569f, 1.0f);}
	static constexpr Colorf darkOliveGreen() {return Colorf(0.3333333333333333f, 0.4196078431372549f, 0.1843137254901961f, 1.0f);}
	static constexpr Colorf lightYellow() {return Colorf(1.0f, 1.0f, 0.8784313725490196f, 1.0f);}
	static constexpr Colorf brown() {return Colorf(0.6470588235294118f, 0.16470588235294117f, 0.16470588235294117f, 1.0f);}
	static constexpr Colorf lemonChiffon() {return Colorf(1.0f, 0.9803921568627451f, 0.803921568627451f, 1.0f);}
	static constexpr Colorf aquamarine() {return Colorf(0.4980392156862745f, 1.0f, 0.8313725490196079f, 1.0f);}
	static constexpr Colorf fireBrick() {return Colorf(0.6980392156862745f, 0.13333333333333333f, 0.13333333333333333f, 1.0f);}
	static constexpr Colorf mediumAquamarine() {return Colorf(0.4f, 0.803921568627451f, 0.6666666666666666f, 1.0f);}
	static constexpr Colorf mistyRose() {return Colorf(1.0f, 0.8941176470588236f, 0.8823529411764706f, 1.0f);}
	static constexpr Colorf ivory() {return Colorf(1.0f, 1.0f, 0.9411764705882353f, 1.0f);}
	static constexpr Colorf papayaWhip() {return Colorf(1.0f, 0.9372549019607843f, 0.8352941176470589f, 1.0f);}
	static constexpr Colorf paleGreen() {return Colorf(0.596078431372549f, 0.984313725490196f, 0.596078431372549f, 1.0f);}
	static constexpr Colorf hotPink() {return Colorf(1.0f, 0.4117647058823529f, 0.7058823529411765f, 1.0f);}
	static constexpr Colorf mediumPurple() {return Colorf(0.5764705882352941f, 0.4392156862745098f, 0.8588235294117647f, 1.0f);}
	static constexpr Colorf darkGray() {return Colorf(0.6627450980392157f, 0.6627450980392157f, 0.6627450980392157f, 1.0f);}
	static constexpr Colorf moccasin() {return Colorf(1.0f, 0.8941176470588236f, 0.7098039215686275f, 1.0f);}
	static constexpr Colorf saddleBrown() {return Colorf(0.5450980392156862f, 0.27058823529411763f, 0.07450980392156863f, 1.0f);}
	static constexpr Colorf sienna() {return Colorf(0.6274509803921569f, 0.3215686274509804f, 0.17647058823529413f, 1.0f);}
	static constexpr Colorf mintCream() {return Colorf(0.9607843137254902f, 1.0f, 0.9803921568627451f, 1.0f);}
	static constexpr Colorf lightGreen() {return Colorf(0.5647058823529412f, 0.9333333333333333f, 0.5647058823529412f, 1.0f);}
	static constexpr Colorf tan() {return Colorf(0.8235294117647058f, 0.7058823529411765f, 0.5490196078431373f, 1.0f);}
	static constexpr Colorf lightSkyBlue() {return Colorf(0.5294117647058824f, 0.807843137254902f, 0.9803921568627451f, 1.0f);}
	static constexpr Colorf lightPink() {return Colorf(1.0f, 0.7137254901960784f, 0.7568627450980392f, 1.0f);}
	static constexpr Colorf mediumTurquoise() {return Colorf(0.2823529411764706f, 0.8196078431372549f, 0.8f, 1.0f);}
	static constexpr Colorf lime() {return Colorf(0.0f, 1.0f, 0.0f, 1.0f);}
	static constexpr Colorf coral() {return Colorf(1.0f, 0.4980392156862745f, 0.3137254901960784f, 1.0f);}
	static constexpr Colorf cornsilk() {return Colorf(1.0f, 0.9725490196078431f, 0.8627450980392157f, 1.0f);}
	static constexpr Colorf aqua() {return Colorf(0.0f, 1.0f, 1.0f, 1.0f);}
	static constexpr Colorf honeydew() {return Colorf(0.9411764705882353f, 1.0f, 0.9411764705882353f, 1.0f);}
	static constexpr Colorf deepSkyBlue() {return Colorf(0.0f, 0.7490196078431373f, 1.0f, 1.0f);}
	static constexpr Colorf indianRed() {return Colorf(0.803921568627451f, 0.3607843137254902f, 0.3607843137254902f, 1.0f);}
	static constexpr Colorf purple() {return Colorf(0.5019607843137255f, 0.0f, 0.5019607843137255f, 1.0f);}
	static constexpr Colorf khaki() {return Colorf(0.9411764705882353f, 0.9019607843137255f, 0.5490196078431373f, 1.0f);}
	static constexpr Colorf wheat() {return Colorf(0.9607843137254902f, 0.8705882352941177f, 0.7019607843137254f, 1.0f);}
	static constexpr Colorf sandyBrown() {return Colorf(0.9568627450980393f, 0.6431372549019608f, 0.3764705882352941f, 1.0f);}
	static constexpr Colorf lawnGreen() {return Colorf(0.48627450980392156f, 0.9882352941176471f, 0.0f, 1.0f);}
	static constexpr Colorf lightSteelBlue() {return Colorf(0.6901960784313725f, 0.7686274509803922f, 0.8705882352941177f, 1.0f);}
	static constexpr Colorf yellow() {return Colorf(1.0f, 1.0f, 0.0f, 1.0f);}
	static constexpr Colorf peachPuff() {return Colorf(1.0f, 0.8549019607843137f, 0.7254901960784313f, 1.0f);}
	static constexpr Colorf mediumOrchid() {return Colorf(0.7294117647058823f, 0.3333333333333333f, 0.8274509803921568f, 1.0f);}
	static constexpr Colorf fuchsia() {return Colorf(1.0f, 0.0f, 1.0f, 1.0f);}
	static constexpr Colorf dodgerBlue() {return Colorf(0.11764705882352941f, 0.5647058823529412f, 1.0f, 1.0f);}
	static constexpr Colorf yellowGreen() {return Colorf(0.6039215686274509f, 0.803921568627451f, 0.19607843137254902f, 1.0f);}
	static constexpr Colorf lightBlue() {return Colorf(0.6784313725490196f, 0.8470588235294118f, 0.9019607843137255f, 1.0f);}
	static constexpr Colorf lightSeaGreen() {return Colorf(0.12549019607843137f, 0.6980392156862745f, 0.6666666666666666f, 1.0f);}
	static constexpr Colorf seashell() {return Colorf(1.0f, 0.9607843137254902f, 0.9333333333333333f, 1.0f);}
	static constexpr Colorf snow() {return Colorf(1.0f, 0.9803921568627451f, 0.9803921568627451f, 1.0f);}
	static constexpr Colorf royalBlue() {return Colorf(0.2549019607843137f, 0.4117647058823529f, 0.8823529411764706f, 1.0f);}
	static constexpr Colorf slateGray() {return Colorf(0.4392156862745098f, 0.5019607843137255f, 0.5647058823529412f, 1.0f);}
	static constexpr Colorf paleGoldenrod() {return Colorf(0.9333333333333333f, 0.9098039215686274f, 0.6666666666666666f, 1.0f);}
	static constexpr Colorf peru() {return Colorf(0.803921568627451f, 0.5215686274509804f, 0.24705882352941178f, 1.0f);}
	static constexpr Colorf mediumVioletRed() {return Colorf(0.7803921568627451f, 0.08235294117647059f, 0.5215686274509804f, 1.0f);}
	static constexpr Colorf mediumSpringGreen() {return Colorf(0.0f, 0.9803921568627451f, 0.6039215686274509f, 1.0f);}
	static constexpr Colorf darkKhaki() {return Colorf(0.7411764705882353f, 0.7176470588235294f, 0.4196078431372549f, 1.0f);}
	static constexpr Colorf salmon() {return Colorf(0.9803921568627451f, 0.5019607843137255f, 0.4470588235294118f, 1.0f);}
	static constexpr Colorf darkCyan() {return Colorf(0.0f, 0.5450980392156862f, 0.5450980392156862f, 1.0f);}
	static constexpr Colorf darkBlue() {return Colorf(0.0f, 0.0f, 0.5450980392156862f, 1.0f);}
	static constexpr Colorf darkSeaGreen() {return Colorf(0.5607843137254902f, 0.7372549019607844f, 0.5607843137254902f, 1.0f);}
	static constexpr Colorf thistle() {return Colorf(0.8470588235294118f, 0.7490196078431373f, 0.8470588235294118f, 1.0f);}
	static constexpr Colorf lightSlateGray() {return Colorf(0.4666666666666667f, 0.5333333333333333f, 0.6f, 1.0f);}
	static constexpr Colorf oldLace() {return Colorf(0.9921568627450981f, 0.9607843137254902f, 0.9019607843137255f, 1.0f);}
	static constexpr Colorf orchid() {return Colorf(0.8549019607843137f, 0.4392156862745098f, 0.8392156862745098f, 1.0f);}
	static constexpr Colorf burlyWood() {return Colorf(0.8705882352941177f, 0.7215686274509804f, 0.5294117647058824f, 1.0f);}
	static constexpr Colorf lightSalmon() {return Colorf(1.0f, 0.6274509803921569f, 0.47843137254901963f, 1.0f);}

	float red;
	float green;
	float blue;
	float alpha;
};

inline constexpr Colorf::Colorf():
	red(0.f), green(0.f), blue(0.f), alpha(0.f)
{

}

inline constexpr Colorf::Colorf(unsigned int color):
	red(((color & 0x00FF0000U) >> 16) / 255.f), green(((color & 0x0000FF00U) >> 8) / 255.f), blue(((color & 0x000000FFU)) / 255.f), alpha(((color & 0xFF000000U) >> 24) / 255.f)
{
}

inline constexpr Colorf::Colorf(float redValue, float greenValue, float blueValue):
	red(redValue), green(greenValue), blue(blueValue), alpha(1.0)
{

}

inline constexpr Colorf::Colorf(float redValue, float greenValue, float blueValue, float alphaValue):
	red(redValue), green(greenValue), blue(blueValue), alpha(alphaValue)
{

}



}

#endif /* COLOR_H_ */
