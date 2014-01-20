
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "Menus.h"
#include "Variables.h"
#include "FallingRocks.h"
#include "UpdateDwarf.h"


//Hall of fame result 
void HallOfFame()
{
	system("CLS");
	std::cout << "Your highscore is " << highScore << std::endl;
	std::cout << "Press 'q' to return to menu." << std::endl;
}

//Prints the options menu from the text file
void PrintOptionsMenu()
{
	std::string line;
	std::ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(std::ios::beg);
	while (std::getline(myfile, line))
	{
		if (line == "marker8")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			std::cout << line << std::endl;
		}
		if (line == "marker7")
		{
			toPrint = true;
		}
	}
}

//Waits for the correct key to be pressed in order to choose a set of controls
void OptionsMenuKey()
{
	while (true)
	{
		if (_kbhit())
		{
			char mainMenuKey = _getch();
			switch (mainMenuKey)
			{
				case 's':
					useArrowKeys = false;
					break;
				case 't':
					useArrowKeys = true;
					break;
				default:
					toBreak = false;
			}
			if (toBreak)
			{
				break;
			}
			else
			{
				toBreak = true;
			}
		}
	}
}



//Program waits for the user to press one of the following keys
void MainMenuKey()
{
	while (true)
	{
		if (_kbhit())
		{
			char mainMenuKey = _getch();
			switch (mainMenuKey)
			{
				case NEW_GAME_CHAR:
					PicksDwarfProperties();
					break;
				case LOAD_CHAR:
					LoadGame();
					break;
				case OPTIONS_CHAR:
					Options();
					break;
				case FAME_CHAR:
					HallOfFame();
					break;
				case CREDITS_CONTINUE_CHAR:
					Credits();
					break;
				case INSTRUCTIONS_CHAR:
					Instructions();
					break;
				case QUIT_CHAR:
					quit = true;
					break;
				default:
					toBreak = false;
			}
			if (toBreak)
			{
				break;
			}
			else
			{
				toBreak = true;
			}
		}
	}
}
// Prints the MainMenu from "main menu.text". Markers serve as CheckPionts in the text file
void PrintMainMenu()
{
	system("CLS");
	std::string line;
	std::ifstream myfile("main menu.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			if (line == "marker1")
			{
				break;
			}
			std::cout << line << std::endl;
		}
	}
}

//Prints Character selection menu
void CharacterSelection()
{
	std::string line;
	std::ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(std::ios::beg);
	while (std::getline(myfile, line))
	{
		if (line == "marker6")
		{
			toPrint = false;
			break;
		}
		if (toPrint == true)
		{
			std::cout << line << std::endl;
		}
		if (line == "marker5")
		{
			toPrint = true;
		}
	}
}

//Prints the credits menu
void Credits()
{
	std::string line;
	std::ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(std::ios::beg);
	while (std::getline(myfile, line))
	{
		if (line == "marker3")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			std::cout << line << std::endl;
		}
		if (line == "marker2")
		{
			toPrint = true;
		}
	}
}

//Prints the instructions menu if set1 has been chosen from options
void InstructionsOne()
{
	std::string line;
	std::ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(std::ios::beg);
	while (std::getline(myfile, line))
	{
		if (line == "marker4")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			std::cout << line << std::endl;
		}
		if (line == "marker3")
		{
			toPrint = true;
		}
	}
}

//Prints the instructions menu if set2 has been chosen from options
void InstructionsTwo()
{
	std::string line;
	std::ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(std::ios::beg);
	while (std::getline(myfile, line))
	{
		if (line == "marker9")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			std::cout << line << std::endl;
		}
		if (line == "marker8")
		{
			toPrint = true;
		}
	}
}

//Prints the correct instructions menu
void Instructions()
{
	if (!useArrowKeys)
	{
		InstructionsOne();
	}
	else
	{
		InstructionsTwo();
	}
}

//Waiting for the rigth key to be pressed in order to choose character
void KeyToChooseModel()
{
	while (true)
	{
		if (_kbhit)
		{
			while (true)
			{
				char model;
				model = _getch();

				if (model > 48 && model < 54)
				{
					dwarfShape = model - 48;
					break;
				}
			}
		}
		break;
	}
}

//Waiting for the rigth key to be pressed in order to choose character color
void KeyToChooseColor()
{
	while (true)
	{
		if (_kbhit)
		{
			while (true)
			{
				char color;
				color = _getch();

				if (color > 48 && color < 57)
				{
					dwarfColor = color - 48;
					break;
				}
			}
		}
		break;
	}
}

//Prints charater solor selection menu
void CharacterColorSelection()
{
	std::string line;
	std::ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(std::ios::beg);
	while (std::getline(myfile, line))
	{
		if (line == "marker7")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			std::cout << line << std::endl;
		}
		if (line == "marker6")
		{
			toPrint = true;
		}
	}
}

void Reset()
{
	difficulty = 1;
	phaseShiftDuration = 0;
	phaseShift = false;
	phaseShiftAvailable = false;
	dwarfSpeed = 3;
	lastDwarfSpeed = 3;
	dwarfShape = 1;
	lastDwarfShape = 1;
	enlargeX = WindowWidth / 2;
	enlargeY = WindowHeight - 2;
	stoneCounter = 0;
	colour = 0xF;
	sleepDuration = 150;
	isShrinked = false;
	levelCount = 1;
	frameCounter = 0;
	copyOfFrameCounter = 0;
	rockSpawnInterval = 10;
	andromedaSkillOn = false;
	lastUsedAndroSkill = 0;
	fire = false;
	lastUsedFireSkill = 5;
	fireDuration = 0;
	fireAvailable = false;
	fastBonusDurtion = 0;
	if (score > highScore)
	{
		highScore = score;
	}
	score = 0;
	dwarf.clear();
	rocks.clear();
	powups.clear();
	missiles.clear();
}

void SaveGame()
{
	score = stoneCounter * 15 + score;
	std::ofstream saveFile("SafeFile.txt");
	saveFile << fastBonusDurtion << std::endl;
	saveFile << dwarfSpeed << std::endl;
	saveFile << lastDwarfSpeed << std::endl;
	saveFile << dwarfShape << std::endl;
	saveFile << lastDwarfShape << std::endl;
	saveFile << enlargeX << std::endl;
	saveFile << enlargeY << std::endl;
	saveFile << stoneCounter << std::endl;
	saveFile << sleepDuration << std::endl;
	saveFile << isShrinked << std::endl;
	saveFile << levelCount << std::endl;
	saveFile << frameCounter << std::endl;
	saveFile << copyOfFrameCounter << std::endl;
	saveFile << rockSpawnInterval << std::endl;
	saveFile << score << std::endl;
	saveFile << dwarfColor << std::endl;
	saveFile << phaseShiftAvailable << std::endl;
	saveFile << phaseShift << std::endl;
	saveFile << phaseShiftDuration << std::endl;
	saveFile << difficulty << std::endl;
	saveFile << andromedaSkillOn;
	saveFile << lastUsedAndroSkill << std::endl;
	saveFile << fire << std::endl;
	saveFile << lastUsedFireSkill << std::endl;
	saveFile << fireDuration << std::endl;
	saveFile << fireAvailable << std::endl;
	saveFile.close();
	system("CLS");
	std::cout << "Your game has been saved" << std::endl;
	std::cout << "Press q to return to menu" << std::endl;
}


void InGameMenuKey()
{
	while (true)
	{
		if (_kbhit())
		{

			char mainMenuKey = _getch();
			switch (mainMenuKey)
			{
			case CREDITS_CONTINUE_CHAR:
				start = true;
				break;
			case SAVE_CHAR:
				SaveGame();
				break;
			case OPTIONS_CHAR:
				Options();
				break;
			case FAME_CHAR:
				HallOfFame();
				break;
			case INSTRUCTIONS_CHAR:
				Instructions();
				break;
			case MENU_CHAR:
				Reset();
				quit = true;
				start = true;
				break;
			case QUIT_CHAR:
				quit = true;
				break;
			default:
				toBreak = false;
			}
			if (toBreak)
			{
				break;
			}
			else
			{
				toBreak = true;
			}
		}
	}
}

void ReturnToMenu()
{
	while (true)
	{
		char inGameMainMenuKey = _getch();
		if (inGameMainMenuKey == 'q')
		{
			break;
		}
	}
}

void InGameMenu()
{
	PlaySound(TEXT("secret.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (true)
	{
		PrintInGameMenu();
		InGameMenuKey();

		if (start == true && quit == false)
		{
			start = false;
			break;
		}
		if (quit == true && start == false)
		{
			break;
		}
		if (quit == true && start == true)
		{
			break;
		}
		ReturnToMenu();
	}
	if (quit == true && start == true)
	{
		main();
	}
}

void PrintInGameMenu()
{
	system("CLS");
	std::string line;
	std::ifstream myfile("main menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == "marker5")
			{
				toPrint = false;
				break;
			}
			if (toPrint)
			{
				std::cout << line << std::endl;
			}
			if (line == "marker4")
			{
				toPrint = true;
			}
		}
	}
}

//Details
void Options()
{
	PrintOptionsMenu();
	OptionsMenuKey();
	if (!useArrowKeys)
	{
		std::cout << "You have chosen SET1" << std::endl;
		std::cout << "Press 'q' to return to menu" << std::endl;
	}
	else
	{
		std::cout << "You have chosen SET2" << std::endl;
		std::cout << "Press 'q' to return to menu" << std::endl;
	}
}

// Loads Save Game
void LoadGame()
{
	std::ifstream loadFile("SafeFile.txt");
	loadFile >> fastBonusDurtion;
	loadFile >> dwarfSpeed;
	loadFile >> lastDwarfSpeed;
	loadFile >> dwarfShape;
	loadFile >> lastDwarfShape;
	loadFile >> enlargeX;
	loadFile >> enlargeY;
	loadFile >> stoneCounter;
	loadFile >> sleepDuration;
	loadFile >> isShrinked;
	loadFile >> levelCount;
	loadFile >> frameCounter;
	loadFile >> copyOfFrameCounter;
	loadFile >> rockSpawnInterval;
	loadFile >> score;
	loadFile >> dwarfColor;
	loadFile >> phaseShiftAvailable;
	loadFile >> phaseShift;
	loadFile >> phaseShiftDuration;
	loadFile >> difficulty;
	loadFile >> andromedaSkillOn;
	loadFile >> lastUsedAndroSkill;
	loadFile >> fire;
	loadFile >> lastUsedFireSkill;
	loadFile >> fireDuration;
	loadFile >> fireAvailable;
	loadFile.close();
	start = true;
	UpdateDwarf();
}
