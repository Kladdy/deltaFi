#include "stdafx.h"
#include "ParticleController.h"

using namespace std;
using namespace sf;

UILib pc_IL;

namespace variables
{
	bool pc_isInitialized = false;

	bool animateIntro = false;;
	bool animateOutro = false;
	Clock animationClock;
	Int32 currentTime = 0;
	int fadeDuration = 1000;
	int alpha = 0;

	//Fonts
	static map<string, sf::Font> loadedFonts;

	//Text labels
	static vector<sf::Text> textLabels;

	//Textures
	static map<string, sf::Texture> loadedTextures;

	//SoundsBuffers
	static map<string, sf::SoundBuffer> loadedSoundBuffers;

	//Sounds
	static map<string, sf::Sound> sounds;

	//Sprites
	vector<Sprite> loadedSprites;

	//CircleShapes
	vector<CircleShape> circleShapes;

	//Rectangles
	vector<RectangleShape> rectangleShapes;
}

using namespace variables;

void ParticleController::initializeAssets()
{
	animateIntro = true;
	animationClock.restart();

	rectangleShapes.push_back(pc_IL.newRectangle(sf::Vector2f(0, 0), sf::Vector2f(1500, 750), sf::Color(0, 0, 0, 255), 0, sf::Color::Black, 0, false));

	pc_isInitialized = true;
}

void ParticleController::mouseClicked(sf::Vector2i mousePos, sf::Mouse::Button buttonPressed)
{

}

void ParticleController::keyPressed(sf::Keyboard::Key key, bool control, bool alt, bool shift, bool system)
{
	
}

void ParticleController::updateWindow(sf::RenderWindow& window, sf::Vector2i mousePos)
{
	if (!pc_isInitialized) initializeAssets();

	if (animateIntro || animateOutro) {
		fadeAnimatíon();
		window.draw(rectangleShapes[0]);
	}

}

void ParticleController::fadeAnimatíon()
{
	currentTime = animationClock.getElapsedTime().asMilliseconds();

	if (animateIntro)
	{
		if (currentTime <= fadeDuration)
		{
			alpha = 255 - ceil(255.f * ((float)currentTime) / (fadeDuration));
			rectangleShapes[0].setFillColor(Color(0, 0, 0, alpha));
			return;
		}

		animateIntro = false;
	} else if (animateOutro) {
		if (currentTime <= fadeDuration)
		{
			alpha = ceil(255.f * ((float)currentTime) / (fadeDuration));
			rectangleShapes[0].setFillColor(Color(0, 0, 0, alpha));
			return;
		}

		animateOutro = false;
	}
}


ParticleController::ParticleController()
{
}


ParticleController::~ParticleController()
{
}
