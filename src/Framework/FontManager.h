#ifndef FONTMANAGER_H_
#define FONTMANAGER_H_

#include <tuple>
#include <vector>
#include <unordered_map>
#include <memory>

#include <ft2build.h>
#include <boost/functional/hash_fwd.hpp>

#include "Framework/FontFace.h"

#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace rf
{

class FontManager
{
	struct FaceHasher
	{
		size_t operator ()(const std::tuple<std::string, int, int>& key) const
		{
			size_t hash = std::hash<std::string>()(std::get<0>(key));
			hash ^= std::get<1>(key);
			hash ^= std::get<2>(key);

			return hash;
		}
	};

public:
	typedef std::unordered_map<std::tuple<std::string, int, int>, std::weak_ptr<const FontFace>, FaceHasher> FaceMap;

	FontManager();
	~FontManager();

	FontManager(const FontManager&) = delete;
	FontManager(FontManager&& other) noexcept;
	FontManager& operator =(const FontManager&) = delete;
	FontManager& operator =(FontManager&& other) noexcept;

	FontFace createFontFace(const std::string& name, int sizeX, int sizeY);

	std::shared_ptr<const FontFace> getFontFace(const std::string& name, int sizeX, int sizeY);

	FT_Library getFreeTypeLibrary() const {return m_library;}

	void clearCache();

	void setDefaultGlyphLoadFlags(const Flags<FontFace::GlyphLoadFlags>& flags);

protected:

	std::shared_ptr<std::vector<unsigned char>> getFontData(const std::string& fileName);

	std::shared_ptr<std::vector<unsigned char>> loadFontFile(const std::string& fileName) const;

	FaceMap m_faces;
	std::unordered_map<std::string, std::weak_ptr<std::vector<unsigned char>>> m_fontData;
	Flags<FontFace::GlyphLoadFlags> m_defaultLoadFlags = FontFace::GlyphLoadFlags::Render;

	FT_Library m_library = nullptr;
};

}

#endif
