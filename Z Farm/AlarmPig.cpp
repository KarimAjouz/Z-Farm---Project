//#include "AlarmPig.h"
//
//#include "Definitions.h"
//
//
//AlarmPig::AlarmPig(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos) :
//	_data(data),
//	_animSys(&sprite, _data),
//	Enemy(data, world)
//{
//	InitAnimations();
//
//	worldRef = world;
//	sprite.setPosition(pos);
//	sprite.setScale(-2.0f, 2.0f);
//	sprite.setOrigin(sf::Vector2f(20, 15));
//
//	dialogueOffset = sf::Vector2f(20, -15);
//
//	hitbox = sf::RectangleShape(sf::Vector2f(12, 12));
//	hitbox.setOrigin(6, 6);
//	hitbox.setPosition(sprite.getPosition());
//	hitbox.setScale(2.0f, 2.0f);
//	hitbox.setFillColor(sf::Color::Transparent);
//	hitbox.setOutlineColor(sf::Color::Blue);
//	hitbox.setOutlineThickness(1.0f);
//
//	type = Agent::Type::alarmPig;
//
//	InitPhysics(pos);
//
//	_animSys.SetAnimation("PigIdle");
//	_animSys.Play();
//}
//
//AlarmPig::~AlarmPig()
//{
//}
//
//void AlarmPig::Update(float dT)
//{
//	UpdateState();
//	UpdateAnimations();
//
//	_animSys.Update(dT);
//
//	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
//	hitbox.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 12));
//
//	alertBubble.Update(dT, sprite.getPosition() + dialogueOffset);
//}
//
//void AlarmPig::Draw()
//{
//	_data->GameWindow.draw(sprite);
//
//	alertBubble.Draw();
//}
//
//void AlarmPig::UpdateState()
//{
//	switch (_state)
//	{
//	case State::idle:
//		if (alertBubble.UpdateState(CanSeePlayer(), &questionTimer))
//			_state = State::alarmed;
//		break;
//	case State::hit:
//		if (_animSys.GetCurrentAnim() == "PigHit" && _animSys.Complete())
//			DestroyPig();
//		break;
//	case State::alarmed:
//
//		break;
//	}
//
//}
//
//void AlarmPig::UpdateAnimations()
//{
//	switch (_state)
//	{
//		case State::idle:
//			if (_animSys.GetCurrentAnim() != "PigIdle")
//			{
//				_animSys.SetAnimation("PigIdle");
//				_animSys.Play();
//			}
//			break;
//		case State::hit:
//			if (_animSys.GetCurrentAnim() != "PigHit")
//			{
//				_animSys.SetAnimation("PigHit");
//				_animSys.Play();
//			}
//			break;
//		case State::alarmed:
//			if (_animSys.GetCurrentAnim() != "PigAlarm")
//			{
//				_animSys.SetAnimation("PigAlarm");
//				_animSys.Play();
//			}
//			break;
//	}
//
//}
//
//void AlarmPig::InitAnimations()
//{
//	sf::IntRect frameRect = sf::IntRect(0, 0, 34, 28);
//	sf::Vector2f frameOrigin = sf::Vector2f(20, 12);
//	_animSys.AddAnimation("PigIdle", PIG_IDLE, 1.1f, true, frameRect, frameOrigin);
//	_animSys.AddAnimation("PigHit", PIG_DEATH, 1.1f, false, frameRect, frameOrigin);
//	_animSys.AddAnimation("PigAlarm", PIG_ALARM, 0.6f, true, frameRect, frameOrigin);
//}
//
//void AlarmPig::InitPhysics(sf::Vector2f pos)
//{
//	b2BodyDef bodyDef;
//	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
//	bodyDef.type = b2_dynamicBody;
//	body = worldRef->CreateBody(&bodyDef);
//	body->SetFixedRotation(true);
//
//	b2CircleShape circleShape;
//	circleShape.m_radius = 17 / SCALE;
//	circleShape.m_p = b2Vec2(0, 17 / 2 / SCALE);
//
//	b2FixtureDef myFixtureDef;
//	myFixtureDef.density = 1.0f;
//
//	myFixtureDef.friction = 0.4f;
//	myFixtureDef.restitution = 0.5f;
//	myFixtureDef.shape = &circleShape;
//	b2Fixture* pigFixture = body->CreateFixture(&myFixtureDef);
//	pigFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemy);
//}
//
//void AlarmPig::DestroyPig()
//{
//	//_worldRef->DestroyBody(body);
//	isMarked = true;
//}
//
//void AlarmPig::Hit()
//{
//	if (_state != State::hit)
//	{
//		_state = State::hit;
//	}
//}
//
//void AlarmPig::Hit(sf::Vector2f playerPos)
//{
//	if (_state != State::hit)
//	{
//		if (playerPos.x < sprite.getPosition().x)
//		{
//			if (isFlipped)
//				FlipSprite();
//
//			body->ApplyLinearImpulseToCenter(b2Vec2(3.0f, -3.0f), true);
//		}
//
//		if (playerPos.x > sprite.getPosition().x)
//		{
//			if (!isFlipped)
//				FlipSprite();
//
//			body->ApplyLinearImpulseToCenter(b2Vec2(-3.0f, -3.0f), true);
//		}
//
//		_state = State::hit;
//	}
//}