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

#include <p2physics.h>

#include <physics/body2d.h>
#include <physics/physics.h>
#include <engine/game_object.h>
#include <engine/transform.h>

namespace sfge
{

void Body2d::Init()
{
}

void Body2d::Update(float dt)
{
	m_GameObject->GetTransform()->SetPosition(meter2pixel(m_Body->GetPosition()));
	m_GameObject->GetTransform()->SetEulerAngle(m_Body->GetAngle());
}

p2Body * Body2d::GetBody()
{
	return m_Body;
}


void Body2d::SetVelocity(p2Vec2 v)
{
	if (m_Body)
	{
		m_Body->SetLinearVelocity(v);
	}
}

p2Vec2 Body2d::GetVelocity()
{
	if (m_Body != nullptr)
	{
		return m_Body->GetLinearVelocity();
	}
	return p2Vec2();
}

void Body2d::ApplyForce(p2Vec2 v)
{
	if (m_Body != nullptr)
		m_Body->ApplyForce(v);
}

float Body2d::GetMass()
{
	if (m_Body != nullptr)
		return m_Body->GetMass();
	return 0.0f;
}

Body2d * Body2d::LoadBody2d(Engine & engine, GameObject * gameObject, json& componentJson)
{
	auto physicsManager = engine.GetPhysicsManager();
	if (physicsManager->GetWorld() == nullptr)
	{
		return nullptr;
	}
	p2World* world = physicsManager->GetWorld();
	
	p2BodyDef bodyDef;

	bodyDef.type = p2BodyType::DYNAMIC;

	if (CheckJsonNumber(componentJson, "body_type"))
	{
		bodyDef.type = componentJson["body_type"];
	}
	bodyDef.position = pixel2meter(gameObject->GetTransform()->GetPosition());
	bodyDef.angle = gameObject->GetTransform()->GetEulerAngle();
	if (CheckJsonParameter(componentJson, "offset", json::value_t::array))
	{
		if (componentJson["offset"].size() == 2)
		{
			bodyDef.position += pixel2meter(sf::Vector2f(componentJson["offset"]["x"], componentJson["offset"]["y"]));
		}
	}

	if (CheckJsonParameter(componentJson, "velocity", json::value_t::array))
	{
		p2Vec2 newVelocity;
		if (IsJsonValueNumeric(componentJson["velocity"][0]))
		{
			newVelocity.x = componentJson["velocity"][0];
		}
		if (IsJsonValueNumeric(componentJson["velocity"][1]))
		{
			newVelocity.y = componentJson["velocity"][1];
		}
		bodyDef.linearVelocity = newVelocity;
	}

	if (CheckJsonNumber(componentJson, "mass"))
	{
		bodyDef.mass = componentJson["mass"];
	}

	if (CheckJsonNumber(componentJson, "gravity_scale"))
	{
		bodyDef.gravityScale = componentJson["gravity_scale"];
	}

	p2Body* body = world->CreateBody(&bodyDef);
	Body2d* bodyComponent = new Body2d(gameObject);

	bodyComponent->m_Body = body;
	physicsManager->m_Bodies.push_back(bodyComponent);
	return bodyComponent;
}

}

