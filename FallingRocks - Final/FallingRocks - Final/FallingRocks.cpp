#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "ConsoleGaming.h"

#include "FallingRocks.h"
#include "Variables.h"
#include "Bonuses.h"
#include "Menus.h"
#include "Skills.h"
#include "Missiles.h"
#include "Powups.h"
#include "UpdateDwarf.h"
#include "Level.h"
#include "Rocks.h"
#include "Collision.h"

using namespace std;
using namespace ConsoleColors;

HANDLE consoleHandle;

//Picks dwarf properties
void PicksDwarfProperties()
{
	CharacterSelection();
	KeyToChooseModel();

	CharacterColorSelection();
	KeyToChooseColor();

	lastDwarfShape = dwarfShape;
	start = true;
	UpdateDwarf();
}

//MainMenu  manipulation
void MainMenu()
{
	PlaySound(TEXT("secret.wav"), NULL, SND_FILENAME|SND_ASYNC);
	start = false;
	quit = false;
	while (true)
	{
		PrintMainMenu();
		MainMenuKey();
		if (start)
		{
			start = false;
			break;
		}
		if (quit)
		{
			break;
		}
		ReturnToMenu();
	}
}

//Updates everything
void Update()
{
	UpdateDwarfCoordinates();
	ChangeColor();

	CreatingRocks();
	RocksShapeAndColor();
	diceRolled = false;

	CreatingPowups();
	AddingPowupWithDifShapes();

	MissileMovement();
	MissileForm();
	FireDuration();

	if (quit)
	{
		return;
	}
	ChangeLevel();
	if (fastBonusDurtion != 0)
	{
		fastBonusDurtion--;
	}
	frameCounter++;
}

//Prints the objects on screen
void Draw()
{
	ClearScreen(consoleHandle);
	for (const_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Draw(consoleHandle);
	}

	for (const_iterator rock = rocks.begin(); rock != rocks.end(); ++rock)
	{
		rock->Draw(consoleHandle);
	}
	for (const_iterator powup = powups.begin(); powup != powups.end(); ++powup)
	{
		powup->Draw(consoleHandle);
	}
	for (const_iterator missile = missiles.begin(); missile != missiles.end(); ++missile)
	{
		missile->Draw(consoleHandle);
	}
}


int main()
{
	MainMenu();
	if (quit)
	{
		return 0;
	}
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	while (true)
	{
		Update();
		if (quit)
		{
			break;
		}
		Collision();
		SkillDuration();
		PowupCollsion();
		Draw();
		Sleep(sleepDuration);
	}
	return 0;
}
