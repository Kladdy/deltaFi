#pragma once
#include "deltaFi.h"
#include "fonts.hpp"
#include "textures.hpp"

class WindowController
{
public:
	void mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed);
	void updateWindow(sf::RenderWindow& window, int FPS);
	void initializeAssets(int state);

	void newCircleShape(int state, sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness, int rotation);
	void newSprite(int state, sf::Vector2f position, std::string texture, sf::Vector2f scale);
	void newText(int state, sf::Vector2f position, std::string text, std::string font, int size, sf::Color color);
	void menuAnimation();

	WindowController();
	~WindowController();

	
};

