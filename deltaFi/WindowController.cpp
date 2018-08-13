#include "stdafx.h"
#include "WindowController.h"
#include "LanguageController.h"

using namespace sf;
using namespace std;

LanguageController lang;
UILib IL;

namespace variables
{
	bool isInitialized = false;

	bool windowHasFocus = false;

	enum state
	{
		menu = 0,
		particle = 1,
	};
	state currentState = menu;

	string currentLanguage = "en_US";
	//string currentLanguage = "sv_SE";

	//Fonts
	static map<string, sf::Font> loadedFonts;

	//Text labels
	static vector<sf::Text> textLabels;

	//Textures
	static map<string, sf::Texture> loadedTextures;

	//SoundsBuffers
	static map<string, sf::SoundBuffer> loadedSoundBuffers;

	//Sounds
	static vector<sf::Sound> sounds;
}

namespace menuVariables
{
	bool isInitialized = false;

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

	//Intro animation
	bool animateIntro = false;
	Clock animateIntroClock;
	Int32 currentTime;
	float yDisplacement;

	//Menu layout sizes
	int mainLogoDistance = 150;
	int mainLogoAmplitude = 20;
	int topRowDistance = 400;
	int deltaTopBot = 200;
	int distanceFromLeft = 400;

	//Simulation animation
	Clock simulationClock;
	int selectedSimulation;
	bool animateToSimulation = false;
	float simulationClockTime;
	int introFadeDuration = 1000;
	int alpha = 0;

	//Sprites
	vector<Sprite> loadedSprites;

	//CircleShapes
	vector<CircleShape> circleShapes;

	//Rectangles
	vector<RectangleShape> rectangleShapes;
}

namespace particleVariables
{
	bool isInitialized = false;

	//CircleShapes
	vector<sf::CircleShape> circleShapes;
}

using namespace variables;

void WindowController::initializeAssets(int state)
{
	UILib IL;

	switch (state)
	{
	case -1:
		if (variables::isInitialized) break;

		//General setup
		lang.selectLanguage(variables::currentLanguage);

		//Fonts
		loadedFonts["comfortaa"] = IL.loadFontFromMemory((void*)ComfortaaLight, ComfortaaLight_Size);
		loadedFonts["opensans"] = IL.loadFontFromMemory((void*)OpenSans, OpenSans_Size);

		//Textures
		loadedTextures["deltaFiLogo"] = IL.loadTextureFromMemory((void*)deltaFiLogo, deltaFiLogo_Size);
		loadedTextures["particleLogo"] = IL.loadTextureFromMemory((void*)particleLogo, particleLogo_Size);
		loadedTextures["particleLogo2"] = IL.loadTextureFromMemory((void*)particleLogo2, particleLogo2_Size);
		loadedTextures["particleLogo3"] = IL.loadTextureFromMemory((void*)particleLogo3, particleLogo3_Size);

		//SoundBuffers
		loadedSoundBuffers["menuLoop"] = IL.loadSoundBufferFromMemory((void*)menuLoop, menuLoop_Size);
		loadedSoundBuffers["mouseOver"] = IL.loadSoundBufferFromMemory((void*)mouseOverSFX, mouseOverSFX_Size);

		//Sounds
		sounds.push_back(sf::Sound(loadedSoundBuffers["menuLoop"]));
		sounds.push_back(sf::Sound(loadedSoundBuffers["mouseOver"]));

		sounds[0].setLoop(true);
		sounds[0].play();

		//FPS & UPS counter
		variables::textLabels.push_back(IL.newText(Vector2f(1427, 695), "FPS: ", &loadedFonts["opensans"], 20, Color::White, false));
		variables::textLabels.push_back(IL.newText(Vector2f(1490, 720), "UPS: ", &loadedFonts["opensans"], 20, Color::White, false));

		variables::isInitialized = true;
		break;

	case 0:
		if (menuVariables::isInitialized) break;

		//Menu
		menuVariables::loadedSprites.push_back(IL.newSprite(Vector2f(750, 200), &loadedTextures["deltaFiLogo"], Vector2f(0.8f, 0.8f), 0)); //Logo
		newMenuButton(lang.selectedLanguage.particle, Color(211, 164, 232, 200), "particleLogo", Vector2f(0.5f, 0.5f));
		newMenuButton(lang.selectedLanguage.planetary, Color(211, 164, 232, 200), "particleLogo2", Vector2f(0.5f, 0.5f));
		newMenuButton(lang.selectedLanguage.pendulum, Color(211, 164, 232, 200), "particleLogo3", Vector2f(0.5f, 0.5f));
		newMenuButton(lang.selectedLanguage.swing, Color(211, 164, 232, 200), "deltaFiLogo", Vector2f(0.3f, 0.3f));

		menuVariables::rectangleShapes.push_back(IL.newRectangle(sf::Vector2f(0, 0), sf::Vector2f(1500, 750), sf::Color(0, 0, 0, 0), 0, sf::Color::Black, 0, false));

		menuVariables::animateIntro = true;
		menuVariables::animateIntroClock.restart();

		menuVariables::isInitialized = true;
		break;

	case 1:
		if (particleVariables::isInitialized) break;

		//Particle
		particleVariables::circleShapes.push_back(IL.newCircleShape(Vector2f(300, 300), 50, 50, Color::Cyan, Color::Cyan, 5, 0));

		particleVariables::isInitialized = true;
		break;

	default:
		break;
	}
}

void WindowController::mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed)
{
	cout << "X: " << mousePos.x << " Y: " << mousePos.y << endl;

	for (menuVariables::menuButton menu_button : menuVariables::menuButtons)
	{
		if (menu_button.isHovered){
			menuVariables::animateIntro = false;
			menuVariables::animateToSimulation = true;
			menuVariables::simulationClock.restart();
			menuVariables::selectedSimulation = menu_button.index;
			return;
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

void WindowController::updateWindow(sf::RenderWindow& window, Vector2i mousePos, int FPS, int UPS)
{
	windowHasFocus = window.hasFocus();

	textLabels[0].setString("FPS: " + to_string(FPS));
	textLabels[1].setString("UPS: " + to_string(UPS));
	textLabels[1].setOrigin((int)(textLabels[1].getGlobalBounds().width), 0);

	for (Text text : textLabels) {
		window.draw(text);
	}

	switch (currentState)
	{
	case menu:
		
		if (menuVariables::animateIntro || menuVariables::animateToSimulation) menuAnimation(mousePos);
		if (currentState != menu) break;

		for (Sprite loaded_sprite : menuVariables::loadedSprites){
			window.draw(loaded_sprite);
		}

		for (menuVariables::menuButton menu_button : menuVariables::menuButtons){
			if (menu_button.isVisable){
				window.draw(menu_button.circleShape);
				window.draw(menu_button.textLable);
				window.draw(menu_button.icon);
			}
		}

		if (menuVariables::animateToSimulation) window.draw(menuVariables::rectangleShapes[0]);

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

void WindowController::newMenuButton(string text, Color hoverColor, string icon, Vector2f iconScale)
{
	using namespace menuVariables;
	menuButton button;
	sf::Vector2f pos;
	pos.y = topRowDistance + deltaTopBot * (menuButtons.size() % 2);
	pos.x = distanceFromLeft + distanceBetweenButtons * floor(menuButtons.size() / 2);

	button.circleShape = IL.newCircleShape(pos, menuButtonRadius, menuButtonCorners, Color::Black, menuButtonColor, menuButtonOutlineSize, 0);
	button.textLable = IL.newText(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius), text, &loadedFonts["opensans"] , menuButtonTextSize, Color(255, 255, 255, 0), true);
	button.index = menuButtons.size();
	button.isVisable = false;
	ClickRadius clickRadius;
	clickRadius.centerXY = pos;
	clickRadius.radius = menuButtonRadius + menuButtonOutlineSize;
	button.clickRadius = clickRadius;
	button.isHovered = false;
	button.hoverColor = hoverColor;
	button.hoverClock.restart();
	button.animateHover = false;
	button.icon = IL.newSprite(pos, &loadedTextures[icon], iconScale, 45);

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

	if (animateIntro) {
		currentTime = animateIntroClock.getElapsedTime().asMilliseconds();
		if (currentTime <= 5541) {

			yDisplacement = (mainLogoDistance - (float)(100.f * (float)(exp((float)(currentTime - 2400.f) / -1000.f))*(float)sin((float)(currentTime - 2400.f) / 1000.f)));
			loadedSprites[0].setPosition(Vector2f(750, yDisplacement));

			Color color = loadedSprites[0].getColor();
			color.a = 255 * currentTime / 5541;
			loadedSprites[0].setColor(color);
		}
		else {
			yDisplacement = (mainLogoDistance + mainLogoAmplitude * (float)sin((float)((currentTime + 742.f) / 1000.f)));
			loadedSprites[0].setPosition(Vector2f(750, yDisplacement));
		}
		if (currentTime >= 1700 && currentTime <= 5541 + 500.f * (menuButtons.size() - 1))
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
					pos.y = (topRowDistance + deltaTopBot * (i % 2) - (float)50 * (float)(exp((float)(currentTime - 2400.f - 500.f * i) / -1000.f))*(float)sin((float)(currentTime - 2400.f - 500.f * i) / 1000.f));
					menuButtons[i].circleShape.setPosition(pos);
					menuButtons[i].icon.setPosition(Vector2f(pos.x, ceil(pos.y)));
					menuButtons[i].textLable.setPosition(Vector2f(pos.x - 4, ceil(pos.y + 0.4f * menuButtonRadius)));

					Color color = menuButtonColor;
					color.a = menuButtonColor.a * (currentTime - (500.f * i) - 1700.f) / 3841.f;
					menuButtons[i].circleShape.setOutlineColor(color);
					menuButtons[i].icon.setColor(Color(255, 255, 255, 255 * (currentTime - (500.f * i) - 1700.f) / 3841.f));
					menuButtons[i].textLable.setFillColor(Color(255, 255, 255, color.a));
				}
			}
		}
		else if (currentTime > 5541 + 500.f * (menuButtons.size() - 1)) {
			int i = 0;
			for (menuButton menu_button : menuButtons)
			{
				i = menu_button.index;
				Int32 clockTime = menuButtons[i].hoverClock.getElapsedTime().asMilliseconds();
				if (!menu_button.isHovered && menu_button.clickRadius.isHovered(mousePos)) {
					if (windowHasFocus) sounds[1].play();
					menuButtons[i].circleShape.setOutlineColor(menu_button.hoverColor);
					menuButtons[i].isHovered = true;
					menuButtons[i].animateHover = true;
					menuButtons[i].hoverClock.restart();
				}
				else if (menu_button.isHovered && !(menu_button.clickRadius.isHovered(mousePos))) {
					menuButtons[i].circleShape.setOutlineColor(menuButtonColor);
					menuButtons[i].isHovered = false;
					menuButtons[i].hoverClock.restart();
				}
				else if (menu_button.isHovered && menu_button.clickRadius.isHovered(mousePos)) {
					if (menu_button.animateHover && clockTime < 141) {
						Vector2f pos = menuButtons[i].circleShape.getPosition();
						pos.y = (int)(topRowDistance + deltaTopBot * (i % 2) - 15.f *((float)((float)clockTime / 200.f) / (float)exp((float)pow((float)((float)clockTime / 200.f), 2))));
						menuButtons[i].circleShape.setPosition(pos);
						menuButtons[i].icon.setPosition(pos);
						menuButtons[i].textLable.setPosition(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius));
						menuButtons[i].clickRadius.centerXY = pos;
					}
				}
				else if (menuButtons[i].animateHover && !(menu_button.clickRadius.isHovered(mousePos))) {
					if (clockTime < 2100) {
						Vector2f pos = menuButtons[i].circleShape.getPosition();
						pos.y = int(topRowDistance + deltaTopBot * (i % 2) - 15.f *((float)(((float)clockTime + 141.f) / 200.f) / (float)exp((float)pow((float)(((float)clockTime + 141.f) / 200.f), 2))));
						menuButtons[i].circleShape.setPosition(pos);
						menuButtons[i].icon.setPosition(pos);
						menuButtons[i].textLable.setPosition(Vector2f(pos.x - 4, pos.y + 0.4f * menuButtonRadius));
						menuButtons[i].clickRadius.centerXY = pos;
					}
					else {
						menuButtons[i].animateHover = false;
					}
				}
			}
		}
	}

	if (animateToSimulation)
	{
		
		simulationClockTime = simulationClock.getElapsedTime().asMilliseconds();

		if (simulationClockTime <= introFadeDuration)
		{
			alpha = ceil(255.f * ((float)simulationClockTime) / (introFadeDuration));
			rectangleShapes[0].setFillColor(Color(0, 0, 0, alpha));
		}
		
		if (simulationClockTime >= introFadeDuration)
		{
			currentState = state(selectedSimulation + 1);
			animateToSimulation = false;
			initializeAssets(currentState);
		}
	}
}

WindowController::WindowController()
{

}

WindowController::~WindowController()
{

}
