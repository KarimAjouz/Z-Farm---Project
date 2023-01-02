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
	std::cout << "BALDY MASS: " << body->GetMass() << std::endl;

	_animState = AnimState::idle;
	_AIState = BaldyAIState::passive;
	_state = BaldyState::idle;
	_watchTimer.Start();
	_animSys.SetAnimation("BaldyIdle");
	_animSys.Play();


	_navComponent = new AgentNavigation(_data);

	targetNodeCircle.setFillColor(sf::Color::Magenta);
	targetNodeCircle.setRadius(5.0f);

	_jumpTimeout = 15;
	//Repath(_targetPosition);
}

Baldy::~Baldy()
{
	delete _navComponent;
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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
	{
		//Jump(_jumpForce);
	}

	if (_jumpTimeout >= 0 && footContacts > 0)
	{
		_jumpTimeout--;
	}
	else
	{
		if (footContacts > 0)
			_jumping = false;
	}

	if (footContacts < 0)
		std::cout << "LIN VEL X: " << body->GetLinearVelocity().x << " Y: " << body->GetLinearVelocity().y << std::endl;

	alertBubble.Update(dT, sprite.getPosition() + dialogueOffset);
}

void Baldy::Draw()
{
	_data->window.draw(sprite);
	//_data->window.draw(hitbox);

	if (_navComponent->Path.size() > 1)
	{
		for (int i = 0; i < _navComponent->Path.size() - 1; i++)
		{
			sf::Vertex line[2];
			line[0].position = _navComponent->Path[i]->GetNodeLocation();
			line[0].color = sf::Color::Red;
			line[1].position = _navComponent->Path[i + 1]->GetNodeLocation();
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
	_navComponent->GeneratePath(_targetPosition, &sprite, _myRoom);
	_animState = AnimState::moving;
	_state = BaldyState::moving;
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

	sf::Vector2f playerPos = sf::Vector2f(playerBody->GetPosition().x / SCALE, playerBody->GetPosition().y / SCALE);
	sf::Vector2f deltaPos = playerPos - sprite.getPosition();
	float deltaPosMagSquared = deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y;

	switch (_AIState)
	{
		case BaldyAIState::passive:
			switch (_state)
			{
				case BaldyState::idle:
					if (_watchTimer.Complete())
					{
						Patrol();
					}
					break;
				case BaldyState::moving:
					if (SeekTarget(_targetPosition))
					{
						StartWatch();
					}
					break;
				default:
					std::cout << "BALDY AI STATE: " << _AIStateStrings[(int)_AIState] << " does not handle state: " << _StateStrings[(int)_state] << std::endl;
					break;
			}
			break;
		case BaldyAIState::questioning:
			switch (_state)
			{
				case BaldyState::idle:
					if (_watchTimer.Complete())
					{
						ReturnHome();
					}
					break;
				case BaldyState::moving:
					if (SeekTarget(_targetPosition))
					{
						StartWatch();
					}
					break;
				default:
					std::cout << "BALDY AI STATE: " << _AIStateStrings[(int)_AIState] << " does not handle state: " << _StateStrings[(int)_state] << std::endl;
					break;
			}
			break;
		case BaldyAIState::alert:
			switch (_state)
			{
				case BaldyState::moving:
					SeekTarget(playerPos);

					if (deltaPosMagSquared < _MaxAttackTriggerDistanceSquared)
					{
						int dir = 1;
						if (deltaPos.x < 0)
							dir = -1;

						BeginAttack(dir);
					}
					break;
				case BaldyState::attacking:

					break;
				default:
					std::cout << "BALDY AI STATE: " << _AIStateStrings[(int)_AIState] << " does not handle state: " << _StateStrings[(int)_state] << std::endl;
					break;
			}
		case BaldyAIState::returning:
		
			break;
	}


	if (alertBubble.UpdateState(CanSeePlayer(), &_questionTimer))
		_state = BaldyState::wary;
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
	if (_navComponent->Path.size() > 0)
	{
		if (nearestNode == _navComponent->Path[_navComponent->Path.size() - 1])
			return true;
	}
	else
		return false;
	

	//If the nearest node is the top node in the path, remove it from the path.
	if (nearestNode == _navComponent->Path[0])
		_navComponent->Path.erase(_navComponent->Path.begin());

	//Get a pointer to the next node (the top node in the path)
	Node* nextPathStep = _navComponent->Path[0];
	Node::Edge nextEdge = _navComponent->GetEdge(nearestNode, nextPathStep, _myRoom);

	targetNodeCircle.setPosition(nextPathStep->GetNodeLocation());


	//Move in the x-direction towards the node.
	switch (nextEdge.type)
	{
		case Node::Edge::Type::walk:
			if (nextPathStep->GetNodeLocation().x > nearestNode->GetNodeLocation().x)
				Move(1);
			else if (nextPathStep->GetNodeLocation().x < nearestNode->GetNodeLocation().x)
				Move(-1);
			break;
		case Node::Edge::Type::drop:
			if (nextPathStep->GetNodeLocation().x > nearestNode->GetNodeLocation().x)
				Move(1);
			else if (nextPathStep->GetNodeLocation().x < nearestNode->GetNodeLocation().x)
				Move(-1);
			break;
		case Node::Edge::Type::invalid:
			Repath(TargetPos);
			break;
		case Node::Edge::Type::jump:
			sf::Vector2f jumpVelocity = nextEdge.JumpTrajectory.startVel;
			Jump(jumpVelocity / (SCALE));
			break;
	}
	
	return false;
}

void Baldy::Move(int dir)
{
	if (footContacts == 0)
		return;

	b2Vec2 vel = body->GetLinearVelocity();
	float newSpeed = 0.0f;

	if (dir == -1)
		newSpeed = b2Max(vel.x - 0.5f, -_curSpeed);
	else if (dir == 1)
		newSpeed = b2Min(vel.x + 0.5f, _curSpeed);

	if ((dir == 1 && isFlipped) || (dir == -1 && !isFlipped))
		FlipSprite();

	float velChange = newSpeed - vel.x;
	float impulse = body->GetMass() * velChange; //disregard time factor

	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

void Baldy::Jump(sf::Vector2f force)
{
	if (!_jumping && footContacts > 0 && _jumpTimeout < 0)
	{
		body->SetLinearVelocity(b2Vec2_zero);
		sf::Vector2f impulse = body->GetMass() * force;
		body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), body->GetWorldCenter(), true);
		_jumpTimeout = 15;
		_animState = AnimState::preJump;
		_jumping = true;
	}
}

void Baldy::Patrol()
{
	/*FlipSprite();
	_state = BaldyState::moving;
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

	Repath(targetNode->GetNodeLocation());*/
}

void Baldy::StartWatch()
{
	_animState = AnimState::idle;
	_state = BaldyState::idle;
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

void Baldy::ReturnHome()
{

}