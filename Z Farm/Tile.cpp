#include "Tile.h"

Tile::Tile(ZEngine::GameDataRef data, b2World* worldRef, std::string name, std::string path, bool collision, sf::Vector2f pos, sf::IntRect frameRect) :
	_data(data),
	sprite(sf::Sprite())
{
	_data->assetManager.LoadTexture(name, path);
	sprite.setTexture(_data->assetManager.GetTexture(name));
	sprite.setTextureRect(frameRect);
	sprite.setPosition(pos);
	sprite.setOrigin(sf::Vector2f(frameRect.width / 2, frameRect.height / 2));
	sprite.setScale(2.0f, 2.0f);

	if (collision)
		collisionTag = CollisionTag::level;
	else
		collisionTag = CollisionTag::background;

	GenPhysics(worldRef, frameRect);

}

Tile::~Tile()
{
}

void Tile::Update(float dT)
{
}

void Tile::Draw()
{
	_data->window.draw(sprite);
}

void Tile::GenPhysics(b2World* worldRef, sf::IntRect frameRect)
{
	b2BodyDef tileDef;
	tileDef.position = b2Vec2(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
	tileDef.type = b2_kinematicBody;
	tileBody = worldRef->CreateBody(&tileDef);
	tileBody->GetUserData().pointer = static_cast<int>(CollisionTag::tile);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox((frameRect.width * sprite.getScale().x / 2) / SCALE, (frameRect.height * sprite.getScale().y / 2 ) / SCALE, b2Vec2(0.0f, 0.0f), 0.0f);

	if (collisionTag == CollisionTag::level)
	{
		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.0f;
		myFixtureDef.shape = &polygonShape;
		b2Fixture* fixture = tileBody->CreateFixture(&myFixtureDef);
		fixture->GetUserData().pointer = static_cast<int>(collisionTag);
	}

}

void Tile::RemovePhysics()
{
	tileBody->DestroyFixture(tileBody->GetFixtureList());
	tileBody->GetWorld()->DestroyBody(tileBody);
}
