#include "SaveDataManager.h"
#include "Definitions.h"

#include <iostream>


SaveDataManager::SaveDataManager()
{

}

SaveDataManager::~SaveDataManager()
{

}

void SaveDataManager::SaveGame(int saveNumber, SaveData data)
{
	std::string filePath = SAVE_PATH + std::to_string(saveNumber) + ".txt";

	std::ofstream output;
	output.open(filePath, std::ofstream::out | std::ofstream::trunc);

	if (output.is_open())
	{
		output << "zBits:" + std::to_string(data.zBits) + "\n";
		output << "gameTier:" + std::to_string(data.gameTier) + "\n";
		output << "damageIndex:" + std::to_string(data.damIndex) + "\n";
		output << "speedIndex:" + std::to_string(data.speedIndex) + "\n";
		output << "bulletsPerShotIndex:" + std::to_string(data.bulletsPerShotIndex) + "\n";
		output << "spreadIndex:" + std::to_string(data.spreadIndex) + "\n";
		output << "ammoCountIndex:" + std::to_string(data.ammoCountIndex) + "\n";

		if(data.isDead)
			output << "isDead:" + std::to_string(1) + "\n";
		else
			output << "isDead:" + std::to_string(0) + "\n";
	}
}

SaveDataManager::SaveData SaveDataManager::LoadGame(int saveNumber)
{
	SaveData save = SaveData();
	if (CheckForSave(saveNumber))
	{
		std::string filePath = SAVE_PATH + std::to_string(saveNumber);
		std::ifstream input(filePath + ".txt");

		std::string line;

		if (input.is_open())
		{
			while (getline(input, line))
			{
				std::string::size_type preData = line.find(':');
				std::string dataType;

				if (preData != std::string::npos)
					dataType = line.substr(0, preData);
				else
				{
					dataType = "Data is corrupted, line reads: " + line;
					std::cout << dataType << std::endl;
				}


				//Need to sort out properly, use a hashed switch statement. Just getting it working for now.
				if (dataType == "zBits")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.zBits = std::stoi(info);
				}
				else if (dataType == "gameTier")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.gameTier = std::stoi(info);
				}
				else if (dataType == "damageIndex")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.damIndex = std::stoi(info);
				}
				else if (dataType == "speedIndex")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.speedIndex = std::stoi(info);
				}
				else if (dataType == "bulletsPerShotIndex")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.bulletsPerShotIndex = std::stoi(info);
				}
				else if (dataType == "spreadIndex")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.spreadIndex = std::stoi(info);
				}
				else if (dataType == "ammoCountIndex")
				{
					std::string info = line.substr(preData + 1, line.size());
					save.ammoCountIndex = std::stoi(info);
				}
				else if (dataType == "isDead")
				{
					std::string info = line.substr(preData + 1, line.size());
					if (info == "0")
						save.isDead = false;
					else if (info == "1")
						save.isDead = true;
				}
			}
		}
	}
	return save;
}

bool SaveDataManager::CheckForSave(int saveNumber)
{
	std::string filePath = SAVE_PATH + std::to_string(saveNumber);
	std::ifstream input;
	input.open(filePath + ".txt");
	if (input.is_open())
		return true;

	return false;
}