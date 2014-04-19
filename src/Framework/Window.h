#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>
#include <memory>

#include "Framework/Vector2.h"

namespace rf
{
class Event;

class Window
{
public:
	Window() = default;
	virtual ~Window() = default;

	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;

	///Set the title of the window
	virtual void setTitle(const std::string& title) = 0;

	///Resize the window's client area
	virtual void resize(int width, int height) = 0;

	///Return the width of the window
	virtual int width() const = 0;
	///Return the height of the window
	virtual int height() const = 0;

	///Move the window to @a position.
	virtual void move(const Vector2i& position) = 0;

	///Return the window client area size
	virtual Vector2i size() const = 0;

	///Return the position of the window, in screen coordinates.
	virtual Vector2i position() const = 0;

	///Return a vector of all pending events in the SDL event queue.
	virtual std::vector<std::unique_ptr<Event>> getEvents() = 0;

	///Return a single pending event from the SDL event queue
	///@details Return nullptr if no events are pending
	virtual std::unique_ptr<Event> getNextEvent() = 0;

	virtual void display() const = 0;

protected:

};

}

#endif
