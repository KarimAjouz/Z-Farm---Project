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


	hitBox.setOrigin(30, 10);

	hitBox.setPosition(sprite.getPosition());
	hitBox.setSize(sf::Vector2f(30.0f, 10.0f) * sprite.getScale().x);

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
	//Define and set the physics body values
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
	bodyDef.type = b2_staticBody;
	body = _worldRef->CreateBody(&bodyDef);

	//Define, set, and add the primary fixture for the spike
	b2PolygonShape fixtureShape;
	fixtureShape.SetAsBox(30 / SCALE, 8 / SCALE);
	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.shape = &fixtureShape;
	b2Fixture* mainFixture = body->CreateFixture(&myFixtureDef);

	fixtureShape.SetAsBox(30 / SCALE, 10 / SCALE);
	b2Fixture* spikeFixture = body->CreateFixture(&myFixtureDef);
	spikeFixture->SetSensor(true);
	spikeFixture->GetUserData().pointer = static_cast<int>(CollisionTag::spike);
}