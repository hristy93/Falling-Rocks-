#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "ConsoleGaming.h"

#define QUIT_CHAR 'q'
#define MENU_CHAR 'm'
#define NEW_GAME_CHAR 'n'
#define INSTRUCTIONS_CHAR 'i'
#define CREDITS_CONTINUE_CHAR 'c'
#define UP_CHAR 'w'
#define DOWN_CHAR 's'
#define LEFT_CHAR 'a'
#define RIGHT_CHAR 'd'
#define FAME_CHAR 'h'
#define SAVE_CHAR 's'
#define LOAD_CHAR 'l'
#define OPTIONS_CHAR 'o'


using namespace std;
using namespace ConsoleColors;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int windowWidth = 80;
const int windowHeight = 26;

// Rock variables
char rockSymbol = '#';
int rockSpeed = 1;

// Dwarf variables
int dwarfSpeed = 3;
int lastDwarfSpeed = 3;
int dwarfShape = 1;
int lastDwarfShape = 1;
int enlargeX = windowWidth / 2;
int enlargeY = windowHeight - 2;
int dwarfColor = 8;

//Counts the number of the stones
int stoneCounter = 0;

//Color variable
unsigned char colour = 0xF;

//Variables to help menu navigation,start and quit game
bool quit = false;
bool start = false;
bool toBreak = true;
bool toPrint = false;

// Game variables
unsigned long sleepDuration = 200;

//Powups variables
char powupSymbol1 = 'F';
char powupSymbol2 = 'S';
char powupSymbol;
int  powupSpeed = 1;

//If the dwarf is shrinked
bool isShrinked = false;

//To use the arrow keys
bool useArrowKeys = false;

//Level variables
int lvlCount = 1;
int score = 0;
int highScore = 0;

//dwarf,rocks,powups vectors
vector<GameObject> dwarf;
vector<GameObject> rocks;
vector<GameObject> powups;

unsigned int frameCounter = 0;
unsigned int copyOfFrameCounter = 0;
unsigned int rockSpawnInterval = 10;

//Prints Character selection menu
void CharacterSelection()
{
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline(myfile, line))
	{
		if (line == "marker6")
		{
			toPrint = false;
			break;
		}
		if (toPrint == true)
		{
			cout << line << endl;
		}
		if (line == "marker5")
		{
			toPrint = true;
		}
	}
}

//Prints charater solor selection menu
void CharacterColorSelection()
{
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline(myfile, line))
	{
		if (line == "marker7")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			cout << line << endl;
		}
		if (line == "marker6")
		{
			toPrint = true;
		}
	}
}

//Resets important global variables on starting a new game 
void Reset()
{
	dwarfSpeed = 5;
	lastDwarfSpeed = 5;
	dwarfShape = 1;
	lastDwarfShape = 1;
	enlargeX = windowWidth / 2;
	enlargeY = windowHeight - 2;
	stoneCounter = 0;
	colour = 0xF;
	sleepDuration = 200;
	isShrinked = false;
	lvlCount = 1;
	frameCounter = 0;
	copyOfFrameCounter = 0;
	rockSpawnInterval = 10;
	if(score > highScore)
	{
		highScore = score;
	}
	score = 0;
	dwarf.clear();
	rocks.clear();
	powups.clear();
}

//Paints the dwarf in the chosen color
void ChangeColor()
{
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		switch (dwarfColor)
		{
		case 1: dwarfBody->Color = Blue; break;
		case 2: dwarfBody->Color = Green; break;
		case 3: dwarfBody->Color = Red; break;
		case 4: dwarfBody->Color = Yellow; break;
		case 5: dwarfBody->Color = Purple; break;
		case 6: dwarfBody->Color = Cyan; break;
		case 7: dwarfBody->Color = Smth; break;
		case 8: dwarfBody->Color = White; break;
		}
	}
}

// Builds/Rebuilds dwarf shape
void UpdateDwarf()
{
	int dwarfY = enlargeY;
	int dwarfX = enlargeX;
	char dwarfSymbol = '*';
	char dwarfSymbol1 = '0';
	char dwarfSymbol2 = '^';
	char dwarfSymbol3 = '|';
	char dwarfSymbol4 = '~';
	char dwarfSymbol5 = '^^';
	char dwarfSymbol6 = '#';
	char dwarfSymbol7 = '/';
	char dwarfSymbol8 = '-';
	char dwarfSymbol9 = '\\';
	if (isShrinked)
	{
		lastDwarfShape = 0;
	}

	switch (lastDwarfShape)
	{
		// Shrink bonus shape
	case 0:
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol2));
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol2));
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol1));
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));
		break;
	case 1:
		//Shape 1-small    
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol8));//hands
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol8));//hands
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol7));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol6));//head
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body 
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol9));//legs
		break;
	case 2:
		// shape 2-Small
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol1));//head
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body

		break;
	case 3:
		// shape 1-Big
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 4, dwarfSymbol1));//head 
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol4));//arms
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol4));//arms
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol2));//legs
		break;
	case 4:

		//Shape 2-Big
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol2));//hands
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol2));//hands
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol7));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 4, dwarfSymbol1));//head
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol2));//arms
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol2));//arms
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol));//Body
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol9));//legs 
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol7));//legs 
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol9));//legs 
		break;
	case 5:
		//Shape 3-Big
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol8));//hands
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol8));//hands
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY, dwarfSymbol7));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 4, dwarfSymbol6));//head  
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol3));//Body 
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol8));//arms
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol8));//arms
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol9));//legs 
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol9));//legs 
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol7));//legs 
		break;
	}
	lastDwarfShape = dwarfShape;
	ChangeColor();
}

//Prints the credits menu
void Credits()
{
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline(myfile, line))
	{
		if (line == "marker3")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			cout << line << endl;
		}
		if (line == "marker2")
		{
			toPrint = true;
		}
	}
}

//Prints the instructions menu
void Instructions()
{
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline(myfile, line))
	{
		if (line == "marker4")
		{
			toPrint = false;
			break;
		}
		if (toPrint)
		{
			cout << line << endl;
		}
		if (line == "marker3")
		{
			toPrint = true;
		}
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

//User will return to  menu if secondary menu is called
void ReturnToMenu();

//Hall of fame result 
void HallOfFame()
{
	system("CLS");
    cout<<"Your highscore is "<<highScore<<endl;
}
// Loads Save Game
void LoadGame()
{
	ifstream loadFile("Safefile1.txt");
	loadFile>>dwarfSpeed;
	loadFile>>lastDwarfSpeed;
    loadFile>>dwarfShape;
	loadFile>>lastDwarfShape;
	loadFile>>enlargeX;
	loadFile>>enlargeY;
	loadFile>>stoneCounter;
	loadFile>>sleepDuration;
	loadFile>>isShrinked;
	loadFile>>lvlCount;
	loadFile>>frameCounter;
	loadFile>>copyOfFrameCounter;
	loadFile>>rockSpawnInterval;
	loadFile>>score;
	loadFile>>dwarfColor;
	lastDwarfShape=dwarfShape;
    loadFile.close();
	start = true ;
	UpdateDwarf();
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
	string line;
	ifstream myfile("main menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == "marker1")
			{
				break;
			}
			cout << line << endl;
		}
	}
}

//MainMenu  manipulation
void MainMenu()
{
	//PlaySound(TEXT("secret.wav"), NULL, SND_FILENAME|SND_ASYNC);
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

// Writes on the screen the level on which is the game
void OutputOfChangeLvl()
{
	system("CLS");
	cout << "Level " << lvlCount << endl;
	Sleep(2000);
}

// Change Level
void ChangeLvl()
{
	if (frameCounter == 0)
	{
		OutputOfChangeLvl();
	}
	if (frameCounter % 100 == 0 && frameCounter != 0)
	{
		lvlCount++;
		OutputOfChangeLvl();
		if (sleepDuration > 10)
		{
			sleepDuration -= 10;
		}
		if (rockSpawnInterval > 1)
		{
			rockSpawnInterval--;
		}
		if (dwarfSpeed > 1 && lvlCount % 5 == 0)
		{
			dwarfSpeed--;
		}
	}
}

//Creates and deletes powerups
void CreatingPowups()
{
	for (randomAccess_iterator powup = powups.begin(); powup != powups.end(); /* Empty clause so we can delete elements */)
	{
		powup->Coordinates.Y += powupSpeed;
		if (powup->Coordinates.Y > windowHeight - 2)
		{
			powup = powups.erase(powup);
		}
		else
		{
			++powup;
		}
	}
}

//Creates and deletes rocks
void CreatingRocks()
{
	for (randomAccess_iterator rock = rocks.begin(); rock != rocks.end(); /* Empty clause so we can delete elements */)
	{
		rock->Coordinates.Y += rockSpeed;
		if (rock->Coordinates.Y > windowHeight - 2)
		{
			rock = rocks.erase(rock);
		}
		else
		{
			++rock;
		}
	}
}

//InGameMenu manipulation
void InGameMenu();

//Regulates dwarf movement+shows menu, updates dwarf position
void UpdateDwarfCOORDS()
{
	COORD direction = { 0, 0 };
	char key;
	if (!useArrowKeys)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case LEFT_CHAR:
				if (dwarf[0].Coordinates.X - dwarfSpeed > 0)
				{
					direction.X = -dwarfSpeed;
					direction.Y = 0;
				}
				else
				{
					direction.X = -dwarf[0].Coordinates.X;
					direction.Y = 0;
				}
				break;
			case UP_CHAR:
				if (dwarf[3].Coordinates.Y - dwarfSpeed > 0)
				{
					direction.X = 0;
					direction.Y = -dwarfSpeed;
				}
				else
				{
					direction.X = 0;
					direction.Y = -dwarf[3].Coordinates.Y;
				}
				break;
			case  RIGHT_CHAR:
				if (dwarf[1].Coordinates.X + dwarfSpeed < windowWidth)
				{
					direction.X = dwarfSpeed;
					direction.Y = 0;
				}
				else
				{
					direction.X = windowWidth - dwarf[1].Coordinates.X - 1;
					direction.Y = 0;
				}
				break;
			case  DOWN_CHAR:
				if (dwarf[2].Coordinates.Y + dwarfSpeed < (windowHeight - 1))
				{
					direction.X = 0;
					direction.Y = dwarfSpeed;
				}
				else
				{
					direction.X = 0;
					direction.Y = windowHeight - 1 - dwarf[2].Coordinates.Y - 1;
				}
				break;
			case MENU_CHAR:
				InGameMenu();
				break;
			};
		}
	}
	else
	{
		unsigned char key;
		if (_kbhit())
		{
			system("CLS");
			key = _getch();
			//for detect the function\arrow keys 
			//we must call the getch() again
			//testing if a is '0' or '0xE0'
			if (key == 0 || key == 0xE0) key = _getch();
			switch (key)
			{
			case 72: //Up
				if (dwarf[3].Coordinates.Y - dwarfSpeed > 0)
				{
					direction.X = 0;
					direction.Y = -dwarfSpeed;
				}
				else
				{
					direction.X = 0;
					direction.Y = -dwarf[3].Coordinates.Y;
				}
				break;

			case 80: //Down
				if (dwarf[2].Coordinates.Y + dwarfSpeed < (windowHeight - 1))
				{
					direction.X = 0;
					direction.Y = dwarfSpeed;
				}
				else
				{
					direction.X = 0;
					direction.Y = windowHeight - 1 - dwarf[2].Coordinates.Y - 1;
				}
				break;

			case 75: //Left
				if (dwarf[0].Coordinates.X - dwarfSpeed > 0)
				{
					direction.X = -dwarfSpeed;
					direction.Y = 0;
				}
				else
				{
					direction.X = -dwarf[0].Coordinates.X;
					direction.Y = 0;
				}
				break;

			case 77: //Right
				if (dwarf[1].Coordinates.X + dwarfSpeed < windowWidth)
				{
					direction.X = dwarfSpeed;
					direction.Y = 0;
				}
				else
				{
					direction.X = windowWidth - dwarf[1].Coordinates.X - 1;
					direction.Y = 0;
				}
				break;
				case MENU_CHAR:
				InGameMenu();
				break;
			}
		}
	}
	if (quit)
	{
		return;
	}
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Coordinates.X += direction.X;
		dwarfBody->Coordinates.Y += direction.Y;
	}
	enlargeX = dwarf[4].Coordinates.X;
	enlargeY = dwarf[4].Coordinates.Y;
}

//Checks if a rock and a powerup have the same x coordinate
void CheckForRockAndPowupIntersection(int &x)
{
	bool cycleRand = false;
	do
	{
		x = rand() % windowWidth;
		for (const_iterator rock = rocks.begin(); rock != rocks.end(); ++rock)
		{
			if (x == rock->Coordinates.X)
			{
				cycleRand = true;
			}
		}
	} while (cycleRand);
}

// Adds new elements to powup vector
void AddingPowupWithDifShapes()
{
	if (frameCounter % 50 == 0 && frameCounter != 0)
	{
		int x = 1;
		CheckForRockAndPowupIntersection(x);
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

//Randomises rock shape and color
void RocksShapeAndColor()
{
	if (frameCounter % rockSpawnInterval == 0)
	{
		int x = rand() % windowWidth;

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

		if (stoneCounter == 2) rocks[0].Color = colour;

		//It makes stones colorful
		randomAccess_iterator rock = rocks.end() - 1;
		switch (shapeNum)
		{
		case 0: rock->Color = Green; break;
		case 1: rock->Color = Red; break;
		case 2: rock->Color = Blue; break;
		case 3: rock->Color = Grey; break;
		case 4: rock->Color = Yellow; break;
		case 5: rock->Color = Purple; break;
		case 6: rock->Color = Cyan; break;
		}
		colour = rock->Color;
	}
}

//Updates everything
void Update()
{

	UpdateDwarfCOORDS();
	ChangeColor();

	CreatingRocks();
	RocksShapeAndColor();

	CreatingPowups();
	AddingPowupWithDifShapes();

	if (quit)
	{
		return;
	}
	ChangeLvl();
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

}

//After a rock hits you
void AfterCollision();

//Checks for collision with rock
void Collision();

// Returns the dwarf to his previous speed or shape, after powups had expired
void DwarfPrevStatus()
{
	if (frameCounter == (copyOfFrameCounter + 30))
	{
		if (dwarfSpeed == 13)
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

//Changes dwarfspeed
void OutputOfFasterBonus()
{
	dwarfSpeed = 13;
	system("CLS");
	cout << "Faster" << endl;
	Sleep(2000);
}

//Changes dwarfShape
void OutputOfShrinkBonus()
{
	isShrinked = true;
	system("CLS");
	cout << "Shrink" << endl;
	Sleep(2000);
	dwarf.clear();
	UpdateDwarf();
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

// Check if the dwarf has catch a powup
void PowUpCollsion()
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

//Program waits for the user to press one of the following keys
void InGameMenuKey();

// Prints the InGameMenu from "main menu.text". Markers serve as CheckPionts in the text file
void PrintInGameMenu();

//Return to InGAmeMenu from secondary menu
void ReturnToInGameMenu();

//Saves your game
void SaveGame();
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
		PowUpCollsion();
		Draw();
		Sleep(sleepDuration);
	}
	return 0;
}

void AfterCollision()
{
	score = stoneCounter * 15 + score;
	system("CLS");
	cout << "Good Game Well Played" << endl;
	cout << "Your score is " << score << endl;
	Sleep(2000);
	Reset();
	main();
}

void PrintInGameMenu()
{
	system("CLS");
	string line;
	ifstream myfile("main menu.txt");
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
				cout << line << endl;
			}
			if (line == "marker4")
			{
				toPrint = true;
			}
		}
	}
}
void SaveGame()
{
	score = stoneCounter*15+score;
	ofstream saveFile("Safefile1.txt");
	saveFile<<dwarfSpeed<<endl;
	saveFile<<lastDwarfSpeed<<endl;
	saveFile<<dwarfShape<<endl;
	saveFile<<lastDwarfShape<<endl;
	saveFile<<enlargeX<<endl;
	saveFile<<enlargeY<<endl;
	saveFile<<stoneCounter<<endl;
	saveFile<<sleepDuration<<endl;
	saveFile<<isShrinked<<endl;
	saveFile<<lvlCount<<endl;
	saveFile<<frameCounter<<endl;
	saveFile<<copyOfFrameCounter<<endl;
	saveFile<<rockSpawnInterval<<endl;
	saveFile<<score<<endl;
	saveFile<<dwarfColor<<endl;
    saveFile.close();
	system("CLS");
	cout<<"Your game has been saved"<<endl;
	cout<<"Press q to return to menu"<<endl;
	Sleep(1500);
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
				AfterCollision();
				if (quit)
				{
					return;
				}
			}
		}
	}
}

void InGameMenu()
{
	//PlaySound(TEXT("secret.wav"), NULL, SND_FILENAME|SND_ASYNC);
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
