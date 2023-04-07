#include "PlayerAnimationComponent.h"

#include "EquipmentState.h"
#include "TraversalState.h"

PlayerAnimationComponent::PlayerAnimationComponent(sf::Sprite* spritePtr, ZEngine::GameDataRef data)
	:
	AnimationComponent(spritePtr, data)
{
	InitAnimations();
}

void PlayerAnimationComponent::InitAnimations()
{
	AddAnimation("PlayerIdle", PLAYER_IDLE, 0.5f, true);
	AddAnimation("PlayerRun", PLAYER_RUN, 0.5f, true);
	AddAnimation("PlayerJump", PLAYER_JUMP, 0.3f, false);
	AddAnimation("PlayerFall", PLAYER_FALL, 0.1f, false);
	AddAnimation("PlayerLand", PLAYER_LAND, 0.3f, false);
	AddAnimation("PlayerDeath", PLAYER_DEATH, 0.4f, false);

	AddAnimation("PlayerIdleSword", PLAYER_IDLE_SWORD, 0.5f, true);
	AddAnimation("PlayerRunSword", PLAYER_RUN_SWORD, 0.5f, true);
	AddAnimation("PlayerJumpSword", PLAYER_JUMP_SWORD, 0.3f, false);
	AddAnimation("PlayerFallSword", PLAYER_FALL_SWORD, 0.1f, false);
	AddAnimation("PlayerLandSword", PLAYER_LAND_SWORD, 0.2f, false);

	AddAnimation("PlayerStab", PLAYER_STAB_ATTACK, 0.3f, false);
	AddAnimation("PlayerUpSlash", PLAYER_UPSLASH_ATTACK, 0.3f, false);
	AddAnimation("PlayerDownSlash", PLAYER_DOWNSLASH_ATTACK, 0.3f, false);
}

void PlayerAnimationComponent::Update(float dT)
{
	AnimationComponent::Update(dT);
}

void PlayerAnimationComponent::SetAnimation(const enum ETraversalType& InAnimType, const enum EEquipmentType& InEquipmentType)
{
	std::string animString = GetAnimForEquipment(InAnimType, InEquipmentType);
	ZEngine::AnimationComponent::SetAnimation(animString);
}

std::string PlayerAnimationComponent::GetAnimForEquipment(const enum ETraversalType& InTraversalStateType, const enum EEquipmentType& InEquipmentType)
{
	std::string OutString = "Player";

	switch (InTraversalStateType)
	{
	case ETraversalType::TT_Idle:
		OutString.append("Idle");
		break;
	case ETraversalType::TT_Run:
		OutString.append("Run");
		break;
	case ETraversalType::TT_Jump:
		OutString.append("Jump");
		break;
	case ETraversalType::TT_Fall:
		OutString.append("Fall");
		break;
	case ETraversalType::TT_Land:
		OutString.append("Land");
		break;
	default:
		OutString.append("Idle");
		break;
	}

	switch (InEquipmentType)
	{
	case EEquipmentType::ET_Sword:
		OutString.append("Sword");
		break;
	case EEquipmentType::ET_Gun:
		OutString.append("Gun");
		break;
	default:
		break;
	}

	return OutString;
}
