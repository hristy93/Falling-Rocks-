#include"Variables.h"
#include "Variables.h"
#include "Powups.h"
#include "Bonuses.h"
#include "UpdateDwarf.h"
//Creates and deletes powerups
void CreatingPowups()
{
	for (randomAccess_iterator powup = powups.begin(); powup != powups.end(); /* Empty clause so we can delete elements */)
	{
		powup->Coordinates.Y += powupSpeed;
		if (powup->Coordinates.Y > WindowHeight - 2)
		{
			powup = powups.erase(powup);
		}
		else
		{
			++powup;
		}
	}
}

//Checks the bonus, changes shape or speed
void OnPowupsCollision()
{
	copyOfFrameCounter = frameCounter;

	if (powupSymbol == powupSymbol1)
	{
		OutputOfFasterBonus();
	}
	if (powupSymbol == powupSymbol2 && !isShrinked)
	{
		OutputOfShrinkBonus();
	}
}

// Returns the dwarf to his previous speed or shape, after powups had expired
void DwarfPrevStatus()
{
	if (frameCounter == (copyOfFrameCounter + (30 + difficulty * 15)))
	{
		if (fastBonusDurtion == 0)
		{
			dwarfSpeed = lastDwarfSpeed;
		}
		if (isShrinked)
		{
			dwarf.clear();
			isShrinked = false;
			UpdateDwarf();
		}
	}
}

// Check if the dwarf has catch a powup
void PowupCollsion()
{
	DwarfPrevStatus();
	for (const_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		int dwarfX = dwarfBody->Coordinates.X;
		int dwarfY = dwarfBody->Coordinates.Y;
		for (const_iterator powup = powups.begin(); powup != powups.end(); ++powup)
		{
			int powupX = powup->Coordinates.X;
			int powupY = powup->Coordinates.Y;
			if (dwarfX == powupX && dwarfY == powupY)
			{
				score += 75;
				OnPowupsCollision();
				if (!powups.empty())
				{
					powups.erase(powup);
					break;
				}
			}
		}
		if (powups.empty())
		{
			break;
		}
	}
}

// Adds new elements to powup vector
void AddingPowupWithDifShapes()
{
	if (frameCounter % 50 == 0 && frameCounter != 0)
	{
		int x = rand() % WindowWidth;
		if (frameCounter % 100 == 0)
		{
			powups.push_back(GameObject(x, 0, powupSymbol1));
			powupSymbol = powupSymbol1;
		}
		else
		{
			powups.push_back(GameObject(x, 0, powupSymbol2));
			powupSymbol = powupSymbol2;
		}
	}
}
