#pragma once
#include "deltaFi.h"
class ClickRadius
{
public:
	bool isHovered(sf::Vector2i mousePos);
	sf::Vector2f centerXY;
	float radius;

	ClickRadius();
	~ClickRadius();
};

