#pragma once
#include "deltaFi.h"

class WindowController
{
public:
	void mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed);
	void updateWindow(sf::RenderWindow& window);


	WindowController();
	~WindowController();
};

