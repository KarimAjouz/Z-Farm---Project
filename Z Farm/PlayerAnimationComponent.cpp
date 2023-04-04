#include "PlayerAnimationComponent.h"

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
