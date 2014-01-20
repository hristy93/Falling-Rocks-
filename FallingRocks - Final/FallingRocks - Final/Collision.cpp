#include "Collision.h"
#include "Variables.h"
#include "Menus.h"
#include "FallingRocks.h"

void AfterCollision()
{
	//if no more hitpoints
	score = stoneCounter * 15 + score;
	system("CLS");
	std::cout << "Good Game Well Played" << std::endl;
	std::cout << "Your score is " << score << std::endl;
	Sleep(2000);
	Reset();
	main();

	//else hitpoints--
}

void Collision()
{

	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		int testDwarfX = dwarfBody->Coordinates.X;
		int testDwarfY = dwarfBody->Coordinates.Y;
		for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
		{
			int testRockX = rock->Coordinates.X;
			int testRockY = rock->Coordinates.Y;
			if (testDwarfX == testRockX && testDwarfY == testRockY)
			{
				//delete rock if hitpoints are included
				if (!phaseShift)
				{
					AfterCollision();
				}
				if (quit)
				{
					return;
				}
			}
		}
	}
}
