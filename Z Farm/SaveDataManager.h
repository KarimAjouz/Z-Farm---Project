#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "ShopGunScale.h"

class SaveDataManager
{
public:

	SaveDataManager();
	~SaveDataManager();

	struct SaveData 
	{
		int zBits = 0;
		int gameTier = 1;

		bool isDead = false;

		int damIndex = 0;
		int speedIndex = 0;
		int bulletsPerShotIndex = 0;
		int spreadIndex = 0;
		int ammoCountIndex = 0;
	};



	void SaveGame(int saveNumber, SaveData data);

	SaveData LoadGame(int saveNumber);

private:


	bool CheckForSave(int saveNumber);

};

