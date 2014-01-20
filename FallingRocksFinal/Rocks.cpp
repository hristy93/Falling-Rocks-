#include "Variables.h"
#include "Rocks.h"
#include "ConsoleGaming.h"

//Randomises rock shape and color
void RocksShapeAndColor()
{
	if (frameCounter % rockSpawnInterval == 0)
	{
		int x = rand() % WindowWidth;

		//Rocks in defferent shapes
		int shapeNum = rand() % 7;
		switch (shapeNum)
		{
		case 0: rockSymbol = static_cast<char>(177); break;
		case 1: rockSymbol = static_cast<char>(176); break;
		case 2: rockSymbol = static_cast<char>(219); break;
		case 3: rockSymbol = static_cast<char>(220); break;
		case 4: rockSymbol = static_cast<char>(222); break;
		case 5: rockSymbol = static_cast<char>(178); break;
		case 6: rockSymbol = static_cast<char>(254); break;
		}
		stoneCounter++;
		rocks.push_back(GameObject(x, 0, rockSymbol));

		if (stoneCounter == 2)
		{
			rocks[0].Color = colour;
		}

		//It makes stones colorful
		randomAccess_iterator rock = rocks.end() - 1;
		switch (shapeNum)
		{
		case 0: rock->Color = ConsoleColors::Green; break;
		case 1: rock->Color = ConsoleColors::Red; break;
		case 2: rock->Color = ConsoleColors::Blue; break;
		case 3: rock->Color = ConsoleColors::Grey; break;
		case 4: rock->Color = ConsoleColors::Yellow; break;
		case 5: rock->Color = ConsoleColors::Purple; break;
		case 6: rock->Color = ConsoleColors::Cyan; break;
		}
		colour = rock->Color;
	}
}

//Creates and deletes rocks
void CreatingRocks()
{
	for (randomAccess_iterator rock = rocks.begin(); rock != rocks.end(); /* Empty clause so we can delete elements */)
	{
		rock->Coordinates.Y += rockSpeed;
		if (rock->Coordinates.Y > WindowHeight - 2)
		{
			rock = rocks.erase(rock);
		}
		else
		{
			++rock;
		}
	}
}
