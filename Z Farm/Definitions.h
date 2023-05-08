#pragma once
#include "SFML/Graphics.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#define TILE_SIZE 32
#define TILE_SCALE 1

#define SPLASH_SCREEN_SHOW_TIME 0.5f

#define NAVIGATION_JUMP_HEIGHT_DIVISIONS 4
#define NAVIGATION_JUMP_SPEED_DIVISIONS 4
#define NAVIGATION_JUMP_POLLING_FREQ 10

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

//struct JumpTrajectory
//{
//public:
//	sf::Vector2f startPos;
//	sf::Vector2f startVel;
//
//	std::vector<sf::Vector2f> pointsArray;
//
//	int fallingPointIndex = 0;
//
//private:
//	sf::Vector2f prevTestNodePos;
//
//public:
//	JumpTrajectory()
//	{
//
//	}
//
//	JumpTrajectory(sf::Vector2f inStartPos, sf::Vector2f inStartVelocity)
//	{
//		startPos = inStartPos;
//		startVel = inStartVelocity;
//
//		GeneratePointsArray();
//	}
//
//private:
//	void SetJumpTrajectoryPos(sf::Vector2f newPos)
//	{
//
//	}
//
//	void GeneratePointsArray()
//	{
//		sf::Vector2f testPos = startPos;
//		int i = 0;
//
//		while
//			(
//			testPos.x > 0.0f && testPos.x < SCREEN_WIDTH &&
//			testPos.y > 0.0f && testPos.y < SCREEN_HEIGHT
//			)
//		{
//			pointsArray.push_back(testPos);
//			prevTestNodePos = testPos;
//			testPos = getTrajectoryPoint(startPos, startVel, i);
//
//			float yVel = testPos.y - prevTestNodePos.y;
//			if (yVel > 0.0f && fallingPointIndex == 0)
//			{
//				fallingPointIndex = i;
//			}
//			i++;
//		}
//	}
//
//	sf::Vector2f GetPoint(int n)
//	{
//		return pointsArray[n];
//	}
//
//	sf::Vector2f getTrajectoryPoint(sf::Vector2f& startingPosition, sf::Vector2f& startingVelocity, float n)
//	{
//		//velocity and gravity are given per second but we want time step values here
//		float t = 1.0f / NAVIGATION_JUMP_POLLING_FREQ; // seconds per time step (at 60fps)
//		sf::Vector2f stepVelocity = t * startingVelocity; // m/s
//		sf::Vector2f stepGravity = t * t * sf::Vector2f(0.0f, 9.81f) * SCALE; // m/s/s
//
//		return startingPosition + n * stepVelocity + 0.5f * (n * n + n) * stepGravity;
//	}
//};

#define SPLASH_SCREEN_BACKGROUND_FILEPATH "Content/Media/Splash/Background.png"
#define MENU_SCREEN_BACKGROUND_FILEPATH "Content/Media/Menu/Background.png"
#define SHOP_SCREEN_BACKGROUND_FILEPATH "Content/Media/Shop/Background.png"

#define TILE_COL_PATH "Content/Media/Textures/CollidableTiles.png"
#define TILE_BG_PATH "Content/Media/Textures/BackgroundTiles.png"
#define PIG_ICON "Content/Media/Textures/PigIcon.png"
#define BALDY_ICON "Content/Media/Textures/BaldyIcon.png"

#define SWORD_ITEM "Content/Media/Gameplay/Pickups/Sword.png"
#define SPIKE_TRAP "Content/Media/Gameplay/Traps/Spikes.png"
#define BOX_OBSTACLE "Content/Media/Gameplay/Props/Box/Box.png"
#define BOX_OBSTACLE_HIT "Content/Media/Gameplay/Props/Box/Hit.png"

#define MENU_BUTTON_FOLDER_FILEPATH "Content/Media/Buttons/Menu/"
#define SCALE_BUTTON_FOLDER_FILEPATH "Content/Media/Buttons/Scale/"

#define SKELE_WALK "Content/Media/Gameplay/Skeleton/Skeleton_Walk.png"
#define SKELE_WIND_UP "Content/Media/Gameplay/Skeleton/Skeleton_Wind_Up.png"
#define SKELE_ATTACK "Content/Media/Gameplay/Skeleton/Skeleton_Attack.png"
#define SKELE_ATTACK_RESET "Content/Media/Gameplay/Skeleton/Skeleton_Attack_Reset.png"
#define SKELE_DAMAGE "Content/Media/Gameplay/Skeleton/Skeleton_Damage.png"
#define SKELE_DEATH "Content/Media/Gameplay/Skeleton/Skeleton_Death.png"

#define PIG_IDLE "Content/Media/Gameplay/Pig/Pig_Idle.png"
#define PIG_ALERT "Content/Media/Gameplay/Pig/Pig_Alert.png"
#define PIG_ALARM "Content/Media/Gameplay/Pig/Pig_Panic.png"
#define PIG_DEATH "Content/Media/Gameplay/Pig/Pig_Death.png"

#define BALDY_IDLE "Content/Media/Gameplay/Pirates/Baldy/Idle.png"
#define BALDY_RUN "Content/Media/Gameplay/Pirates/Baldy/Run.png"
#define BALDY_PREJUMP "Content/Media/Gameplay/Pirates/Baldy/PreJump.png"
#define BALDY_JUMP "Content/Media/Gameplay/Pirates/Baldy/Jump.png"
#define BALDY_FALL "Content/Media/Gameplay/Pirates/Baldy/Fall.png"
#define BALDY_LAND "Content/Media/Gameplay/Pirates/Baldy/Land.png"
#define BALDY_KICK "Content/Media/Gameplay/Pirates/Baldy/Kick.png"
#define BALDY_HIT "Content/Media/Gameplay/Pirates/Baldy/Hit.png"
#define BALDY_DEAD "Content/Media/Gameplay/Pirates/Baldy/Dead.png"

#define DIALOGUE_QUESTION_IN "Content/Media/Dialogue/Question_In.png"
#define DIALOGUE_QUESTION_OUT "Content/Media/Dialogue/Question_Out.png"
#define DIALOGUE_ALERT_IN "Content/Media/Dialogue/Alert_In.png"
#define DIALOGUE_ALERT_OUT "Content/Media/Dialogue/Alert_Out.png"

#define CHAIN_LINK_TEX "Content/Media/Textures/ChainLink8x32.png"

#define DEBUG_FONT_PATH "Content/Media/Fonts/DebugFontBold.otf"

#define UI_RELOADBAR "Content/Media/UI/ReloadBar"

#define SAVE_PATH "SaveData/"
#define LEVEL_PATH "LevelData/"