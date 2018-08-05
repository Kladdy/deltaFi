#include "stdafx.h"
#include "ClickRadius.h"

bool ClickRadius::isHovered(sf::Vector2i mousePos){
	pow(3, 2);
	sf::Vector2f delta = sf::Vector2f((float)(this->centerXY.x - mousePos.x), (float)(this->centerXY.y - mousePos.y));
	return (pow(delta.x,2) + pow(delta.y, 2) <= pow((this->radius),2));
}


ClickRadius::ClickRadius()
{
}


ClickRadius::~ClickRadius()
{
}
