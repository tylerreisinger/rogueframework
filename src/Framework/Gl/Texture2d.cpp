#include "Framework/Gl/Texture2d.h"

#include "Framework/Exceptions/EnumerationValueException.h"
#include "Framework/Exceptions/GlException.h"
#include "Context.h"

namespace rf
{
namespace gl
{

Texture2d::Texture2d(int width, int height, int mipmapLevels,
		InternalPixelFormat internalFormat, Context* context):
	m_width(width), m_height(height)
{
	m_context = context;

	glGenTextures(1, &m_handle);
	CHECK_GL_ERROR(glGenTextures);
	context->bindTexture(*this);

	initializeParams();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels);
	CHECK_GL_ERROR(glTexParameteri);

#if GL_TARGET_VERSION >= 402
	//Use immutable storage if available
	glTexStorage2D(GL_TEXTURE_2D, mipmapLevels, static_cast<GLenum>(internalFormat),
			width, height);
	CHECK_GL_ERROR(glTexStorage2D);
#else
	int levelWidth = width;
	int levelHeight = height;
	for(int i = 0; i < mipmapLevels; ++i)
	{
		glTexImage2D(GL_TEXTURE_2D, i, static_cast<GLenum>(internalFormat), levelWidth, levelHeight, 0,
				GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, nullptr);
		CHECK_GL_ERROR(glTexImage2D);
		if(levelWidth == 1 && levelHeight == 1)
		{
			break;
		}
		levelWidth = std::max(1, levelWidth / 2);
		levelHeight = std::max(1, levelWidth / 2);
	}

#endif
}

Texture2d::Texture2d(Texture2d&& other) noexcept : Texture(std::move(other)),
	m_height(other.m_height), m_width(other.m_width)
{
}

Texture2d& Texture2d::operator =(Texture2d&& other) noexcept
{
	if(&other != this)
	{
		Texture::operator =(std::move(other));
		m_height = other.m_height;
		m_width = other.m_width;
	}
	return *this;
}

Texture2d::~Texture2d()
{
	destroy();
}

void Texture2d::setClampModes(ClampMode clampS, ClampMode clampT)
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(clampS));
	CHECK_GL_ERROR(glTexParameterf);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(clampT));
	CHECK_GL_ERROR(glTexParameterf);
}

void Texture2d::setFilterModes(FilterMode magnificationFilter,
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

void Texture2d::updateData(const Rectanglei& updateRegion,
		DataPixelFormat dataFormat, PixelType sourcePixelType, const void* data)
{
	glTexSubImage2D(GL_TEXTURE_2D, 0, updateRegion.left(), updateRegion.bottom(),
			updateRegion.width(), updateRegion.height(), static_cast<GLenum>(dataFormat),
			static_cast<GLenum>(sourcePixelType), data);
	CHECK_GL_ERROR(glTexSubImage2D);
}

void Texture2d::generateMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
	CHECK_GL_ERROR(glGenerateMipmap);
}

void Texture2d::bind() const
{
	m_context->bindTexture(*this);
}

void Texture2d::destroy()
{
	if(m_handle != 0)
	{
		glDeleteTextures(1, &m_handle);
	}
}

void Texture2d::initializeParams()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	CHECK_GL_ERROR(glTexParameteri);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	CHECK_GL_ERROR(glTexParameteri);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	CHECK_GL_ERROR(glTexParameteri);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	CHECK_GL_ERROR(glTexParameteri);
}

}
}
