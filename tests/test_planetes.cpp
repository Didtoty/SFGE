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
#include <graphics/graphics.h>
#include <graphics/shape.h>
#include <engine/log.h>
#include <engine/game_object.h>
#include <utility/json_utility.h>

int main()
{
	sfge::Engine engine;
	engine.Init(true);

	auto graphicsManager = engine.GetGraphicsManager();

	json gameObjectJson =
	{
			{"name", "PlanetesTest"},
			{"components",
					{
							{
									{"type", 3},
									{"shape_type",(int)sfge::ShapeType::CIRCLE},
									{"position", {400, 300}},
									{"radius", 40.0}
							},
							{
									{"type", 3},
									{"shape_type",(int)sfge::ShapeType::CIRCLE },
									{"position", {600, 150}},
									{ "radius", 10.0}
							}
					}
			}
	};


	auto gameObject = sfge::GameObject::LoadGameObject(engine, gameObjectJson);
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Shape");

	// CE QU'IL FAUT FAIRE
	/*
	* Créer un soleil et lui donner une masse
	* Créer des planètes a des positions et vitesse précises/aléatoires
	* Prédéfinir la vitesse de la planète avec :
	* p2Vec2 r = p.position - sun.getPosition();
	* p.linearVelocity = p2Vec2(-r.Normalized().x, r.Normalized.y) * Mass_Sun / r.getMagnitude * r.getMagnitude()
	* 
	*
	*/



	sf::Clock clock;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// clear the window with black color
		window.clear(sf::Color::Black);

		graphicsManager->GetShapeManager()->Draw(window);

		// end the current frame
		window.display();
	}
	engine.Destroy();

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}

