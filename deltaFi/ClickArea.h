#pragma once
#include "stdafx.h"
#include "deltaFi.h"

class ClickArea {
public:
	bool isHovered(sf::Vector2i mousePos);
	sf::Vector2i topLeftXY;
	sf::Vector2i areaSize;
};