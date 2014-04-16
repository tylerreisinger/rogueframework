#ifndef SDL_WINDOW_H_
#define SDL_WINDOW_H_

#include "Framework/Window.h"

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "Framework/Flags.h"
#include "Framework/Vector2.h"

namespace rf
{
class Event;

/**
 * @brief Represents a single window managed by SDL
 */
class SdlWindow : public Window
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

	SdlWindow(SdlWindow&& other);
	SdlWindow& operator =(SdlWindow&& other);

	///Set the title of the window
	virtual void setTitle(const std::string& title) override;

	///Resize the window's client area
	virtual void resize(int width, int height) override;

	///Return the window client area size
	virtual Vector2i size() const override;

	///Move the window to @a position.
	virtual void move(const Vector2i& position) override;

	///Return the position of the window, in screen coordinates.
	virtual Vector2i position() const override;

	///Return the width of the window
	virtual int width() const override;
	///Return the height of the window
	virtual int height() const override;

	///Display rendered content.
	void display() const;

	///Return a vector of all pending events in the SDL event queue.
	virtual std::vector<std::unique_ptr<Event>> getEvents() override;

	///Return a single pending event from the SDL event queue
	///@details Return nullptr if no events are pending
	virtual std::unique_ptr<Event> getNextEvent() override;

	///Return the raw handle to the sdl window
	SDL_Window* getHandle() const {return m_window;}

protected:

	std::unique_ptr<Event> translateEvent(const SDL_Event& event);

	SDL_Window* m_window = nullptr;
};

}

#endif
