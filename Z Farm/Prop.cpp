//#include "Prop.h"
//#include "Definitions.h"
//
//Prop::Prop()
//{
//
//}
//
//Prop::~Prop()
//{
//	
//}
//
//void Prop::InitPhysics(sf::IntRect collisionBox, b2World* worldRef)
//{
//	b2BodyDef bodyDef;
//	bodyDef.position = b2Vec2((sprite.getPosition().x + collisionBox.left) / SCALE, (sprite.getPosition().y + collisionBox.top) / SCALE);
//
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.userData.pointer = static_cast<int>(CollisionTag::prop);
//	body = worldRef->CreateBody(&bodyDef);
//
//	//Define, set, and add the primary fixture for the spike
//	b2PolygonShape fixtureShape;
//	fixtureShape.SetAsBox(collisionBox.width / SCALE, collisionBox.height / SCALE);
//	b2FixtureDef myFixtureDef;
//	myFixtureDef.density = 1.0f;
//
//	myFixtureDef.filter.categoryBits = _entityCategory::PROPS;
//	myFixtureDef.filter.maskBits = _entityCategory::LEVEL | _entityCategory::PROPS;
//
//	myFixtureDef.shape = &fixtureShape;
//	b2Fixture* mainFixture = body->CreateFixture(&myFixtureDef);
//}