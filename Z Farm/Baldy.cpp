#include "Baldy.h"
#include "Definitions.h"
#include "Utilities.h"

#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>


Baldy::Baldy(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos, Room* myRoom) :
	_data(data),
	_animSys(&sprite, _data),
	_myRoom(myRoom),
	Enemy(data, world),
	_watchTimer(6.8f, false),
	_resetTimer(5.0f, false),
	_questionTimer(1.0f, false),
	_attackCooldown(3.0f, false),
	_attackDelay(0.3f, false)
{
	worldRef = world;
	_curSpeed = _walkSpeed;
	dialogueOffset = sf::Vector2f(30, -34);
	
	
	sprite.setPosition(pos);
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	sprite.setOrigin(sf::Vector2f(30, 34));

	hitbox = sf::RectangleShape(sf::Vector2f(30, 54));
	hitbox.setOrigin(15, 27);
	hitbox.setPosition(sprite.getPosition());
	hitbox.setScale(1.0, 1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Blue);
	hitbox.setOutlineThickness(1.0f);

	type = Type::baldy;

	InitAnimations();
	InitPhysics(pos);

	_animState = AnimState::idle;
	_AIState = BaldyState::watching;
	StartWatch();
	_watchTimer.Start();
	_animSys.SetAnimation("BaldyIdle");
	_animSys.Play();

	targetNodeCircle.setFillColor(sf::Color::Magenta);
	targetNodeCircle.setRadius(5.0f);
	Repath(_targetPosition);

	
}

Baldy::~Baldy()
{
}

void Baldy::Update(float dT)
{
	UpdateState();
	UpdateAnimations();

	_animSys.Update(dT);

	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	hitbox.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
	{
		Repath(sf::Vector2f(sf::Mouse::getPosition(_data->window)));
		SeekTarget(_targetPosition);
	}

	alertBubble.Update(dT, sprite.getPosition() + dialogueOffset);
}

void Baldy::Draw()
{
	_data->window.draw(sprite);
	//_data->window.draw(hitbox);

	if (_path.size() > 1)
	{
		for (int i = 0; i < _path.size() - 1; i++)
		{
			sf::Vertex line[2];
			line[0].position = _path[i]->GetNodeLocation();
			line[0].color = sf::Color::Red;
			line[1].position = _path[i + 1]->GetNodeLocation();
			line[1].color = sf::Color::Red;

			_data->window.draw(line, 2, sf::Lines);
		}
	}
	alertBubble.Draw();
	_data->window.draw(targetNodeCircle);
}

void Baldy::Hit()
{
}

void Baldy::Hit(sf::Vector2f playerPos)
{
	if (_animState != AnimState::death)
		_animState = AnimState::death;
}

void Baldy::Repath(sf::Vector2f pos)
{
	_targetPosition = ZEngine::Utilities::GetNearestNode(pos, _myRoom)->GetNodeLocation();
	_path = ZEngine::Utilities::PathFind(_targetPosition, &sprite, _myRoom);
	_animState = AnimState::moving;
	_AIState = BaldyState::patrolling;
}

void Baldy::UpdateAnimations()
{
	switch (_animState)
	{
		case AnimState::idle:
			if (_animSys.GetCurrentAnim() != "BaldyIdle")
			{
				_animSys.SetAnimation("BaldyIdle");
				_animSys.Play();
			}
			break;
		case AnimState::moving:
			if (_animSys.GetCurrentAnim() != "BaldyRun")
			{
				_animSys.SetAnimation("BaldyRun");
				_animSys.Play();
			}
			break;
		case AnimState::preJump:
			if (_animSys.GetCurrentAnim() != "BaldyPreJump")
			{
				_animSys.SetAnimation("BaldyPreJump");
				_animSys.Play();
			}
			break;
		case AnimState::jumping:
			if (_animSys.GetCurrentAnim() != "BaldyJump")
			{
				_animSys.SetAnimation("BaldyJump");
				_animSys.Play();
			}
			break;
		case AnimState::falling:
			if (_animSys.GetCurrentAnim() != "BaldyFall")
			{
				_animSys.SetAnimation("BaldyFall");
				_animSys.Play();
			}
			break;
		case AnimState::landing:
			if (_animSys.GetCurrentAnim() != "BaldyLand")
			{
				_animSys.SetAnimation("BaldyLand");
				_animSys.Play();
			}
			break;
	}
}

void Baldy::UpdateState()
{
	//switch (_animState)
	//{
	//	case AnimState::idle:
	//		break;
	//	case AnimState::moving:
	//		if (body->GetLinearVelocity().y > 0)
	//			_animState = AnimState::falling;
	//		break;
	//	case AnimState::preJump:
	//		if (_animSys.GetCurrentAnim() == "BaldyPreJump" && _animSys.Complete())
	//		{
	//			_animState = AnimState::jumping;
	//			Jump(10.0f);
	//		}
	//		break;
	//	case AnimState::jumping:
	//		if (body->GetLinearVelocity().y > 0)
	//			_animState = AnimState::falling;
	//		break;
	//	case AnimState::falling:
	//		if (footContacts > 0)
	//			_animState = AnimState::landing;
	//		break;
	//	case AnimState::landing:
	//		if (_animSys.GetCurrentAnim() == "BaldyLand" && _animSys.Complete())
	//			_animState = AnimState::idle;
	//		break;
	//}

	switch (_AIState)
	{
		case BaldyState::watching:
			if (_watchTimer.Complete())
				Patrol();

			if (alertBubble.UpdateState(CanSeePlayer(), &_questionTimer))
				_AIState = BaldyState::alert;


			break;
		case BaldyState::patrolling:
			if (SeekTarget(_targetPosition))
				StartWatch();

			if (alertBubble.UpdateState(CanSeePlayer(), &_questionTimer))
				_AIState = BaldyState::alert;

			break;
		case BaldyState::questioning:
			break;
		case BaldyState::alert:
			if (CanSeePlayer(&_lastSeenPlayerPos))
			{
				Repath(_lastSeenPlayerPos);
				_animState = AnimState::moving;
			}
			else if (!CanSeePlayer())
			{
				_resetTimer.Start();
				_AIState = BaldyState::resetting;
			}

			if (SeekTarget(_lastSeenPlayerPos))
				_animState = AnimState::idle;

			//Decide if attacking here

			for (std::pair<Agent*, int> agents : _nearbyAgents)
				if (agents.first->type == Agent::Type::player)
					BeginAttack(agents.second);

			break;
		case BaldyState::resetting:
			if (_resetTimer.Complete())
				_AIState = BaldyState::patrolling;
			else if (CanSeePlayer())
				_AIState = BaldyState::alert;

			break;
	}

}

void Baldy::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 63, 67);
	sf::Vector2f frameOrigin = sf::Vector2f(30, 34);
	_animSys.AddAnimation("BaldyIdle", BALDY_IDLE, 3.4f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyRun", BALDY_RUN, 1.4f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyPreJump", BALDY_PREJUMP, 0.1f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyKick", BALDY_KICK, 1.2f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyJump", BALDY_JUMP, 0.4f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyFall", BALDY_FALL, 0.2f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyLand", BALDY_LAND, 0.3f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyHit", BALDY_HIT, 1.0f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyDead", BALDY_DEAD, 0.4f, true, frameRect, frameOrigin);
}

void Baldy::InitPhysics(sf::Vector2f pos)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
	body = worldRef->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 5.0f;
	b2Vec2 verts[6];
	verts[0].Set(-15 / SCALE, -28 / SCALE);
	verts[1].Set(-15 / SCALE, 25 / SCALE);
	verts[2].Set(-5 / SCALE, 31 / SCALE);
	verts[3].Set(5 / SCALE, 31 / SCALE);
	verts[4].Set(15 / SCALE, 25 / SCALE);
	verts[5].Set(15 / SCALE, -28 / SCALE);
	polygonShape.Set(verts, 6);

	myFixtureDef.friction = 1.0f;
	myFixtureDef.restitution = 0.2f;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* baldyFixture = body->CreateFixture(&myFixtureDef);
	baldyFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemy);

	polygonShape.SetAsBox(10 / SCALE, 10 / SCALE, b2Vec2(0, (31.0f * abs(sprite.getScale().y)) / SCALE), 0);
	myFixtureDef.isSensor = true;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* footSensorFixture = body->CreateFixture(&myFixtureDef);
	footSensorFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemyFoot);

	b2CircleShape sensorShape;
	sensorShape.m_radius = 20 / SCALE;
	sensorShape.m_p = b2Vec2(45 / SCALE, 0);
	myFixtureDef.shape = &sensorShape;
	b2Fixture* rightSensorFixture = body->CreateFixture(&myFixtureDef);
	sensorShape.m_p = b2Vec2(-45 / SCALE, 0);
	b2Fixture* leftSensorFixture = body->CreateFixture(&myFixtureDef);
}

bool Baldy::SeekTarget(sf::Vector2f TargetPos)
{
	Node* nearestNode = ZEngine::Utilities::GetNearestNode(sprite.getPosition(), _myRoom);
	if (_path.size() > 0)
	{
		if (nearestNode == _path[_path.size() - 1])
			return true;
	}
	else
		return false;
	

	//If the nearest node is the top node in the path, remove it from the path.
	if (nearestNode == _path[0])
		_path.erase(_path.begin());

	//Get a pointer to the next node (the top node in the path)
	Node* targetNode = _path[0];

	targetNodeCircle.setPosition(targetNode->GetNodeLocation());


	//Move in the x-direction towards the node.
	if (targetNode->GetNodeLocation().x > nearestNode->GetNodeLocation().x)
		Move(1);
	else if (targetNode->GetNodeLocation().x < nearestNode->GetNodeLocation().x)
		Move(-1);

	//Decide if we need to jump.
	if (targetNode->GetNodeLocation().y < nearestNode->GetNodeLocation().y)
	{
		Jump(_jumpForce);
	}
	
	return false;
}

void Baldy::Move(int dir)
{
	b2Vec2 vel = body->GetLinearVelocity();
	float newSpeed;

	if (dir == -1)
		newSpeed = b2Max(vel.x - 0.3f, -_curSpeed);
	else if (dir == 1)
		newSpeed = b2Min(vel.x + 0.3f, _curSpeed);

	if ((dir == 1 && isFlipped) || (dir == -1 && !isFlipped))
		FlipSprite();

	float velChange = newSpeed - vel.x;
	float impulse = body->GetMass() * velChange; //disregard time factor

	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

void Baldy::Jump(float force)
{
	if (!_jumping && footContacts > 0 && _jumpTimeout < 0)
	{
		float impulse = body->GetMass() * force;
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.0f));
		body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
		_jumpTimeout = 15;
		_animState = AnimState::preJump;
	}
	else if (_jumpTimeout >= 0)
		_jumpTimeout--;
}

void Baldy::Patrol()
{
	FlipSprite();
	_AIState = BaldyState::patrolling;
	_animState = AnimState::moving;
	Node* targetNode = ZEngine::Utilities::GetNearestNode(sprite.getPosition(), _myRoom);
	sf::Vector2f targetNodePos = targetNode->GetNodeLocation();

	if (isFlipped)
	{
		targetNodePos.x -= 64;
		while (targetNode->GetNodeAtLocation(targetNodePos, &_myRoom->navMap) != nullptr)
		{
			targetNode = targetNode->GetNodeAtLocation(targetNodePos, &_myRoom->navMap);
			targetNodePos.x -= 64;
		}
	}
	else if (!isFlipped)
	{
		targetNodePos.x += 64;
		while (targetNode->GetNodeAtLocation(targetNodePos, &_myRoom->navMap) != nullptr)
		{
			targetNode = targetNode->GetNodeAtLocation(targetNodePos, &_myRoom->navMap);
			targetNodePos.x += 64;
		}
	}

	Repath(targetNode->GetNodeLocation());
}

void Baldy::StartWatch()
{
	_animState = AnimState::idle;
	_AIState = BaldyState::watching;
	_watchTimer.Start();
}

void Baldy::BeginAttack(int dir)
{
	if (dir == 1 && isFlipped || dir == -1 && !isFlipped)
		FlipSprite();

	_attackDelay.Start();
}

void Baldy::TestKick()
{
	if (isFlipped)
	{

	}
	else if (!isFlipped)
	{

	}
}