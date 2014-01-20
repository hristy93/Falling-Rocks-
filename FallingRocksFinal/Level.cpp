#include "Variables.h"
#include "Level.h"
#include "Skills.h"
//Adjusting the difficulty curve
void AdjustDifficulty()
{
	if (levelCount > 7 && levelCount < 15)
	{
		difficulty = 2;
	}
	if (levelCount > 14)
	{
		difficulty = 3;
	}
}

void SetDifficulty()
{
	switch (difficulty)
	{
	case 1:
		sleepDuration = 150;
		break;
	case 2:
		sleepDuration = 100;
		break;
	case 3:
		sleepDuration = 50;
		break;
	}
}

// Writes on the screen the level on which is the game
void OutputOfChangeLevel()
{
	system("CLS");
	std::cout << "Level " << levelCount << std::endl;
	OutputOfAndromedaSkill();
	OutputOfFireSkill();
	OutputOfPhaseShiftSkill();
	Sleep(2000);
}

// Change Level
void ChangeLevel()
{
	if (frameCounter == 0)
	{
		OutputOfChangeLevel();
	}
	if (frameCounter % (100 + difficulty * 50) == 0 && frameCounter != 0)
	{
		levelCount++;
		OutputOfChangeLevel();

		AdjustDifficulty();
		SetDifficulty();

		if (rockSpawnInterval > 1 && levelCount % 2 == 0)
		{
			rockSpawnInterval--;
		}
		if (dwarfSpeed > 1 && levelCount % 10 == 0)
		{
			dwarfSpeed--;
			lastDwarfSpeed--;
		}
	}
}
