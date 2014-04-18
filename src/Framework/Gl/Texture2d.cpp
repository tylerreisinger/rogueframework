#include "Framework/Gl/Texture2d.h"

#include "Framework/Exceptions/EnumerationValueException.h"
#include "Context.h"

namespace rf
{
namespace gl
{

Texture2d::Texture2d(int width, int height, int mipmapLevels, Context* context):
	m_width(width), m_height(height)
{
	m_context = context;

	glGenTextures(1, &m_handle);
	context->bindTexture(*this);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
}

Texture2d::Texture2d(Texture2d&& other) noexcept : Texture(std::move(other)),
	m_height(other.m_height), m_width(other.m_width)
{
}

Texture2d& Texture2d::operator =(Texture2d&& other) noexcept
{
	Texture::operator =(std::move(other));
	m_height = other.m_height;
	m_width = other.m_width;
	return *this;
}

Texture2d::~Texture2d()
{
	glDeleteTextures(1, &m_handle);
}

void Texture2d::setClampModes(ClampMode clampS, ClampMode clampT)
{
	m_context->bindTexture(*this);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(clampS));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(clampT));
}

void Texture2d::setFilterModes(FilterMode magnificationFilter,
		FilterMode minificationFilter)
{
	m_context->bindTexture(*this);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(minificationFilter));
	if(magnificationFilter != FilterMode::Linear && magnificationFilter != FilterMode::Nearest)
	{
		throw EnumerationValueException("FilterMode", "Texture magnification filter does not support mipmap functions");
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(magnificationFilter));
	}
}

void Texture2d::updateData(const Rectanglei& updateRegion,
		DataPixelFormat dataFormat, PixelType sourcePixelType, const void* data,
		int pixelAlignment)
{
	m_context->bindTexture(*this);
	glPixelStorei(GL_UNPACK_ALIGNMENT, pixelAlignment);

	glTexSubImage2D(GL_TEXTURE_2D, 0, updateRegion.left(), updateRegion.bottom(),
			updateRegion.width(), updateRegion.height(), static_cast<GLenum>(dataFormat),
			static_cast<GLenum>(sourcePixelType), data);
}

void Texture2d::generateMipmap()
{
	m_context->bindTexture(*this);

	glGenerateMipmap(GL_TEXTURE_2D);

}

void Texture2d::destroy()
{
	glDeleteTextures(1, &m_handle);
}

}
}