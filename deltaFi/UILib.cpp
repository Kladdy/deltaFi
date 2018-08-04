#include "stdafx.h"
#include "UILib.h"

using namespace sf;
using namespace std;

Font UILib::loadFontFromMemory(const void* data, int sizeInBytes) {
	sf::Font font;
	if (!font.loadFromMemory(data, sizeInBytes)) {
		cout << "Failed to load font" << endl;
	}

	return font;
}

Texture UILib::loadTextureFromMemory(const void* data, int sizeInBytes) {
	sf::Texture texture;
	if (!texture.loadFromMemory(data, sizeInBytes)) {
		cout << "Failed to load texture" << endl;
	}
	texture.setSmooth(true);
	return texture;
}


UILib::UILib()
{
}


UILib::~UILib()
{
}
