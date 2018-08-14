#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class UILib
{
public:

	sf::Font loadFontFromMemory(const void* data, int sizeInBytes);
	sf::Texture loadTextureFromMemory(const void* data, int sizeInBytes);
	sf::SoundBuffer loadSoundBufferFromMemory(const void* data, int sizeInBytes);

	sf::Text newText(sf::Vector2f position, std::string text, sf::Font* font, int size, sf::Color color, bool center);
	sf::Sprite newSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, int yDisplacement);
	sf::CircleShape newCircleShape(sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness, int rotation);
	sf::RectangleShape newRectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color, int outlineThickness, sf::Color outlineColor, int rotation, bool center);

	UILib();
	~UILib();
};

