#pragma once
#include "AnimationComponent.h"

#define PLAYER_IDLE "Content/Media/Gameplay/Player/Idle.png"
#define PLAYER_RUN "Content/Media/Gameplay/Player/Run.png"
#define PLAYER_JUMP "Content/Media/Gameplay/Player/Jump.png"
#define PLAYER_FALL "Content/Media/Gameplay/Player/Fall.png"
#define PLAYER_LAND "Content/Media/Gameplay/Player/Land.png"

#define PLAYER_HIT "Content/Media/Gameplay/Player/Hit.png"
#define PLAYER_DEATH "Content/Media/Gameplay/Player/Hit.png"
#define PLAYER_DASH "Content/Media/Gameplay/Player/Dash.png"

#define PLAYER_IDLE_SWORD "Content/Media/Gameplay/Player/Sword/Idle.png"
#define PLAYER_RUN_SWORD "Content/Media/Gameplay/Player/Sword/Run.png"
#define PLAYER_JUMP_SWORD "Content/Media/Gameplay/Player/Sword/Jump.png"
#define PLAYER_FALL_SWORD "Content/Media/Gameplay/Player/Sword/Fall.png"
#define PLAYER_LAND_SWORD "Content/Media/Gameplay/Player/Sword/Land.png"

#define PLAYER_STAB_ATTACK "Content/Media/Gameplay/Player/Sword/StabAttack.png"
#define PLAYER_UPSLASH_ATTACK "Content/Media/Gameplay/Player/Sword/UpSlashAttack.png"
#define PLAYER_DOWNSLASH_ATTACK "Content/Media/Gameplay/Player/Sword/DownSlashAttack.png"


class PlayerAnimationComponent
	:
	public ZEngine::AnimationComponent
{
public:

	PlayerAnimationComponent(sf::Sprite* spritePtr, ZEngine::GameDataRef data);

	void InitAnimations();

	virtual void Update(float dT) override;

	void SetAnimation(const enum ETraversalType& InTraversalStateType, const enum EEquipmentType& InEquipmentType);
	virtual void SetAnimation(std::string InAnimationName) override;

	virtual std::string GetAnimForEquipment(const enum ETraversalType& InTraversalStateType, const enum EEquipmentType& InEquipmentType);

private:

};

