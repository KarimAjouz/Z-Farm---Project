//#include "Fragment.h"
//#include "Definitions.h"
//#include "Utilities.h"
//
//Fragment::Fragment(ZEngine::GameDataRef data, b2World* worldRef, sf::IntRect texRect, sf::Vector2f pos, sf::Vector2f forceDir) :
//	_data(data),
//	_worldRef(worldRef)
//{
//	sprite.setTexture(_data->assetManager.GetTexture("Box"));
//	sprite.setTextureRect(texRect);
//	sprite.setPosition(pos);
//	sprite.setOrigin(texRect.width / 2, texRect.height / 2);
//	sprite.setScale(2, 2);
//
//	InitPhysics();
//
//	
//	
//	sf::Vector2f force = sf::Vector2f(ZEngine::Utilities::Random(forceDir.x / 2, forceDir.x), ZEngine::Utilities::Random(-20, -40));
//
//	force = ZEngine::Utilities::NormaliseVector(force) * 2.0f;
//
//	b2Vec2 b2Force = b2Vec2(force.x * 2 / 3, force.y * 2 / 3);
//	
//
//	body->ApplyLinearImpulseToCenter(b2Force, true);
//
//}
//
//Fragment::~Fragment()
//{
//
//}
//
//void Fragment::Update(float dT)
//{
//	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
//	sprite.setRotation(body->GetTransform().q.GetAngle() * 180 / b2_pi);
//}
//
//void Fragment::Draw()
//{
//	_data->GameWindow.draw(sprite);
//}
//
//void Fragment::InitPhysics()
//{
//
//	b2BodyDef bodyDef;
//	bodyDef.position = b2Vec2((sprite.getPosition().x + sprite.getTextureRect().left) / SCALE, (sprite.getPosition().y + sprite.getTextureRect().top) / SCALE);
//
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.userData.pointer = static_cast<int>(CollisionTag::prop);
//	body = _worldRef->CreateBody(&bodyDef);
//
//	//Define, set, and add the primary fixture for the spike
//	b2PolygonShape fixtureShape;
//	fixtureShape.SetAsBox(sprite.getTextureRect().width / SCALE, sprite.getTextureRect().height / SCALE);
//	b2FixtureDef myFixtureDef;
//	myFixtureDef.density = 1.0f;
//
//	myFixtureDef.filter.categoryBits = _entityCategory::PROPS;
//	myFixtureDef.filter.maskBits = _entityCategory::LEVEL | _entityCategory::PROPS;
//
//	myFixtureDef.shape = &fixtureShape;
//	b2Fixture* mainFixture = body->CreateFixture(&myFixtureDef);
//
//	body->GetFixtureList()->SetDensity(0.25f);
//	body->GetFixtureList()->SetFriction(0.7f);
//	
//}