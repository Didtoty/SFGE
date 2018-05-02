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

#define MIN_RANGE_TOP 100
#define MAX_RANGE_BOTTOM 500
#define MIN_RANGE_LEFT 100
#define MAX_RANGE_RIGHT 500

#define MIN_SPEED_X -15
#define MAX_SPEED_X 15
#define MIN_SPEED_Y -15
#define MAX_SPEED_Y 15

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
#include <SFML/Graphics.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

int main()
{
	sfge::Engine engine;
	engine.Init(false, true);

	engine.GetSceneManager()->SetCurrentScene("data/scenes/test_quadtree.scene");
	p2World* currentWorld = engine.GetPhysicsManager()->GetWorld();

	srand(time(NULL));

	for (auto& body : currentWorld->GetBodies())
	{
		body->SetPosition(sfge::pixel2meter(sf::Vector2f(rand() % (MAX_RANGE_RIGHT - MIN_RANGE_TOP) + MIN_RANGE_TOP, rand() % (MAX_RANGE_BOTTOM - MIN_RANGE_LEFT) + MIN_RANGE_LEFT)));
		body->SetLinearVelocity(sfge::pixel2meter(sf::Vector2f(rand() % MAX_SPEED_X + MIN_SPEED_X, rand() % MAX_SPEED_Y + MIN_SPEED_Y)));
	}

	// engine.Start();
	sf::Clock clock;
	while (engine.running && engine.GetWindow() != nullptr)
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (engine.GetWindow() != nullptr && engine.GetWindow()->pollEvent(event))
		{
			//ImGui::SFML::ProcessEvent(event);
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

		// If the bodies goes too far, we swap their speed to come back into the scene
		engine.GetPhysicsManager()->Update(dt);
		for (auto& body : currentWorld->GetBodies())
		{
			sf::Vector2f pos = sfge::meter2pixel(body->GetPosition());
			p2Vec2 v = body->GetLinearVelocity();
			if (pos.x < MIN_RANGE_LEFT && v.x < 0.0f)
			{
				body->SetLinearVelocity(p2Vec2(-v.x, v.y));
			}
			else if (pos.x > MAX_RANGE_RIGHT && v.x > 0.0f)
			{
				body->SetLinearVelocity(p2Vec2(-v.x, v.y));
			}
			if (pos.y < MIN_RANGE_TOP && v.y < 0.0f)
			{
				body->SetLinearVelocity(p2Vec2(v.x, -v.y));
			}
			else if (pos.y > MAX_RANGE_BOTTOM && v.y > 0.0f)
			{
				body->SetLinearVelocity(p2Vec2(v.x, -v.y));
			}
		}

		//ImGui::EndFrame();
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
	//ImGui::SFML::Shutdown();
	engine.Destroy();

#if WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}