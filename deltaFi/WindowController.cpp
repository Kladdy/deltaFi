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
	//Menu buttons
	struct menuButton
	{
		int index;
		bool isVisable;
		bool isHovered;
		bool animateHover;
		CircleShape circleShape;
		ClickRadius clickRadius;
		Color hoverColor;
		Clock hoverClock;
		Text textLable;
		Sprite icon;
	};
	vector<menuButton> menuButtons;
	int menuButtonTextSize = 18;
	int menuButtonRadius = 80;
	int menuButtonCorners = 50;
	Color menuButtonColor = Color(200, 200, 200, 200);
	int menuButtonOutlineSize = 4;
	int distanceBetweenButtons = 250;

	//Introanimation
	bool animateIntro = false;
	Clock animateIntroClock;
	Int32 currentTime;
	float yDisplacement;

	//CircleShapes
	vector<CircleShape> circleShapes;

	//Sprites
	vector<Sprite> loadedSprites;
}

namespace particleVariables
{
	//CircleShapes
	vector<sf::CircleShape> circleShapes;
}

using namespace variables;

void WindowController::mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed)
{
	cout << "X: " << mousePos.x << " Y: " << mousePos.y << endl;

	for (menuVariables::menuButton menu_button : menuVariables::menuButtons)
	{
		if (menu_button.isHovered){
			menuVariables::animateIntro = false;
			currentState = state(menu_button.index + 1);
		}
	}

}

void WindowController::keyPressed(Keyboard::Key key, bool control, bool alt, bool shift, bool system)
{
	cout << "Key: " << key << endl;

	if (Keyboard::Key::Escape)
	if (currentState != menu){
		currentState = menu;
		runIntro();
	}

}


void WindowController::updateWindow(sf::RenderWindow& window, Vector2i mousePos, int FPS)
{
	textLabels[0].setString("FPS: " + to_string(FPS));

	for (Text text : textLabels) {
		window.draw(text);
	}

	switch (currentState)
	{
	case menu:
		if (menuVariables::animateIntro) menuAnimation(mousePos);

		for (Sprite loaded_sprite : menuVariables::loadedSprites){
			window.draw(loaded_sprite);
		}

		for (menuVariables::menuButton menu_button : menuVariables::menuButtons){
			if (menu_button.isVisable){
				window.draw(menu_button.circleShape);
				window.draw(menu_button.textLable);
			}
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
	textFonts["opensans"] = IL.loadFontFromMemory((void*)OpenSans, OpenSans_Size);

	//Textures
	loadedTextures["deltaFiLogo"] = IL.loadTextureFromMemory((void*)deltaFiLogo, deltaFiLogo_Size);

	//FPS counter
	newText(-1, Vector2f(1423, 720), "FPS: ", "opensans", 20, Color::White, false);

	switch (state)
	{
	case 0:
		newSprite(state, Vector2f(750, 200), "deltaFiLogo", Vector2f(0.8f, 0.8f)); //Logo
		newMenuButton("Particles", Color(211, 164, 232, 200));
		newMenuButton("Planetary", Color(211, 164, 232, 200));
		newMenuButton("Pendulum", Color(211, 164, 232, 200));
		newMenuButton("Swing", Color(211, 164, 232, 200));
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

void WindowController::newText(int state, sf::Vector2f position, string text, string font, int size, sf::Color color, bool center)
{
	sf::Text label;
	label.setString(text);
	label.setCharacterSize(size);
	label.setFillColor(color);
	label.setFont(textFonts[font]);
	if (center) label.setOrigin((int)(label.getGlobalBounds().width / 2), (int)(label.getGlobalBounds().height / 2));
	label.setPosition(position);

	if (state == -1) textLabels.push_back(label);
}

Text WindowController::newTextMenu(sf::Vector2f position, string text, string font, int size, sf::Color color, bool center)
{
	sf::Text label;
	label.setString(text);
	label.setCharacterSize(size);
	color.a = 0;
	label.setFillColor(color);
	label.setFont(textFonts[font]);
	if (center) label.setOrigin((int)(label.getGlobalBounds().width / 2), (int)(label.getGlobalBounds().height / 2));
	label.setPosition(position);

	return label;
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

CircleShape WindowController::newCircleShapeMenu(sf::Vector2f position, int radius, int corners, sf::Color color, sf::Color outlineColor, int outlineThickness)
{
	sf::CircleShape c(radius, corners);
	c.setFillColor(color);
	outlineColor.a = 0;
	c.setOutlineColor(outlineColor);
	c.setOutlineThickness(outlineThickness);
	c.setOrigin((int)(c.getGlobalBounds().width / 2), (int)(c.getGlobalBounds().height / 2));
	c.setPosition(position);

	return c;
}

void WindowController::newMenuButton(string text, Color hoverColor)
{
	using namespace menuVariables;
	menuButton button;
	sf::Vector2f pos;
	pos.y = 400 + 200 * (menuButtons.size() % 2);
	pos.x = 400 + distanceBetweenButtons * floor(menuButtons.size() / 2);

	button.circleShape = newCircleShapeMenu(pos, menuButtonRadius, menuButtonCorners, Color::Black, menuButtonColor, menuButtonOutlineSize);
	button.textLable = newTextMenu(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius), text, "opensans", menuButtonTextSize, Color::White, true);
	button.index = menuButtons.size();
	button.isVisable = false;
	ClickRadius c;
	c.centerXY = pos;
	c.radius = menuButtonRadius + menuButtonOutlineSize;
	button.clickRadius = c;
	button.isHovered = false;
	button.hoverColor = hoverColor;
	button.hoverClock.restart();
	button.animateHover = false;

	menuButtons.push_back(button);
}

void WindowController::runIntro()
{
	menuVariables::animateIntroClock.restart();
	menuVariables::animateIntro = true;
	for (menuVariables::menuButton menu_button : menuVariables::menuButtons)
	{
		menuVariables::menuButtons[menu_button.index].isVisable = false;
		menuVariables::menuButtons[menu_button.index].animateHover = false;
		menuVariables::menuButtons[menu_button.index].isHovered = false;
	}
}


void WindowController::menuAnimation(Vector2i mousePos)
{
	using namespace menuVariables;
	currentTime = animateIntroClock.getElapsedTime().asMilliseconds();
	if (currentTime <= 5541) {
		
		yDisplacement = (130 - (float)100 * (float)(exp((float)(currentTime - 2400.f) / -1000.f))*(float)sin((float)(currentTime - 2400.f) / 1000.f));
		loadedSprites[0].setPosition(Vector2f(750, yDisplacement));

		Color color = loadedSprites[0].getColor();
		color.a = 255 * currentTime / 5541;
		loadedSprites[0].setColor(color);
	} else {
		yDisplacement = 130 + 20*(float)sin((float)((currentTime + 742.f)/1000.f));
		loadedSprites[0].setPosition(Vector2f(750, yDisplacement));
	}
	if (currentTime >= 1700 && currentTime <= 5541 + 500.f * (menuButtons.size()-1))
	{
		int i = 0;
		for (menuButton menu_button : menuButtons)
		{
			i = menu_button.index;
			if (!menuButtons[i].isVisable && currentTime >= 1700.f + 500.f * i) {
				menuButtons[i].isVisable = true;
			} 
			if (currentTime >= 1700.f + 500.f * i && currentTime <= 5541 + 500 * i) {
				Vector2f pos = menuButtons[i].circleShape.getPosition();
				pos.y = 400 + 200 * (i % 2) - (float)50 * (float)(exp((float)(currentTime - 2400.f - 500.f * i) / -1000.f))*(float)sin((float)(currentTime - 2400.f - 500.f * i) / 1000.f);
				menuButtons[i].circleShape.setPosition(pos);
				menuButtons[i].textLable.setPosition(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius));

				Color color = menuButtonColor;
				color.a = menuButtonColor.a * (currentTime - (500.f * i) - 1700.f) / 3841.f;
				menuButtons[i].circleShape.setOutlineColor(color);
				menuButtons[i].textLable.setFillColor(Color(255, 255, 255, color.a));
			}
			
		}
	} else if (currentTime > 5541 + 500.f * (menuButtons.size() - 1)) {
		int i = 0;
		for (menuButton menu_button : menuButtons)
		{
			i = menu_button.index;
			Int32 clockTime = menuButtons[i].hoverClock.getElapsedTime().asMilliseconds();
			if (!menu_button.isHovered && menu_button.clickRadius.isHovered(mousePos)) {
				menuButtons[i].circleShape.setOutlineColor(menu_button.hoverColor);
				menuButtons[i].isHovered = true;
				menuButtons[i].animateHover = true;
				menuButtons[i].hoverClock.restart();
			} else if (menu_button.isHovered && !(menu_button.clickRadius.isHovered(mousePos))) {
				menuButtons[i].circleShape.setOutlineColor(menuButtonColor);
				menuButtons[i].isHovered = false;
				menuButtons[i].hoverClock.restart();
			} else if(menu_button.isHovered && menu_button.clickRadius.isHovered(mousePos)) {
				if(menu_button.animateHover && clockTime < 141) {
					Vector2f pos = menuButtons[i].circleShape.getPosition();
					pos.y = 400 + 200 * (i % 2) - 15.f *((float)((float)clockTime / 200.f) / (float)exp((float)pow((float)((float)clockTime / 200.f), 2)));
					menuButtons[i].circleShape.setPosition(pos);
					menuButtons[i].textLable.setPosition(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius));
					menuButtons[i].clickRadius.centerXY = pos;
				}
			} else if(menuButtons[i].animateHover && !(menu_button.clickRadius.isHovered(mousePos))){
				if (clockTime < 2100) {
					Vector2f pos = menuButtons[i].circleShape.getPosition();
					pos.y = 400 + 200 * (i % 2) - 15.f *((float)(((float)clockTime + 141.f) / 200.f) / (float)exp((float)pow((float)(((float)clockTime + 141.f) / 200.f), 2)));
					menuButtons[i].circleShape.setPosition(pos);
					menuButtons[i].textLable.setPosition(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius));
					menuButtons[i].clickRadius.centerXY = pos;
				} else {
					menuButtons[i].animateHover = false;
				}
			}
		}
	}
}


WindowController::WindowController()
{

}

WindowController::~WindowController()
{

}
