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

#ifndef SFGE_GUIZMO_H
#define SFGE_GUIZMO_H

#include <p2vector.h>
#include <SFML\Graphics.hpp>
#include <p2guizmo.h>

#include <memory>

class Guizmo : p2Guizmo{
public:
	Guizmo(std::shared_ptr<sf::RenderWindow>& window);
	~Guizmo();

	void DrawRect(p2Vec2 pos, p2Vec2 size, p2Color color);
	void DrawLine(p2Vec2 from, p2Vec2 to, p2Color color);
	void DrawCircle(p2Vec2 pos, float r, p2Color color);

private: 
	std::shared_ptr<sf::RenderWindow> m_Window;
};

#endif /* SFGE_GUIZMO_H */