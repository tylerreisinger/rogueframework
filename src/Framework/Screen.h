#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>

namespace rf
{

/**
 * @brief Represents a transparent 'screen' on which content is rendered.
 * @details Zero or more screens can be drawn each frame with zero or one active screen and
 * any number of overlay screens on top of the active screen. Screens are drawn in a specific
 * order and each occupies the entire screen. Screens are generally created at the beginning
 * of the program and stored in an inactive state when they don't need drawn. This allows
 * persistent state even when a screen is not visible.
 */

class Screen
{
	friend class ScreenManager;
public:
	explicit Screen(const std::string& name);
	virtual ~Screen() = default;

	Screen(const Screen&) = delete;
	Screen(Screen&&) = delete;
	Screen& operator =(const Screen&) = delete;
	Screen& operator =(Screen&&) = delete;

	///Return the name of the Screen.
	std::string name() const {return m_name;}

protected:
	std::string m_name;

	///Called when the Screen is activated or made an overlay.
	virtual void onActivate(bool isOverlay) {};
	///Called when the Screen is deactivated or removed as an overlay.
	virtual void onDeactivate() {};
	///Called every frame during the update phase.
	virtual void update() = 0;
	///Called every frame on active Screens. All drawing should occur only here.
	virtual void draw() = 0;
};

}
#endif
