#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "ClickArea.h"
#include "ClickRadius.h"
#include <functional>
#include "WindowController.h"
#include "UILib.h"
#include "math.h"
#include <cmath>
#include "fonts.hpp"
#include "textures.hpp"
#include "musics.hpp"
#include "sounds.hpp"

class WindowController
{
public:
	void mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed);
	void keyPressed(sf::Keyboard::Key key, bool control, bool alt, bool shift, bool system);
	void updateWindow(sf::RenderWindow& window, sf::Vector2i mousePos, int FPS, int UPS);
	void initializeAssets(int state);

	void newMenuButton(std::string text, sf::Color hoverColor, std::string icon, sf::Vector2f iconScale);

	void runIntro();
	void menuAnimation(sf::Vector2i mousePos);

	WindowController();
	~WindowController();

	
};

