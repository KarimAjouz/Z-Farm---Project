#pragma once

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#define SPLASH_SCREEN_SHOW_TIME 0.5f

const float SCALE = 30.f;

enum class CollisionTag
{
	def,
	player,
	playerFoot,
	level,
	tile,
	ground,
	enemy, 
	background,
	room,
	playerSword
};

#define SPLASH_SCREEN_BACKGROUND_FILEPATH "Media/Splash/Background.png"
#define MENU_SCREEN_BACKGROUND_FILEPATH "Media/Menu/Background.png"
#define SHOP_SCREEN_BACKGROUND_FILEPATH "Media/Shop/Background.png"

#define TILE_PATH "Media/Textures/TerrainAndBackWall.png"
#define UNITS_PATH "Media/Textures/EnemyTiles.png"
#define SWORD_ITEM "Media/Gameplay/Pickups/Sword.png"


#define MENU_BUTTON_FOLDER_FILEPATH "Media/Buttons/Menu/"
#define SCALE_BUTTON_FOLDER_FILEPATH "Media/Buttons/Scale/"


#define PLAYER_FILEPATH "Media/Gameplay/Player.png"
#define ZOMBIE_FILEPATH "Media/Gameplay/Zombie.png"
#define BULLET_FILEPATH "Media/Gameplay/Bullet.png"
#define PICKUP_FILEPATH "Media/Gameplay/Pickup.png"

#define SKELE_WALK "Media/Gameplay/Skeleton/Skeleton_Walk.png"
#define SKELE_WIND_UP "Media/Gameplay/Skeleton/Skeleton_Wind_Up.png"
#define SKELE_ATTACK "Media/Gameplay/Skeleton/Skeleton_Attack.png"
#define SKELE_ATTACK_RESET "Media/Gameplay/Skeleton/Skeleton_Attack_Reset.png"
#define SKELE_DAMAGE "Media/Gameplay/Skeleton/Skeleton_Damage.png"
#define SKELE_DEATH "Media/Gameplay/Skeleton/Skeleton_Death.png"

#define PIG_IDLE "Media/Gameplay/Pig/Pig_Idle.png"
#define PIG_ALERT "Media/Gameplay/Pig/Pig_Alert.png"
#define PIG_ALARM "Media/Gameplay/Pig/Pig_Panic.png"
#define PIG_DEATH "Media/Gameplay/Pig/Pig_Death.png"

#define QUESTION_IN "Media/Gameplay/Dialogue/Question_In.png"
#define EXCLAMATION_IN "Media/Gameplay/Dialogue/Alert_In.png"
#define QUESTION_OUT "Media/Gameplay/Dialogue/Question_Out.png"
#define EXCLAMATION_OUT "Media/Gameplay/Dialogue/Alert_Out.png"

#define PLAYER_IDLE "Media/Gameplay/Player/Idle.png"
#define PLAYER_RUN "Media/Gameplay/Player/Run.png"
#define PLAYER_JUMP "Media/Gameplay/Player/Jump.png"
#define PLAYER_FALL "Media/Gameplay/Player/Fall.png"
#define PLAYER_LAND "Media/Gameplay/Player/Land.png"

#define PLAYER_HIT "Media/Gameplay/Player/Hit.png"
#define PLAYER_DEATH "Media/Gameplay/Player/Death.png"
#define PLAYER_DASH "Media/Gameplay/Player/Dash.png"

#define PLAYER_IDLE_SWORD "Media/Gameplay/Player/Sword/Idle.png"
#define PLAYER_RUN_SWORD "Media/Gameplay/Player/Sword/Run.png"
#define PLAYER_JUMP_SWORD "Media/Gameplay/Player/Sword/Jump.png"
#define PLAYER_FALL_SWORD "Media/Gameplay/Player/Sword/Fall.png"
#define PLAYER_LAND_SWORD "Media/Gameplay/Player/Sword/Land.png"
#define PLAYER_STAB_ATTACK "Media/Gameplay/Player/Sword/StabAttack.png"
#define PLAYER_UPSLASH_ATTACK "Media/Gameplay/Player/Sword/UpSlashAttack.png"
#define PLAYER_DOWNSLASH_ATTACK "Media/Gameplay/Player/Sword/DownSlashAttack.png"

#define UI_RELOADBAR "Media/UI/ReloadBar"

#define SAVE_PATH "SaveData/"
#define LEVEL_PATH "LevelData/"