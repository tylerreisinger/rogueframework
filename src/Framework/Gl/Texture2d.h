#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include "Framework/Gl/Texture.h"

#include "Framework/Rectangle.h"

namespace rf
{
namespace gl
{

class Texture2d: public rf::gl::Texture
{
public:
	Texture2d(int width, int height, int mipmapLevels, Context* context);
	virtual ~Texture2d();

	/**
	 * @brief Replace part or all of the pixel data in the texture with new data.
	 * @details The buffer is not reallocated, so @a updateRegion must be entirely
	 * within the current image data of the Texture.
	 * @param updateRegion The rectangular region of pixels within the image to
	 * update.
	 * @param dataFormat The format of @a data provided to the function.
	 * @param sourcePixelType The type of pixel data in @a data.
	 * @param data The raw pixel data to be copied into the Texture's image.
	 * @param pixelAlignment The data alignment of the rows in @a data. Must be
	 * 1, 2, 4 or 8.
	 */
	void updateData(const Rectanglei& updateRegion, DataPixelFormat dataFormat,
			PixelType sourcePixelType, const void* data, int pixelAlignment = 4);

	void setClampModes(ClampMode clampS, ClampMode clampT);

	/**
	 * @brief Set the functions used to scale the Texture image.
	 * @param magnificationFilter The filter mode used when the texture is enlarged.
	 * This may not be one of the mipmap filtering modes.
	 * @param minificationFilter The filter mode used when the texture is shunk.
	 * @throw EnumerationValueException An invalid mode was specified for the magnification filter.
	 */
	void setFilterModes(FilterMode magnificationFilter, FilterMode minificationFilter);

	///Return the width of the texture, in pixels.
	int width() const {return m_width;}
	///Return the height of the texture, in pixels.
	int height() const {return m_height;}

	///Generate mipmap images based on the base level image stored in the Texture.
	void generateMipmap();

protected:
	virtual void destroy() override;

	int m_width;
	int m_height;
};

}
}

#endif
