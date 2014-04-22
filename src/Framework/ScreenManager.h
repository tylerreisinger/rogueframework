#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include <unordered_map>
#include <memory>
#include <string>
#include <deque>

#include "Framework/Screen.h"

namespace rf
{

/**
 * @brief Manages the updating and rendering of Screen objects.
 * @details All registered Screen objects are accessible by name and can either be
 * set as the active Screen, which is the primary screen of the game, or an overlay screen
 * which presents information on top of the active screen.
 * All Screen objects are owned by the ScreenManager and can be assumed to exist until
 * the screen manager is destroyed or RemoveScreen is called.
 */
class ScreenManager
{
public:
	ScreenManager() = default;
	~ScreenManager() = default;

	ScreenManager(const ScreenManager&) = delete;
	ScreenManager(ScreenManager&&) = delete;
	ScreenManager& operator =(const ScreenManager&) = delete;
	ScreenManager& operator =(ScreenManager&&) = delete;

	/**
	 * @brief Adds a new Screen.
	 * @param screen The Screen to add.
	 * @throw ObjectAlreadyExistsException A Screen with the name @a name already exists.
	 */
	void addScreen(std::unique_ptr<Screen> screen);

	///Return true if a screen with the name @a name is registered, false otherwise.
	bool hasScreen(const std::string& name) const;

	/**
	 * @brief Remove a registered Screen.
	 * @param name The name of the Screen to remove.
	 * @return A std::unique_ptr owning the removed Screen.
	 * @throw std::out_of_range No screen is registered with the name @a name.
	 */
	std::unique_ptr<Screen> removeScreen(const std::string& name);

	///Return the active screen or nullptr if there is no active screen.
	Screen* getActiveScreen() {return m_activeScreen;}

	///Return the string registered with the given name or nullptr if no screen is registerd with that name.
	Screen* getScreen(const std::string& name);

	/**
	 * @brief Activate a screen with the given name, deactivating any previously active screen.
	 * @details If the screen is currently the active screen, this function does nothing.
	 * @param name The name of the screen to activate.
	 * @throw std::out_of_range No screen is registered with the name @a name.
	 * @throw std::runtime_error The screen is currently an overlay screen.
	 * A screen may not be both an overlay and the active screen at the same time.
	 */
	void activateScreen(const std::string& name);

	/**
	 * @brief Make the Screen named @a name an active overlay.
	 * @details If the screen is currently an overlay, this function does nothing.
	 * @throw std::out_of_range No screen is registered with the name @a name.
	 * @throw std::runtime_error The screen is currently the active screen.
	 * A screen may not be both an overlay and the active screen at the same time.
	 */
	void addOverlay(const std::string& name);

	///If the screen named @a name is an overlay, deactivate it, otherwise, do nothing.
	void removeOverlay(const std::string& name);
	///Return true if the screen named @a name is an overlay, false otherwise
	bool isOverlay(const std::string& name) const;

	/**
	 * @brief Return the overlay position of the screen named @a name.
	 * @details The overlay position is the index in the z-order of overlay screens.
	 * The overlay with position = 0 is the first drawn followed by 1 and so on
	 * until the end of the overlay stack.
	 * @throw std::out_of_range No screen is registered with the name @a name.
	 */
	int getOverlayPosition(const std::string& name) const;

	///Return the current number of active overlays.
	int overlayCount() const {return m_overlayStack.size();}

	/**
	 * @brief Change the overlay position of the Screen named @a name to @a newPosition.
	 * @details @a newPosition is clamped to the valid range of overlay positions
	 * (0, overlayCount] and is inserted before the element currently in that position, if any.
	 * If the Screen is not an overlay before calling this function, it is inserted
	 * as an overlay into the position specified.
	 * @param name The name of the overlay Screen to move.
	 * @param newPosition The position to move to.
	 * @throw std::out_of_range No screen is registered with the name @a name.
	 */
	void moveOverlay(const std::string& name, int newPosition);

	///Deactivate all overlay screens
	void removeAllOverlays();

	void draw();
	void update();

protected:

	std::unordered_map<std::string, std::unique_ptr<Screen>> m_screens;

	Screen* m_activeScreen = nullptr;
	std::deque<Screen*> m_overlayStack;
};

}
#endif
