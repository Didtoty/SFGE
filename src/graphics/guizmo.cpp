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

#include <graphics/guizmo.h>

#include <physics\physics.h>

#include <memory>

#include <iostream>

Guizmo::Guizmo(std::shared_ptr<sf::RenderWindow>& window) : m_Window(window)
{
}

Guizmo::~Guizmo()
{
}

void Guizmo::DrawRect(p2Vec2 pos, p2Vec2 size, p2Color color = p2Color(255, 255, 255, 255))
{
	if (m_Window == nullptr)
		return;

	sf::RectangleShape rectangle = sf::RectangleShape(sfge::meter2pixel(size * 2));
	rectangle.setPosition(sfge::meter2pixel(pos - size));
	rectangle.setFillColor(sf::Color::Magenta);
	(*m_Window).draw(rectangle);
}

void Guizmo::DrawLine(p2Vec2 from, p2Vec2 to, p2Color color = p2Color(0, 0, 0, 255))
{
	if (m_Window == nullptr)
		return;

	sf::Vertex vertices[2] =
	{
		sf::Vertex(sfge::meter2pixel(from), sf::Color(color.r, color.g, color.b, color.a)),
		sf::Vertex(sfge::meter2pixel(to), sf::Color(color.r, color.g, color.b, color.a))
	};

	(*m_Window).draw(vertices, 2, sf::Lines);
}

void Guizmo::DrawCircle(p2Vec2 pos, float r, p2Color color = p2Color(0, 0, 0, 255))
{
	if (m_Window == nullptr)
		return;

	sf::CircleShape circle(r);
	circle.setPosition(sfge::meter2pixel(pos));
	circle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));

	(*m_Window).draw(circle);
}
