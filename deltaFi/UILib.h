#pragma once
#include "deltaFi.h"

class UILib
{
public:

	sf::Font loadFontFromMemory(const void* data, int sizeInBytes);
	sf::Texture loadTextureFromMemory(const void* data, int sizeInBytes);

	UILib();
	~UILib();
};

