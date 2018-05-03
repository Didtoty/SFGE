/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <engine/engine.h>
#include <engine/scene.h>
#include <graphics/graphics.h>
#include <input/input.h>
#include <python/python_engine.h>
#include <engine/config.h>
#include <audio/audio.h>
#include <engine/editor.h>
#include <graphics/sprite.h>
#include <physics/physics.h>
#include <engine/log.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <p2Collider.h>

int main()
{
	sfge::Engine engine;
	engine.Init(false, true);

	engine.GetSceneManager()->SetCurrentScene("data/scenes/test_robot_offset.scene");

	// engine.Start();
	sf::Clock clock;
	while (engine.running && engine.GetWindow() != nullptr)
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (engine.GetWindow() != nullptr && engine.GetWindow()->pollEvent(event))
		{
			engine.GetEditor()->ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				engine.running = false;
				engine.GetWindow()->close();
			}
		}
		if (!engine.running)
		{
			continue;
		}
		engine.GetPhysicsManager()->Update(dt);
		engine.GetInputManager()->Update(dt);
		engine.GetPythonManager()->Update(dt);

		engine.GetSceneManager()->Update(dt);

		engine.GetEditor()->Update(dt);
		if (engine.GetSceneManager()->IsSwitching())
		{
			engine.Collect();
		}
		engine.GetGraphicsManager()->Update(dt);
		engine.GetEditor()->Draw();
		engine.GetGraphicsManager()->Display();
	}
	engine.Destroy();

#if WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}