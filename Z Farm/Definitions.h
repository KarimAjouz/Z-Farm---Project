#pragma once
#include "SFML/Graphics.hpp"

#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 512

#define TILE_SIZE 32
#define TILE_SCALE 1

#define SPLASH_SCREEN_SHOW_TIME 0.5f

#define NAVIGATION_JUMP_HEIGHT_DIVISIONS 4
#define NAVIGATION_JUMP_SPEED_DIVISIONS 4
#define NAVIGATION_JUMP_POLLING_FREQ 10


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
	enemyFoot,
	background,
	room,
	playerSword,
	spike,
	box
};

struct RoomTileData
{
	sf::Vector2i tileSheetCoords;
	bool collision;

	RoomTileData()
	{
		tileSheetCoords = sf::Vector2i(1, 1);
		collision = false;
	};

	RoomTileData(sf::Vector2i sheetCoords, bool col)
	{
		tileSheetCoords = sheetCoords;
		collision = col;
	};
};

struct JumpTrajectory
{
public:
	sf::Vector2f startPos;
	sf::Vector2f startVel;

	std::vector<sf::Vector2f> pointsArray;

	int fallingPointIndex = 0;

private:
	sf::Vector2f prevTestNodePos;

public:
	JumpTrajectory()
	{

	}

	JumpTrajectory(sf::Vector2f inStartPos, sf::Vector2f inStartVelocity)
	{
		startPos = inStartPos;
		startVel = inStartVelocity;

		GeneratePointsArray();
	}

private:
	void SetJumpTrajectoryPos(sf::Vector2f newPos)
	{

	}

	void GeneratePointsArray()
	{
		sf::Vector2f testPos = startPos;
		int i = 0;

		while 
			(
			testPos.x > 0.0f && testPos.x < SCREEN_WIDTH &&
			testPos.y > 0.0f && testPos.y < SCREEN_HEIGHT
			)
		{
			pointsArray.push_back(testPos);
			prevTestNodePos = testPos;
			testPos = getTrajectoryPoint(startPos, startVel, i);

			float yVel = testPos.y - prevTestNodePos.y;
			if (yVel > 0.0f && fallingPointIndex == 0)
			{
				fallingPointIndex = i;
			}
			i++;
		}
	}

	sf::Vector2f GetPoint(int n)
	{
		return pointsArray[n];
	}

	sf::Vector2f getTrajectoryPoint(sf::Vector2f& startingPosition, sf::Vector2f& startingVelocity, float n)
	{
		//velocity and gravity are given per second but we want time step values here
		float t = 1.0f / NAVIGATION_JUMP_POLLING_FREQ; // seconds per time step (at 60fps)
		sf::Vector2f stepVelocity = t * startingVelocity; // m/s
		sf::Vector2f stepGravity = t * t * sf::Vector2f(0.0f, 9.81f) * SCALE; // m/s/s

		return startingPosition + n * stepVelocity + 0.5f * (n * n + n) * stepGravity;
	}
};

#define SPLASH_SCREEN_BACKGROUND_FILEPATH "Media/Splash/Background.png"
#define MENU_SCREEN_BACKGROUND_FILEPATH "Media/Menu/Background.png"
#define SHOP_SCREEN_BACKGROUND_FILEPATH "Media/Shop/Background.png"

#define TILE_COL_PATH "Media/Textures/CollidableTiles.png"
#define TILE_BG_PATH "Media/Textures/BackgroundTiles.png"
#define PIG_ICON "Media/Textures/PigIcon.png"
#define BALDY_ICON "Media/Textures/BaldyIcon.png"

#define SWORD_ITEM "Media/Gameplay/Pickups/Sword.png"
#define SPIKE_TRAP "Media/Gameplay/Traps/Spikes.png"
#define BOX_OBSTACLE "Media/Gameplay/Props/Box/Box.png"
#define BOX_OBSTACLE_HIT "Media/Gameplay/Props/Box/Hit.png"



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

#define PLAYER_IDLE "Media/Gameplay/Player/Idle.png"
#define PLAYER_RUN "Media/Gameplay/Player/Run.png"
#define PLAYER_JUMP "Media/Gameplay/Player/Jump.png"
#define PLAYER_FALL "Media/Gameplay/Player/Fall.png"
#define PLAYER_LAND "Media/Gameplay/Player/Land.png"

#define PLAYER_HIT "Media/Gameplay/Player/Hit.png"
#define PLAYER_DEATH "Media/Gameplay/Player/Hit.png"
#define PLAYER_DASH "Media/Gameplay/Player/Dash.png"

#define PLAYER_IDLE_SWORD "Media/Gameplay/Player/Sword/Idle.png"
#define PLAYER_RUN_SWORD "Media/Gameplay/Player/Sword/Run.png"
#define PLAYER_JUMP_SWORD "Media/Gameplay/Player/Sword/Jump.png"
#define PLAYER_FALL_SWORD "Media/Gameplay/Player/Sword/Fall.png"
#define PLAYER_LAND_SWORD "Media/Gameplay/Player/Sword/Land.png"
#define PLAYER_STAB_ATTACK "Media/Gameplay/Player/Sword/StabAttack.png"
#define PLAYER_UPSLASH_ATTACK "Media/Gameplay/Player/Sword/UpSlashAttack.png"
#define PLAYER_DOWNSLASH_ATTACK "Media/Gameplay/Player/Sword/DownSlashAttack.png"


#define BALDY_IDLE "Media/Gameplay/Pirates/Baldy/Idle.png"
#define BALDY_RUN "Media/Gameplay/Pirates/Baldy/Run.png"
#define BALDY_PREJUMP "Media/Gameplay/Pirates/Baldy/PreJump.png"
#define BALDY_JUMP "Media/Gameplay/Pirates/Baldy/Jump.png"
#define BALDY_FALL "Media/Gameplay/Pirates/Baldy/Fall.png"
#define BALDY_LAND "Media/Gameplay/Pirates/Baldy/Land.png"
#define BALDY_KICK "Media/Gameplay/Pirates/Baldy/Kick.png"
#define BALDY_HIT "Media/Gameplay/Pirates/Baldy/Hit.png"
#define BALDY_DEAD "Media/Gameplay/Pirates/Baldy/Dead.png"


#define DIALOGUE_QUESTION_IN "Media/Dialogue/Question_In.png"
#define DIALOGUE_QUESTION_OUT "Media/Dialogue/Question_Out.png"
#define DIALOGUE_ALERT_IN "Media/Dialogue/Alert_In.png"
#define DIALOGUE_ALERT_OUT "Media/Dialogue/Alert_Out.png"





#define UI_RELOADBAR "Media/UI/ReloadBar"

#define SAVE_PATH "SaveData/"
#define LEVEL_PATH "LevelData/"