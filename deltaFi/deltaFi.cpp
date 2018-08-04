#include "stdafx.h"
#include "deltaFi.h"

using namespace std;
using namespace sf;

//Controls
Vector2i mousePos = Vector2i(0, 0);

//Update
Clock timerClock;
const float updateRate = 60;
float FPS = 0.f;
int timeElapsedSinceUpdate = 0;

//Window
struct WindowStruct {
	RenderWindow inst;
	function<void()> loop;
};

void windowLoop(sf::RenderWindow* w)
{
	sf::RenderWindow& window = *w;
	WindowController windowController;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mousePos = Mouse::getPosition();

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left){
					windowController.mouseClicked(mousePos, Mouse::Button::Left);
				}
				break;

			default:
				break;
			}
			

		}

		if (timerClock.getElapsedTime().asMicroseconds() >= (1000000.f / static_cast<float>(updateRate))) {
			timeElapsedSinceUpdate = timerClock.restart().asMicroseconds();
			FPS = static_cast<float>(1000000.f / timeElapsedSinceUpdate);

			window.clear(Color::Black);

			windowController.updateWindow(window);

			window.display();
		}

	}
}

int main() {
	WindowStruct mainWindow;

	//Constants
	const Vector2i windowSize = Vector2i(1500, 750);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	mainWindow.inst.create(VideoMode(windowSize.x, windowSize.y), "deltaFi", Style::Titlebar | Style::Close, settings);
	mainWindow.loop = bind(windowLoop, &mainWindow.inst);

	mainWindow.loop();

	return 0;
}