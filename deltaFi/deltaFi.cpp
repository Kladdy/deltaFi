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
int UPS = 0;
int timeElapsedSinceUpdate = 0;

//Window
struct WindowStruct {
	RenderWindow inst;
	function<void()> loop;
};

void windowLoop(RenderWindow* w)
{
	RenderWindow& window = *w;
	WindowController windowController;
	windowController.initializeAssets(-1);
	windowController.initializeAssets(0);

	while (window.isOpen())
	{
		if (timerClock.getElapsedTime().asMicroseconds() >= (1000000.f / static_cast<float>(updateRate))) {
			timeElapsedSinceUpdate = timerClock.restart().asMicroseconds();
			FPS = static_cast<float>(1000000.f / timeElapsedSinceUpdate);
			UPS = round(((float)(UPS * FPS) / 1000.f)) * 1000.f;

			mousePos = Mouse::getPosition(window);

			Event event;
			while (window.pollEvent(event))
			{
				if (window.hasFocus()) {
					switch (event.type)
					{
					case Event::Closed:
						window.close();
						break;

					case Event::MouseButtonPressed:
						if (event.mouseButton.button == Mouse::Left) {
							windowController.mouseClicked(mousePos, Mouse::Button::Left);
						}
						break;

					case Event::KeyPressed:
						windowController.keyPressed(event.key.code, event.key.control, event.key.alt, event.key.shift, event.key.system);
						break;

					default:
						break;
					}
				}
			}

			window.clear(Color::Black);

			windowController.updateWindow(window, mousePos, round(FPS), UPS);
			UPS = 0;

			window.display();
		}

		UPS++;
	}
}

int main() {
	WindowStruct mainWindow;

	const Vector2i windowSize = Vector2i(1500, 750);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	mainWindow.inst.create(VideoMode(windowSize.x, windowSize.y), "deltaFi", Style::Titlebar | Style::Close, settings);
	mainWindow.loop = bind(windowLoop, &mainWindow.inst);

	mainWindow.loop();

	return 0;
}