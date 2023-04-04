//#include "RopeSegment.h"
//#include "Definitions.h"
//#include "Utilities.h"
//
//#include <iostream>
//
//RopeSegment::RopeSegment(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos) :
//	_data(data)
//{
//	_data->assetManager.LoadTexture("RopeSegment", CHAIN_LINK_TEX);
//	worldRef = world;
//
//	sprite.setTexture(_data->assetManager.GetTexture("RopeSegment"));
//	sprite.setOrigin(4, 17);
//	sprite.setPosition(pos);	
//	sprite.setTextureRect(sf::IntRect(0, 0, 8, 30));
//
//
//	hitbox.setSize(sf::Vector2f(8, 31));
//	hitbox.setOrigin(4, 15);
//	hitbox.setScale(sprite.getScale());
//	hitbox.setPosition(sprite.getPosition());
//
//	type = Obstacle::Type::box;
//
//	InitPhysics();
//}
//
//RopeSegment::~RopeSegment()
//{
//}
//
//void RopeSegment::Update(float dT)
//{
//	sprite.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y) * SCALE);
//	sprite.setRotation(ZEngine::Utilities::RadToDeg(body->GetAngle()));
//
//}
//
//void RopeSegment::Draw()
//{
//	_data->GameWindow.draw(sprite);
//}
//
//void RopeSegment::InitPhysics()
//{
//	sf::IntRect collisionBox = sf::IntRect(0, 0, hitbox.getSize().x, hitbox.getSize().y);
//	b2BodyDef bodyDef;
//	bodyDef.position = b2Vec2((sprite.getPosition().x + collisionBox.left) / SCALE, (sprite.getPosition().y) / SCALE);
//
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
//	bodyDef.linearDamping = 0.5f;
//
//	body = worldRef->CreateBody(&bodyDef);
//
//	//Define, set, and add the primary fixture for the spike
//	b2PolygonShape fixtureShape;
//	fixtureShape.SetAsBox(collisionBox.width / 2 / SCALE, collisionBox.height / 2 / SCALE);
//	b2FixtureDef myFixtureDef;
//
//	myFixtureDef.density = 1.0f;
//	myFixtureDef.isSensor = true;
//	myFixtureDef.userData.pointer = static_cast<int>(CollisionTag::interactable);
//
//	myFixtureDef.filter.categoryBits = _entityCategory::INTERACTABLE;
//	myFixtureDef.filter.maskBits = _entityCategory::LEVEL | _entityCategory::OBSTACLES | _entityCategory::PLAYERINTERACT | _entityCategory::DAMAGE;
//
//	myFixtureDef.shape = &fixtureShape;
//	
//	b2RevoluteJointDef myJointDef = b2RevoluteJointDef();
//	myJointDef.bodyA = body;
//
//	b2Vec2 testPosition = body->GetPosition();
//	testPosition.y -= (12.0f) / SCALE;
//	for (b2Body* testBody = worldRef->GetBodyList(); testBody; testBody = testBody->GetNext())
//	{
//		//do something with the body 'b'
//
//		if (testBody->GetUserData().pointer == static_cast<int>(CollisionTag::level) || testBody->GetUserData().pointer == static_cast<int>(CollisionTag::box));
//		{
//			for (b2Fixture* testFixture = testBody->GetFixtureList(); testFixture; testFixture = testFixture->GetNext())
//			{
//				if (testFixture->TestPoint(testPosition))
//				{
//					myJointDef.bodyB = testBody;
//					b2Vec2 jointPosAnchorB = testBody->GetLocalPoint(testPosition);
//					myJointDef.localAnchorB.Set(jointPosAnchorB.x, jointPosAnchorB.y);
//					break;
//				}
//			}
//		}
//	}
//
//	if (myJointDef.bodyB == nullptr)
//	{
//		std::cout << "Error: RopeSegment::InitPhysics --> bodyB is invalid!" << std::endl;
//		return;
//	}
//
//	myJointDef.collideConnected = false;
//	myJointDef.localAnchorA.Set(0, - (collisionBox.height / 2) / SCALE);
//	b2Fixture* mainFixture = body->CreateFixture(&myFixtureDef);
//
//	b2Joint* revoluteJoint = worldRef->CreateJoint(&myJointDef);
//
//
//}
