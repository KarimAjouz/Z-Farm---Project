#include "ContactListener.h"
#include "AttackState.h"
#include "EquipmentState.h"
#include "Attack.h"
#include "Box.h"

#include "b2_settings.h"

ContactListener::ContactListener(Player* player, Level* level) :
	playerRef(player),
	levelRef(level)
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	// Get the fixture tags.
	PhysicsUserData* m_FixtureAUserData = reinterpret_cast<PhysicsUserData*>(contact->GetFixtureA()->GetUserData().pointer);
	PhysicsUserData* m_FixtureBUserData = reinterpret_cast<PhysicsUserData*>(contact->GetFixtureB()->GetUserData().pointer);

	if (m_FixtureAUserData == NULL || !m_FixtureAUserData->bIsValid)
	{
		std::cout << "ContactListener::BeginContact --> FixtureAUserData is null!" << std::endl;
		return;
	}

	if (m_FixtureBUserData == NULL || !m_FixtureBUserData->bIsValid)
	{
		std::cout << "ContactListener::BeginContact --> FixtureBUserData is null!" << std::endl;
		return;
	}

	if (m_FixtureAUserData->ObjectPointer)
		m_FixtureAUserData->ObjectPointer->HandleContactBegin(m_FixtureBUserData, m_FixtureAUserData->CollisionTag);

	if (m_FixtureBUserData->ObjectPointer)
		m_FixtureBUserData->ObjectPointer->HandleContactBegin(m_FixtureAUserData, m_FixtureBUserData->CollisionTag);

	std::cout << "ContactListener::BeginContact --> END" << std::endl;
	//if (IsContact(ECollisionTag::playerSword, ECollisionTag::box))
	//{
	//    bool isAFixPlayerRef = fixtureAUserData == static_cast<int>(ECollisionTag::playerSword);

	//    if (playerRef == nullptr)
	//    {
	//        std::cout << "Error: ContactListener::BeginContact --> playerRef is invalid!" << std::endl;
	//        return;
	//    }

	//    SwordItem* SwordRef = playerRef->GetEquipmentState()->GetItem();

	//    if (SwordRef == nullptr)
	//    {
	//        std::cout << "Error: ContactListener::BeginContact --> SwordRef is invalid!" << std::endl;
	//        return;
	//    }

	//    Attack* AttackRef;

	//    if (playerRef->GetTraversalState()->GetTraversalType() == ETraversalType::TT_Attack)
	//    {
	//        AttackState* AttackStateRef = static_cast<AttackState*>(playerRef->GetTraversalState());

	//        if (AttackStateRef == nullptr)
	//        {
	//            std::cout << "Error: ContactListener::BeginContact --> AttackStateRef is invalid!" << std::endl;
	//            return;
	//        }

	//        AttackRef = AttackStateRef->GetCurrentSequenceItem();
	//    }
	//    else
	//    {
	//        if (SwordRef->GetAttackSequence()->size() == 0)
	//        {
	//            std::cout << "Error: ContactListener::BeginContact --> AttackSequence is empty!" << std::endl;
	//            return;
	//        }

	//        AttackRef = SwordRef->GetAttackSequence()->at(0);
	//    }

	//    if (AttackRef == nullptr)
	//    {
	//        std::cout << "Error: ContactListener::BeginContact --> AttackRef is invalid!" << std::endl;
	//        return;
	//    }

	//    if (isAFixPlayerRef)
	//        AttackRef->AddContactObject(reinterpret_cast<ZEngine::GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer));
	//    else
	//        AttackRef->AddContactObject(reinterpret_cast<ZEngine::GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer));

	//}

	//// Handles Spike Collisions with Player
	//if (IsContact(ECollisionTag::player, ECollisionTag::spike))
	//    playerRef->Hit();
}

void ContactListener::EndContact(b2Contact* contact)
{
	// Get the fixture tags.
	PhysicsUserData* m_FixtureAUserData = reinterpret_cast<PhysicsUserData*>(contact->GetFixtureA()->GetUserData().pointer);
	PhysicsUserData* m_FixtureBUserData = reinterpret_cast<PhysicsUserData*>(contact->GetFixtureB()->GetUserData().pointer);

	if (m_FixtureAUserData == NULL || !m_FixtureAUserData)
	{
		std::cout << "ContactListener::EndContact --> FixtureAUserData is null!" << std::endl;
		return;
	}

	if (m_FixtureBUserData == NULL || !m_FixtureBUserData)
	{
		std::cout << "ContactListener::EndContact --> FixtureBUserData is null!" << std::endl;
		return;
	}

	if (m_FixtureAUserData->ObjectPointer)
		m_FixtureAUserData->ObjectPointer->HandleContactEnd(m_FixtureBUserData, m_FixtureAUserData->CollisionTag);

	if (m_FixtureBUserData->ObjectPointer)
		m_FixtureBUserData->ObjectPointer->HandleContactEnd(m_FixtureAUserData, m_FixtureBUserData->CollisionTag);

	std::cout << "ContactListener::EndContact --> END" << std::endl;

	// if (IsContact(ECollisionTag::playerSword, ECollisionTag::box))
	// {
	//     //Player* playerRef = nullptr;
	//     //Box* boxRef = nullptr;
	//     bool isAFixPlayerRef = fixtureAUserData == static_cast<int>(ECollisionTag::playerSword);

	//     //if (isAFixPlayerRef)
	//     //{
	//     //    playerRef = reinterpret_cast<Player*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	//     //}
	//     //else
	//     //{
	//     //    playerRef = reinterpret_cast<Player*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	//     //}

	//     if (playerRef == nullptr)
	//     {
	//         std::cout << "Error: ContactListener::BeginContact --> playerRef is invalid!" << std::endl;
	//         return;
	//     }

	//     SwordItem* SwordRef = playerRef->GetEquipmentState()->GetItem();

	//     if (SwordRef == nullptr)
	//     {
	//         std::cout << "Error: ContactListener::BeginContact --> SwordRef is invalid!" << std::endl;
	//         return;
	//     }

	//     Attack* AttackRef;

	//     if (playerRef->GetTraversalState()->GetTraversalType() == ETraversalType::TT_Attack)
	//     {
	//         AttackState* AttackStateRef = static_cast<AttackState*>(playerRef->GetTraversalState());

	//         if (AttackStateRef == nullptr)
	//         {
	//             std::cout << "Error: ContactListener::BeginContact --> AttackStateRef is invalid!" << std::endl;
	//             return;
	//         }

	//         AttackRef = AttackStateRef->GetCurrentSequenceItem();
	//     }
	//     else
	//     {
	//         if (SwordRef->GetAttackSequence()->size() == 0)
	//         {
	//             std::cout << "Error: ContactListener::BeginContact --> AttackSequence is empty!" << std::endl;
	//             return;
	//         }

	//         AttackRef = SwordRef->GetAttackSequence()->at(0);
	//     }

	//     if (AttackRef == nullptr)
	//     {
	//         std::cout << "Error: ContactListener::BeginContact --> AttackRef is invalid!" << std::endl;
	//         return;
	//     }

	//     if (isAFixPlayerRef)
	//         AttackRef->RemoveContactObject(reinterpret_cast<ZEngine::GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer));
	//     else
	//         AttackRef->RemoveContactObject(reinterpret_cast<ZEngine::GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer));

	// }

	///* if (IsContact(ECollisionTag::interactable, ECollisionTag::playerFoot))
	// {
	//     if (fixtureAUserData == static_cast<int>(ECollisionTag::interactable))
	//         playerRef->SetInteractable(nullptr);
	//     else
	//         playerRef->SetInteractable(nullptr);

	//     std::cout << "ROPESEGMENT UNSET FAM" << std::endl;
	// }*/

	// if (IsContact(ECollisionTag::player, ECollisionTag::room))
	//     playerRef->SetView();
}

bool ContactListener::IsContact(ECollisionTag aTag, ECollisionTag bTag)
{
	// if (fixtureAUserData == static_cast<int>(aTag) && fixtureBUserData == static_cast<int>(bTag) || fixtureBUserData == static_cast<int>(aTag) && fixtureAUserData == static_cast<int>(bTag))
	//     return true;

	return false;
}