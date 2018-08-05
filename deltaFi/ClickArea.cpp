#include "stdafx.h"
#include "ClickArea.h"

bool ClickArea::isHovered(sf::Vector2i mousePos) {
	return ((mousePos.x >= this->topLeftXY.x && mousePos.x <= (this->topLeftXY.x + this->areaSize.x)) && (mousePos.y >= this->topLeftXY.y && mousePos.y <= (this->topLeftXY.y + this->areaSize.y)));
}