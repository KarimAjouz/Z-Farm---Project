//#pragma once
//#include "Game.h"
//#include "Level.h"
//#include "TilePicker.h"
//#include "Player.h"
//
//
//#include <SFML/Graphics.hpp>
//
//#include <string>
//
//class LevelBuilder
//{
//public:
//	LevelBuilder(ZEngine::GameDataRef data, b2World* worldRef, Level* levelRef, Player* playerRef);
//	~LevelBuilder();
//
//	void Update(float dT);
//	void Draw();
//
//	void Activate();
//	void Deactivate();
//
//	bool isActive() { return _active; }
//
//	void Scroll(int dir);
//
//	void AddTile();
//	void RemoveTile();
//	void ReplaceTile();
//
//	void SaveLevel();
//	void LoadLevel();
//	void LoadLevel(std::string name);
//
//	void MouseRelease();
//	void OpenSelector();
//
//	void SetMouseGridLock(bool isLock);
//
//	void HandleKeyboardInputs(sf::Event* event);
//
//private:
//	int _scrollSelector = 0;
//	ZEngine::GameDataRef _data;
//
//	sf::Vector2f _curRoomOffset = sf::Vector2f();
//	Level* _levelRef;
//	b2World* _worldRef;
//	Player* _playerRef;
//
//	sf::IntRect _texRect = sf::IntRect(0, 0, TILE_SIZE * TILE_SCALE, TILE_SIZE * TILE_SCALE);
//
//	sf::Sprite _curSelectedTexture;
//	sf::RectangleShape _curTextureOutline;
//
//	sf::RectangleShape _hoveredTile;
//	sf::RectangleShape _newRoomSelector;
//
//	std::vector<std::vector<sf::Vector2i>> _curMap;
//	Room _emptyRoom;
//
//
//	TilePicker _tilePicker;
//	bool _active = false;
//
//	bool _mouseLocked = true;
//	bool _painting = false;
//
//	void PaintLevel();
//
//	int _entityType;
//	bool CheckForLevel(std::string levelName);
//	bool _inRoom = false;
//
//	void NewRoom();
//	void AddUnit(int type);
//	void AddObstacle(int type);
//
//	void TestMouseHover();
//
//};
