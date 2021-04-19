#include "Spike.h"
#include "Definitions.h"

Spike::Spike(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos) :
	_data(data),
	_worldRef(worldRef)
{
	_data->assetManager.LoadTexture("Spikes", SPIKE_TRAP);
	sprite.setTexture(_data->assetManager.GetTexture("Spikes"));
	sprite.setScale(2.0f, 2.0f);
	sprite.setPosition(sf::Vector2f(pos.x, pos.y + 52));
	sprite.setOrigin(16, 26);


	hitbox.setOrigin(30, 10);

	hitbox.setPosition(sprite.getPosition());
	hitbox.setSize(sf::Vector2f(30.0f, 10.0f) * sprite.getScale().x);

	InitPhysics();

}

Spike::~Spike()
{
}

void Spike::Update(float dT)
{

}

void Spike::Draw()
{
	_data->window.draw(sprite);

}

void Spike::InitPhysics()
{
	// Call the base InitPhysics function to initialise the body.
	Obstacle::InitPhysics(sf::IntRect(0, 0, 30, 8), true, false, _worldRef);

	// Create the spike sensor fixture.
	b2FixtureDef myFixtureDef;
	b2PolygonShape fixtureShape;
	myFixtureDef.shape = &fixtureShape;
	fixtureShape.SetAsBox(30 / SCALE, 10 / SCALE);

	b2Fixture* spikeFixture = body->CreateFixture(&myFixtureDef);
	spikeFixture->SetSensor(true);
	spikeFixture->GetUserData().pointer = static_cast<int>(CollisionTag::spike);
}

void Spike::Hit()
{

}