#include "Framework/FontManager.h"

#include <fstream>

#include "Framework/Exceptions/FileIoException.h"
#include "Framework/FontFace.h"

namespace rf
{

FontManager::FontManager()
{
	FT_Init_FreeType(&m_library);
}

FontManager::~FontManager()
{
	if(m_library)
	{
		FT_Done_FreeType(m_library);
	}
}

FontManager::FontManager(FontManager&& other) noexcept:
	m_library(other.m_library), m_defaultLoadFlags(other.m_defaultLoadFlags),
	m_faces(std::move(other.m_faces)), m_fontData(std::move(other.m_fontData))
{
	other.m_library = nullptr;
}

FontManager& FontManager::operator =(FontManager&& other) noexcept
{
	if(&other != this)
	{
		if(m_library)
		{
			FT_Done_FreeType(m_library);
		}
		m_library = other.m_library;
		m_defaultLoadFlags = other.m_defaultLoadFlags;
		m_faces = std::move(other.m_faces);
		m_fontData = std::move(other.m_fontData);
		other.m_library = nullptr;
	}
	return *this;
}

FontFace FontManager::createFontFace(const std::string& name, int sizeX, int sizeY)
{
	auto fontData = getFontData(name);
	return FontFace(this, fontData, sizeX, sizeY);
}

std::shared_ptr<const FontFace> FontManager::getFontFace(const std::string& name, int sizeX, int sizeY)
{
	std::shared_ptr<const FontFace> fontFace;
	auto it = m_faces.find(std::make_tuple(name, sizeX, sizeY));

	if(it != m_faces.end())
	{
		fontFace = it->second.lock();
	}

	if(!fontFace)
	{
		auto fontData = getFontData(name);
		fontFace = std::shared_ptr<const FontFace>(new FontFace(this, fontData, sizeX, sizeY, 0, m_defaultLoadFlags));
		if(it != m_faces.end())
		{
			it->second = std::weak_ptr<const FontFace>(fontFace);
		}
		else
		{
			m_faces.emplace(std::make_tuple(name, sizeX, sizeY), std::weak_ptr<const FontFace>(fontFace));
		}
	}

	return fontFace;
}

std::shared_ptr<std::vector<unsigned char>> FontManager::getFontData(
		const std::string& fileName)
{
	std::shared_ptr<std::vector<unsigned char>> outPtr;
	auto it = m_fontData.find(fileName);
	//The font data is currently in the vector, check if it is still valid and grab it if it is.
	if(it != m_fontData.end())
	{
		outPtr = it->second.lock();
	}
	//The font data needs reloaded.
	if(!outPtr)
	{
		outPtr = loadFontFile(fileName);
		if(it != m_fontData.end())
		{
			it->second = std::weak_ptr<std::vector<unsigned char>>(outPtr);
		}
		else
		{
			m_fontData.emplace(fileName, std::weak_ptr<std::vector<unsigned char>>(outPtr));
		}
	}

	return outPtr;
}

std::shared_ptr<std::vector<unsigned char>> FontManager::loadFontFile(
		const std::string& fileName) const
{
	std::vector<unsigned char> data;

	std::ifstream fontFile(fileName, std::ios::binary | std::ios::in | std::ios::ate);

	if(!fontFile.is_open())
	{
		throw FileIoException(fileName, "Unable to open file");
	}
	size_t fileSize = fontFile.tellg();
	//Don't use std::make_shared here so the file data can be deallocated when the
	//reference count drops to 0, even if there are std::weak_ptrs still referring to the data.
	std::shared_ptr<std::vector<unsigned char>> fileData(new std::vector<unsigned char>(fileSize));
	fontFile.seekg(0, std::ios::beg);
	fontFile.read(reinterpret_cast<char*>(fileData->data()), fileSize);
	fontFile.close();
	return fileData;
}

void FontManager::clearCache()
{
	m_fontData.clear();
	m_faces.clear();
}

void FontManager::setDefaultGlyphLoadFlags(const Flags<FontFace::GlyphLoadFlags>& flags)
{
	clearCache();
	m_defaultLoadFlags = flags;
}

}


