#include "stdafx.h"
#include "WindowController.h"

using namespace sf;
using namespace std;

namespace variables
{
	enum state
	{
		menu = 0,
		particle = 1,
	};
	state currentState = menu;

	//Fonts
	map<string, sf::Font> textFonts;

	//Text labels
	vector<sf::Text> textLabels;

	//Textures
	map<string, sf::Texture> loadedTextures;
	
}

namespace menuVariables
{
	//Introanimation
	bool animateIntro = false;
	Clock animateIntroClock;
	Int32 currentTime;
	float yDisplacement;

	//CircleShapes
	vector<sf::CircleShape> circleShapes;

	//Sprites
	vector<sf::Sprite> loadedSprites;
}

namespace particleVariables
{
	//CircleShapes
	vector<sf::CircleShape> circleShapes;
}

using namespace variables;

void WindowController::mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed)
{

}

void WindowController::updateWindow(sf::RenderWindow& window, int FPS)
{
	textLabels[0].setString("FPS: " + to_string(FPS));

	for (Text text : textLabels) {
		window.draw(text);
	}

	switch (currentState)
	{
	case menu:
		if (menuVariables::animateIntro) menuAnimation();

		for (Sprite loaded_sprite : menuVariables::loadedSprites){
			window.draw(loaded_sprite);
		}
		break;

	case particle:
		for (CircleShape circle_shape : particleVariables::circleShapes) {
			window.draw(circle_shape);
		}
		break;

	default:
		break;
	}
}

void WindowController::initializeAssets(int state)
{
	UILib IL;
	//Fonts
	textFonts["comfortaa"] = IL.loadFontFromMemory((void*)ComfortaaLight, ComfortaaLight_Size);

	//Textures
	loadedTextures["deltaFiLogo"] = IL.loadTextureFromMemory((void*)deltaFiLogo, deltaFiLogo_Size);

	//FPS counter
	newText(-1, Vector2f(1423, 720), "FPS: ", "font", 20, Color::White);

	switch (state)
	{
	case 0:
		newSprite(state, Vector2f(750, 200), "deltaFiLogo", Vector2f(1.f, 1.f)); //Logo
		menuVariables::animateIntro = true;
		menuVariables::animateIntroClock.restart();
		break;

	case 1:
		newCircleShape(state, Vector2f(300, 300), 50, 50, Color::Black, Color::Cyan, 5, 0);
		break;

	default:
		break;
	}
}

void WindowController::newText(int state, sf::Vector2f position, string text, string font, int size, sf::Color color) 
{
	sf::Text label;
	label.setPosition(position);
	label.setString(text);
	label.setCharacterSize(size);
	label.setFillColor(color);
	label.setFont(textFonts["comfortaa"]);

	if (state == -1) textLabels.push_back(label);
}

void WindowController::newSprite(int state, sf::Vector2f position, string texture, sf::Vector2f scale) 
{
	sf::Sprite sprite;
	sprite.setTexture(loadedTextures[texture]);
	sprite.setScale(scale);
	sprite.setOrigin((int)(sprite.getGlobalBounds().width / 2), (int)(sprite.getGlobalBounds().height / 2));
	sprite.setPosition(position);

	if (state == 0) menuVariables::loadedSprites.push_back(sprite);
}

void WindowController::newCircleShape(int state, sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness, int rotation) 
{
	sf::CircleShape c(radius, corners);
	c.setFillColor(color);
	c.setOutlineColor(outlineColor);
	c.setOutlineThickness(outlineThickness);
	c.setOrigin((int)(c.getGlobalBounds().width / 2), (int)(c.getGlobalBounds().height / 2));
	c.rotate(rotation);
	c.setPosition(position);

	if (state == 0) menuVariables::circleShapes.push_back(c);
	if (state == 1) particleVariables::circleShapes.push_back(c);
}

void WindowController::menuAnimation()
{
	if (menuVariables::currentTime <= 5541) {
		menuVariables::currentTime = menuVariables::animateIntroClock.getElapsedTime().asMilliseconds();
		menuVariables::yDisplacement = (200 - (float)100 * (float)(exp((float)(menuVariables::currentTime - 2400.f) / -1000.f))*(float)sin((float)(menuVariables::currentTime - 2400.f) / 1000.f));
		menuVariables::loadedSprites[0].setPosition(Vector2f(750, menuVariables::yDisplacement));

		Color color = menuVariables::loadedSprites[0].getColor();
		color.a = 255 * menuVariables::currentTime / 5541;
		menuVariables::loadedSprites[0].setColor(color);
	} else {
		menuVariables::currentTime = menuVariables::animateIntroClock.getElapsedTime().asMilliseconds();
		menuVariables::yDisplacement = 200 + 25*(float)sin((float)((menuVariables::currentTime + 742.f)/1000.f));
		menuVariables::loadedSprites[0].setPosition(Vector2f(750, menuVariables::yDisplacement));
	}

	;
}


WindowController::WindowController()
{

}

WindowController::~WindowController()
{

}
