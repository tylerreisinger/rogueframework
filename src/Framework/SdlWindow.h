#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>

#include "Flags.h"
#include "Vector2.h"

namespace rf
{


/**
 * @brief Represents a single window managed by the system.
 * @details Windows are currently managed by SDL and thus this class is a wrapper for the SDL window interface.
 */
class SdlWindow
{
public:

	enum class WindowFlags : Uint32 {Fullscreen = SDL_WINDOW_FULLSCREEN, OpenGL = SDL_WINDOW_OPENGL,
		Borderless = SDL_WINDOW_BORDERLESS, Resizable = SDL_WINDOW_RESIZABLE};

	/**
	 * @brief Construct a new window.
	 * @param title The title of the window.
	 * @param width The window of the window, in pixels.
	 * @param height The height of the window, in pixels.
	 * @param flags Combination of WindowFlags to modify the window behavior.
	 * @throw SDLException The window could not be created.
	 */
	SdlWindow(const std::string& title, int width, int height, const Flags<WindowFlags>& flags = {});

	virtual ~SdlWindow();

	///Disallow copying
	SdlWindow(const SdlWindow&) = delete;
	///Disallow moving
	SdlWindow(SdlWindow&&) = delete;
	///Disallow copying
	SdlWindow& operator =(const SdlWindow&) = delete;
	///Disallow moving
	SdlWindow& operator =(SdlWindow&&) = delete;

	///Set the title of the window
	void setTitle(const std::string& title);

	///Resize the window's client area
	void resizeWindow(int width, int height);

	/**
	 * Return the window's client area size.
	 * @param width Out. The current width of the window, in pixels.
	 * @param height Out. The current height of the window, in pixels.
	 */
	void size(int& width, int& height)const;

	///Set the position of the window, in screen coordinates.
	void setPosition(const Vector2i& position);

	///Return the position of the window, in screen coordinates.
	Vector2i position() const;

	int width() const;
	int height() const;

	//GL Functions

	///Display rendered content.
	void display() const;

	SDL_Window* getHandle() const {return m_window;}

protected:
	SDL_Window* m_window = nullptr;
};

}

#endif
