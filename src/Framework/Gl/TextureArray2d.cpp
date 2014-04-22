#include "Framework/Gl/TextureArray2d.h"

#include "Framework/Gl/Context.h"
#include "Framework/Exceptions/GlException.h"
#include "Framework/Exceptions/EnumerationValueException.h"

namespace rf
{
namespace gl
{

TextureArray2d::TextureArray2d(int width, int height, int layers, int mipmapLevels,
		InternalPixelFormat internalFormat, Context* context):
	m_width(width), m_height(height), m_layers(layers)
{
	m_context = context;

	glGenTextures(1, &m_handle);
	CHECK_GL_ERROR(glGenTextures);

	context->bindTexture(*this);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, mipmapLevels);
	CHECK_GL_ERROR(glTexParameteri);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	CHECK_GL_ERROR(glTexParameteri);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	CHECK_GL_ERROR(glTexParameteri);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	CHECK_GL_ERROR(glTexParameteri);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	CHECK_GL_ERROR(glTexParameteri);

#if GL_TARGET_VERSION >= 402
	//Use immutable storage if available
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipmapLevels, static_cast<GLenum>(internalFormat),
			width, height, layers);
	CHECK_GL_ERROR(glTexStorage3D);
#else
	int levelWidth = width;
	int levelHeight = height;
	for(int i = 0; i < mipmapLevels; ++i)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, i, static_cast<GLenum>(internalFormat), levelWidth, levelHeight, layers, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		CHECK_GL_ERROR(glTexImage3D);
		if(levelWidth == 1 && levelHeight == 1)
		{
			break;
		}
		levelWidth = std::max(1, levelWidth / 2);
		levelHeight = std::max(1, levelWidth / 2);
	}

#endif

}

TextureArray2d::~TextureArray2d()
{
	destroy();
}

TextureArray2d::TextureArray2d(TextureArray2d&& other) noexcept : Texture(std::move(other)),
	m_height(other.m_height), m_width(other.m_width), m_layers(other.m_layers)
{
}

TextureArray2d& TextureArray2d::operator =(TextureArray2d&& other) noexcept
{
	if(&other != this)
	{
		Texture::operator =(std::move(other));
		m_height = other.m_height;
		m_width = other.m_width;
		m_layers = other.m_layers;
	}
	return *this;
}

void TextureArray2d::setClampModes(ClampMode clampS, ClampMode clampT)
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(clampS));
	CHECK_GL_ERROR(glTexParameterf);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(clampT));
	CHECK_GL_ERROR(glTexParameterf);
}

void TextureArray2d::setFilterModes(FilterMode magnificationFilter,
		FilterMode minificationFilter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(minificationFilter));
	CHECK_GL_ERROR(glTexParameteri);
	if(magnificationFilter != FilterMode::Linear && magnificationFilter != FilterMode::Nearest)
	{
		throw EnumerationValueException("FilterMode", "Texture magnification filter does not support mipmap functions");
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(magnificationFilter));
		CHECK_GL_ERROR(glTexParameteri);
	}
}

void TextureArray2d::setData(const Rectanglei& updateRegion, int startLayer,
		int layerCount, int mipmapLayer, DataPixelFormat dataFormat, PixelType sourcePixelType,
		const void* data)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, mipmapLayer, updateRegion.left(), updateRegion.bottom(),
			startLayer, updateRegion.width(), updateRegion.height(), layerCount,
			static_cast<GLenum>(dataFormat), static_cast<GLenum>(sourcePixelType),
			data);
	CHECK_GL_ERROR(glTexImage3D);
}

void TextureArray2d::generateMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
	CHECK_GL_ERROR(glGenerateMipmap);
}

void TextureArray2d::bind() const
{
	m_context->bindTexture(*this);
}

void TextureArray2d::destroy()
{
	if(m_handle != 0)
	{
		glDeleteTextures(1, &m_handle);
	}
}

}
}


