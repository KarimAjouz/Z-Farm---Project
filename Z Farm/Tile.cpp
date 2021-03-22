#include "Tile.h"

Tile::Tile(ZEngine::GameDataRef data, b2World* worldRef, std::string name, std::string path, bool collision, sf::Vector2f pos, sf::IntRect frameRect) :
	_data(data),
	_sprite(sf::Sprite()),
	debugRect(sf::Vector2f(frameRect.width, frameRect.height))
{
	_data->assetManager.LoadTexture(name, path);
	_sprite.setTexture(_data->assetManager.GetTexture(name));
	_sprite.setTextureRect(frameRect);
	_sprite.setPosition(pos);
	_sprite.setOrigin(sf::Vector2f(frameRect.width / 2, frameRect.height / 2));
	_sprite.setScale(2.0f, 2.0f);





	if (collision)
		_collisionTag = CollisionTag::level;
	else
		_collisionTag = CollisionTag::background;

	GenPhysics(worldRef, frameRect);

	debugRect.setOrigin(sf::Vector2f(frameRect.width / 2, frameRect.height / 2));
	debugRect.setFillColor(sf::Color::Transparent);
	debugRect.setOutlineColor(sf::Color::Magenta);
	debugRect.setOutlineThickness(1.0f);
	debugRect.setPosition(tileBody->GetTransform().p.x * SCALE, tileBody->GetTransform().p.y * SCALE);
	debugRect.setScale(2.0f, 2.0f);

}

Tile::~Tile()
{
}

void Tile::Update(float dT)
{
}

void Tile::Draw()
{
	_data->window.draw(_sprite);
	//_data->window.draw(debugRect);
}

void Tile::GenPhysics(b2World* worldRef, sf::IntRect frameRect)
{
	b2BodyDef tileDef;
	tileDef.position = b2Vec2(_sprite.getPosition().x / SCALE, _sprite.getPosition().y / SCALE);
	tileDef.type = b2_kinematicBody;
	tileBody = worldRef->CreateBody(&tileDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox((frameRect.width * _sprite.getScale().x / 2) / SCALE, (frameRect.height * _sprite.getScale().y / 2 ) / SCALE, b2Vec2(0.0f, 0.0f), 0.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* fixture = tileBody->CreateFixture(&myFixtureDef);

	fixture->GetUserData().pointer = static_cast<int>(_collisionTag);
}
