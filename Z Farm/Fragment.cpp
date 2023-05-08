#include "Fragment.h"
#include "Definitions.h"
#include "Utilities.h"
#include "PhysicsComponent.h"

Fragment::Fragment(ZEngine::GameDataRef data, b2World* worldRef, sf::IntRect texRect, sf::Vector2f pos, sf::Vector2f forceDir) :
	m_Data(data),
	_worldRef(worldRef)
{
	sprite.setTexture(m_Data->assetManager.GetTexture("Box"));
	sprite.setTextureRect(texRect);
	sprite.setPosition(pos);
	sprite.setOrigin(texRect.width / 2, texRect.height / 2);
	sprite.setScale(1, 1);

	InitPhysics();

	sf::Vector2f force = sf::Vector2f(ZEngine::Utilities::Random(forceDir.x / 2, forceDir.x), -ZEngine::Utilities::Random(forceDir.y / 2, forceDir.y));

	force = ZEngine::Utilities::NormaliseVector(force) * 10.0f / SCALE;

	b2Vec2 b2Force = b2Vec2(force.x * 2 / 3, force.y * 2 / 3);

	body->ApplyLinearImpulseToCenter(b2Force, true);
}

Fragment::~Fragment()
{
}

void Fragment::Update(float dT)
{
	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	sprite.setRotation(body->GetTransform().q.GetAngle() * 180 / b2_pi);
}

void Fragment::Draw()
{
	m_Data->GameWindow.draw(sprite);
}

void Fragment::InitPhysics()
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((sprite.getPosition().x + sprite.getTextureRect().left) / SCALE, (sprite.getPosition().y + sprite.getTextureRect().top) / SCALE);

	bodyDef.type = b2_dynamicBody;
	bodyDef.userData.pointer = static_cast<int>(ECollisionTag::CT_Prop);
	body = _worldRef->CreateBody(&bodyDef);

	//Define, set, and add the primary fixture for the spike
	b2PolygonShape fixtureShape;
	fixtureShape.SetAsBox(sprite.getTextureRect().width / 2 / SCALE, sprite.getTextureRect().height / 2 / SCALE);
	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;

	myFixtureDef.filter.categoryBits = EEntityCategory::PROPS;
	myFixtureDef.filter.maskBits = EEntityCategory::LEVEL | EEntityCategory::PROPS;

	myFixtureDef.shape = &fixtureShape;
	b2Fixture* mainFixture = body->CreateFixture(&myFixtureDef);

	body->GetFixtureList()->SetDensity(0.25f);
	body->GetFixtureList()->SetFriction(0.7f);
}