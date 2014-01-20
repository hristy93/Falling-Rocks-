#include "Missiles.h"
#include "Variables.h"

// Adding misiless
void MissileMovement()
{
	for (randomAccess_iterator missile = missiles.begin(); missile != missiles.end();)
	{
		missile->Coordinates.Y -= powupSpeed;
		if (missile->Coordinates.Y < 0)
		{
			missile = missiles.erase(missile);
		}
		else
		{
			++missile;
		}
	}
}

// Missile form
void MissileForm()
{
	if (fire)
	{
		int x = dwarf[3].Coordinates.X;
		int y = dwarf[3].Coordinates.Y - 1;
		missiles.push_back(GameObject(x, y, '!'));
	}
}

// Check if the missile had hit a rock
void MissileCollision()
{
	int x = rocks.size();
	for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
	{
		int testRockX = rock->Coordinates.X;
		int testRockY = rock->Coordinates.Y;
		for (const_iterator missile = missiles.begin(); missile != missiles.end(); ++missile)
		{
			int testMissileX = missile->Coordinates.X;
			int testMissileY = missile->Coordinates.Y;
			if (testMissileX == testRockX && testMissileY == testRockY)
			{
				if (!rocks.empty())
				{
					rocks.erase(rock);
					break;
				}
				missiles.erase(missile);
				if (quit)
				{
					return;
				}
			}
		}
		if (rocks.size() == x - 1)
		{
			break;
		}
	}
}
