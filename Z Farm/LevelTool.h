#pragma once
#include "Button.h"

class LevelTool : public ZEngine::Button
{
public:
	LevelTool();
	LevelTool(ZEngine::GameDataRef data, sf::Vector2f pos, std::string borderFilePath, std::string borderFileName, std::string iconFilePath, std::string iconFileName);


	~LevelTool();


private:
	ZEngine::GameDataRef _data;

	std::string _bFileName;
	std::string _iFileName;
};

