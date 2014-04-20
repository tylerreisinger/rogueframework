#ifndef TEXTUREARRAY2D_H_
#define TEXTUREARRAY2D_H_

#include "Framework/Gl/Texture.h"

#include "Framework/Rectangle.h"

namespace rf
{
namespace gl
{
class Context;

class TextureArray2d: public Texture
{
public:
	TextureArray2d(int width, int height, int layers, int mipmapLevels,
			InternalPixelFormat internalFormat, Context* context);
	virtual ~TextureArray2d();

	TextureArray2d(TextureArray2d&& other) noexcept;
	TextureArray2d& operator =(TextureArray2d&& other) noexcept;

	void setData(const Rectanglei& updateRegion, int startLayer, int layerCount, int mipmapLayer,
			DataPixelFormat dataFormat, PixelType sourcePixelType,
			const void* data);

	void setClampModes(ClampMode clampS, ClampMode clampT);

	/**
	 * @brief Set the functions used to scale the Texture image.
	 * @param magnificationFilter The filter mode used when the texture is enlarged.
	 * This may not be one of the mipmap filtering modes.
	 * @param minificationFilter The filter mode used when the texture is shunk.
	 * @throw EnumerationValueException An invalid mode was specified for the magnification filter.
	 */
	void setFilterModes(FilterMode magnificationFilter, FilterMode minificationFilter);

	///Return the width of the textures, in pixels.
	int width() const {return m_width;}
	///Return the height of the textures, in pixels.
	int height() const {return m_height;}
	///Return the number of layers in the array
	int layers() const {return m_layers;}

	///Generate mipmap images based on the base level image stored in the Texture.
	void generateMipmap();

protected:
	virtual void destroy() override;

	int m_width;
	int m_height;
	int m_layers;


};

}
}

#endif
