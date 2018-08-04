#pragma once
#include "stdafx.h"
#include "deltaFi.h"

class ClickArea {
public:
	bool isClicked(sf::Vector2i mousePos);
	bool isHovered(sf::Vector2i mousePos);
	sf::Vector2i topLeftXY;
	sf::Vector2i areaSize;
};