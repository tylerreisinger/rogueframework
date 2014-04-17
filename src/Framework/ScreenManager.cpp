#include "ScreenManager.h"

#include <algorithm>

#include "Framework/Exceptions/NotFoundException.h"
#include "Framework/Exceptions/ObjectExistsException.h"

namespace rf
{

void ScreenManager::addScreen(std::unique_ptr<Screen> screen)
{
	if(hasScreen(screen->name()))
	{
		throw ObjectExistsException("Cannot add a new screen with name '" + screen->name() +
				"' as a screen with that name already exists");
	}
	m_screens[screen->name()] = std::move(screen);
}

bool ScreenManager::hasScreen(const std::string& str) const
{
	return m_screens.find(str) != m_screens.end();
}

std::unique_ptr<Screen> ScreenManager::removeScreen(const std::string& name)
{
	auto iter = m_screens.find(name);
	if(iter == m_screens.end())
	{
		throw NotFoundException("Screen with the name '" + name + "' could not be removed "
				"as no screen is registered with that name");
	}
	std::unique_ptr<Screen> screen = std::move(iter->second);
	if(m_activeScreen == screen.get())
	{
		m_activeScreen->onDeactivate();
		m_activeScreen = nullptr;
	}
	//If the screen to be removed is an overlay, remove it
	for(auto it = m_overlayStack.begin(); it != m_overlayStack.end(); ++it)
	{
		if(*it == screen.get())
		{
			(*it)->onDeactivate();
			m_overlayStack.erase(it);
			break;
		}
	}
	m_screens.erase(iter);
	return screen;
}

void ScreenManager::activateScreen(const std::string& name)
{
	Screen* screen;
	try
	{
		screen = m_screens.at(name).get();
	}
	catch(const NotFoundException&)
	{
		throw NotFoundException("Screen '" + name + "' could not be activated"
				"as no screen with that name is registered");
	}
	if(screen == m_activeScreen)
	{
		return;
	}
	if(isOverlay(name))
	{
		//TODO: Make another one of these
		throw Exception("Screen '" + name + "' is already an overlay. "
				"A screen may not be both an overlay and the active screen at the same time");
	}
	m_activeScreen = screen;
	screen->onActivate(false);
}

Screen* ScreenManager::getScreen(const std::string& name)
{
	auto iter = m_screens.find(name);
	if(iter != m_screens.end())
	{
		return iter->second.get();
	}
	else
	{
		return nullptr;
	}
}

void ScreenManager::addOverlay(const std::string& name)
{
	if(!isOverlay(name))
	{
		Screen* screen = getScreen(name);
		if(!screen)
		{
			throw NotFoundException("No screen registered with the name '" + name + "'");
		}
		if(screen == m_activeScreen)
		{
			throw Exception("The screen '" + name + "' is the active screen, "
					"it may not also be made an overlay screen.");

		}
		m_overlayStack.push_back(screen);
		screen->onActivate(true);
	}
}

void ScreenManager::removeOverlay(const std::string& name)
{
	if(isOverlay(name))
	{
		for(auto it = m_overlayStack.begin(); it != m_overlayStack.end(); ++it)
		{
			if((*it)->name() == name)
			{
				(*it)->onDeactivate();
				m_overlayStack.erase(it);
				break;
			}
		}
	}
}

bool ScreenManager::isOverlay(const std::string& name) const
{
	for(auto it : m_overlayStack)
	{
		if(it->name() == name)
		{
			return true;
		}
	}
	return false;
}

int ScreenManager::getOverlayPosition(const std::string& name) const
{
	int pos = 0;
	for(auto it : m_overlayStack)
	{
		if(it->name() == name)
		{
			return pos;
		}
		++pos;
	}
	throw NotFoundException("No screen with name '" + name + "' is currently acting as an an overlay.");
}

void ScreenManager::moveOverlay(const std::string& name, int newPosition)
{
	removeOverlay(name);
	Screen* screen = getScreen(name);
	newPosition = std::max(newPosition, static_cast<int>(m_overlayStack.size()));
	newPosition = std::min(newPosition, 0);
	m_overlayStack.insert(m_overlayStack.begin() + newPosition + 1, screen);
}

void ScreenManager::removeAllOverlays()
{
	m_overlayStack.clear();
}

}
