#include "Fragment.h"
#include "Definitions.h"

Fragment::Fragment(ZEngine::GameDataRef data, b2World* worldRef, sf::IntRect texRect, sf::Vector2f pos) :
	_data(data),
	_worldRef(worldRef)
{
	sprite.setTexture(_data->assetManager.GetTexture("Box"));
	sprite.setTextureRect(texRect);
	sprite.setPosition(pos);
	sprite.setOrigin(texRect.width / 2, texRect.height / 2);
	sprite.setScale(2, 2);

	InitPhysics();

}

Fragment::~Fragment()
{

}

void Fragment::Update(float dT)
{
	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	sprite.setRotation( body->GetTransform().q.GetAngle() * 180 / b2_pi);
}

void Fragment::Draw()
{
	_data->window.draw(sprite);
}

void Fragment::InitPhysics()
{
	Prop::InitPhysics(sf::IntRect(0, 0, sprite.getTextureRect().width, sprite.getTextureRect().height), _worldRef);

	body->GetFixtureList()->SetDensity(1.0f);
	
}