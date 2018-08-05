#pragma once
#include "deltaFi.h"
#include "fonts.hpp"
#include "textures.hpp"

class WindowController
{
public:
	void mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed);
	void keyPressed(sf::Keyboard::Key key, bool control, bool alt, bool shift, bool system);
	void updateWindow(sf::RenderWindow& window, sf::Vector2i mousePos, int FPS);
	void initializeAssets(int state);

	void newCircleShape(int state, sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness, int rotation);
	sf::CircleShape newCircleShapeMenu(sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness);
	void newSprite(int state, sf::Vector2f position, std::string texture, sf::Vector2f scale);
	sf::Sprite newSpriteMenu(sf::Vector2f postion, std::string texture, sf::Vector2f scale);
	void newText(int state, sf::Vector2f position, std::string text, std::string font, int size, sf::Color color, bool center);
	sf::Text newTextMenu(sf::Vector2f position, std::string text, std::string font, int size, sf::Color color, bool center);
	void newMenuButton(std::string text, sf::Color hoverColor, std::string icon, sf::Vector2f iconScale);
	void menuAnimation(sf::Vector2i mousePos);
	void runIntro();

	WindowController();
	~WindowController();

	
};

