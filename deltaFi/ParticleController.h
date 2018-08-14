#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "ClickArea.h"
#include "ClickRadius.h"
#include <functional>
#include "UILib.h"
#include "math.h"
#include <cmath>
#include "RoundedRectangleShape.h"

class ParticleController
{
public:
	void initializeAssets();
	void mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed);
	void keyPressed(sf::Keyboard::Key key, bool control, bool alt, bool shift, bool system);
	void updateWindow(sf::RenderWindow& window, sf::Vector2i mousePos);

	void fadeAnimatíon();

	ParticleController();
	~ParticleController();
};

