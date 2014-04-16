#include "SdlWindow.h"

#include "Exceptions/SdlException.h"

namespace rf
{

SdlWindow::SdlWindow(const std::string& title, int width, int height,
		const Flags<WindowFlags>& flags)
{
	Flags<WindowFlags> flagsCopy;
	flagsCopy.setFlag(WindowFlags::OpenGL);
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, flags.getRawValue());

	if(m_window == nullptr)
	{
		throw SdlException("SDL_CreateWindow failed");
	}
}

SdlWindow::~SdlWindow()
{
	if(m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
	}
}

void SdlWindow::setTitle(const std::string& title)
{
	SDL_SetWindowTitle(m_window, title.c_str());
}

void SdlWindow::resizeWindow(int width, int height)
{
	SDL_SetWindowSize(m_window, width, height);
}

void SdlWindow::size(int& width, int& height) const
{
	SDL_GetWindowSize(m_window, &width, &height);
}

void SdlWindow::setPosition(const Vector2i& position)
{
	SDL_SetWindowPosition(m_window, position.x, position.y);
}

Vector2i SdlWindow::position() const
{
	int x;
	int y;
	SDL_GetWindowPosition(m_window, &x, &y);
	return Vector2i(x, y);
}

int SdlWindow::width() const
{
	int width;
	int height;
	SDL_GetWindowSize(m_window, &width, &height);
	return width;
}

int SdlWindow::height() const
{
	int width;
	int height;
	SDL_GetWindowSize(m_window, &width, &height);
	return height;
}

void SdlWindow::display() const
{
	SDL_GL_SwapWindow(m_window);
}

}

