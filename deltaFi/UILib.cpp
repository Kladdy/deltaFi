#include "stdafx.h"
#include "UILib.h"
#include <iostream>
#include <SFML/Audio.hpp>

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

Text UILib::newText(sf::Vector2f position, string text, Font* font, int size, sf::Color color, bool center)
{
	sf::Text label;
	label.setString(text);
	label.setCharacterSize(size);
	label.setFillColor(color);
	label.setFont(*font);
	if (center) label.setOrigin((int)(label.getGlobalBounds().width / 2), (int)(label.getGlobalBounds().height / 2));
	label.setPosition(position);

	return label;
}

Sprite UILib::newSprite(sf::Vector2f position, Texture* texture, sf::Vector2f scale, int yDisplacement)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setOrigin((int)(sprite.getGlobalBounds().width / 2), (int)(sprite.getGlobalBounds().height / 2 + yDisplacement));
	sprite.setScale(scale);
	sprite.setPosition(position);

	return sprite;
}

CircleShape UILib::newCircleShape(sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness, int rotation)
{
	sf::CircleShape circleShape(radius, corners);
	circleShape.setFillColor(color);
	circleShape.setOutlineColor(outlineColor);
	circleShape.setOutlineThickness(outlineThickness);
	circleShape.setOrigin((int)(circleShape.getGlobalBounds().width / 2), (int)(circleShape.getGlobalBounds().height / 2));
	circleShape.rotate(rotation);
	circleShape.setPosition(position);

	return circleShape;
}

RectangleShape UILib::newRectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color, int outlineThickness, sf::Color outlineColor, int rotation, bool center) {

	sf::RectangleShape rect(size);
	rect.setFillColor(color);
	rect.rotate(rotation);
	rect.setPosition(position);
	rect.setOutlineThickness(outlineThickness);
	rect.setOutlineColor(outlineColor);
	if (center) rect.setOrigin((int)(size.x / 2), (int)(size.y / 2));

	return rect;
}

UILib::UILib()
{
}


UILib::~UILib()
{
}
