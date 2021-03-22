#include "PhysicsDebugDraw.h"

#include "Definitions.h"
#include "SFML/Graphics.hpp"

PhysicsDebugDraw::PhysicsDebugDraw(ZEngine::GameDataRef data) :
	_data(data)
{
}

void PhysicsDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexCount);

	for (int i = 0; i < vertexCount; i++) 
	{
		polygon.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
	}

	polygon.setOutlineColor(sf::Color::Red);
	polygon.setOutlineThickness(1.0f);

	_data->window.draw(polygon);

}

void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexCount);

	for (int i = 0; i < vertexCount; i++)
	{
		polygon.setPoint(i, sf::Vector2f(vertices[i].x * SCALE, vertices[i].y * SCALE));
	}

	polygon.setOutlineColor(sf::Color::Red);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineThickness(2.0f);

	_data->window.draw(polygon);
}

void PhysicsDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}

void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
}

void PhysicsDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void PhysicsDebugDraw::DrawTransform(const b2Transform& xf)
{
}

void PhysicsDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}
