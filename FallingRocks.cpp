#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iomanip>

#include "ConsoleGaming.h"

using namespace std;
using namespace ConsoleColors;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 80;
const int WindowHeight = 20;

// Rock variables
char RockSymbol = '#';
int rockSpeed = 1;

// Dwarf variables
int dwarfSpeed = 1;

// Game variables
unsigned long sleepDuration = 200;

//Collision detection
bool Collision = false;

//If the cmd will close
bool Stay = true;

//If the game is running
bool inGame = false;

vector<GameObject> dwarf;
vector<GameObject> rocks;

unsigned int frameCounter = 0;
unsigned int rockSpawnInterval = 10;

//void CheckCollision (int rockXCoord, int rockYCoord)
//{
//   bool Collided = false;
//   for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
//   {
//       if(dwarfBody->Coordinates.X == rockXCoord && dwarfBody->Coordinates.Y == rockYCoord)
//       {
//           Collided = true;
//       }
//   }
//   Collision = Collided;
//}

void ShowMenu()
{
    ClearScreen(consoleHandle);
	cout << " _____     _ _ _               ____            _" << endl;
	cout << "|  ___|_ _| | (_)_ __   __ _  |  _ \\ ___   ___| | _____" << endl;
	cout << "| |_ / _` | | | | '_ \\ / _` | | |_) / _ \\ / __| |/ / __|" << endl;
	cout << "|  _| (_| | | | | | | | (_| | |  _ < (_) | (__|   <\\__ \\" << endl;
	cout << "|_|  \\__,_|_|_|_|_| |_|\\__, | |_| \\_\\___/ \\___|_|\\_\\___/" << endl;
	cout << "                       |___/" << endl;
	int choice = 1;
	if (!inGame)
	{
		cout << "Choose an option:" << endl;
		cout << "1 - Start a new game" << endl;
		cout << "2 - Game instructions" << endl;
		cout << "3 - Show your highest score" << endl;
		cout << "4 - Exit the game" << endl;
		cout << "You can always return to this menu by pressing the M key" << endl;
	}
	else
	{
		cout << "Choose an option:" << endl;
		cout << "1 - Resume the game" << endl;
		cout << "2 - Start a new game" << endl;
		cout << "3 - Game intructions" << endl;
		cout << "4 - Show your highest score" << endl;
		cout << "5 - Exit the game" << endl;
		cout << "You can always retun to this menu by pressing the M key" << endl;
	}
	cin >> choice;
	switch (choice)
	{
		case 1:
		{
			return;
		}
		case 2:
		{
			if (inGame)
			{
		      /*
			    rockSpeed = 1;
				dwarfSpeed = 1;
				sleepDuration = 200;
				Collision = false;
				Stay = true;
				inGame = false;
				frameCounter = 0;
				rockSpawnInterval = 10;
				goto MainFunk;
				*/
				break;
			  
			}
		}
		case 4:
		{
			if (!inGame)
			{
				Stay = false;
				break;
			}
		}
		case 5:
		{
			if (inGame)
			{
				Stay = false;
				break;
			}
		}
	}
	
}

void Update()
{
	COORD direction = { 0, 0 };
	if (kbhit())
	{
		char key = getch();
		switch (key)
		{
		case 'a':
			direction.X = -dwarfSpeed;
			direction.Y = 0;
			break;
		case 'w':
			direction.X = 0;
			direction.Y = -dwarfSpeed;
			break;
		case 'd':
			direction.X = dwarfSpeed;
			direction.Y = 0;
			break;
		case 's':
			direction.X = 0;
			direction.Y = dwarfSpeed;
			break;
		case 'm':
			ShowMenu();
			break;
		};
	}
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Coordinates.X += direction.X;
		dwarfBody->Coordinates.Y += direction.Y;
		//dwarfBody->Color = Green;
	}

	// Update the position of all rocks. Remove any rock that goes outside the window

	for (randomAccess_iterator rock = rocks.begin(); rock != rocks.end(); /* Empty clause so we can delete elements */)
	{
		rock->Coordinates.Y += rockSpeed;
		if (rock->Coordinates.Y > WindowHeight - 1)
		{
			rock = rocks.erase(rock);
		}
		else
		{
			++rock;
		}
		// CheckCollision(rock->Coordinates.X,rock->Coordinates.Y);
	}

	if (frameCounter % rockSpawnInterval == 0)
	{
		// Spawn a new rock at every x frames
		int x = rand() % WindowWidth;
		//		The original RockSymbol
		//		rocks.push_back(GameObject(x, 0, RockSymbol));

		rocks.push_back(GameObject(x, 0, RockSymbol));

		//      Rocks in defferent shapes
		int shapeNum = rand() % 7;
		switch (shapeNum)
		{
			case 1: RockSymbol = static_cast<char>(176); break;
			case 2: RockSymbol = static_cast<char>(219); break;
			case 3: RockSymbol = static_cast<char>(220); break;
			case 4: RockSymbol = static_cast<char>(222); break;
			case 5: RockSymbol = static_cast<char>(178); break;
			case 6: RockSymbol = static_cast<char>(254); break;
		}

		//Make stones colorful
		randomAccess_iterator rock = rocks.end() - 1;
		switch (shapeNum)
		{
		case 1: rock->Color = Red; break;
		case 2: rock->Color = Blue; break;
		case 3: rock->Color = White; break;
		case 4: rock->Color = Yellow; break;
		case 5: rock->Color = Purple; break;
		case 6: rock->Color = Cyan; break;
		}

		//rocks.push_back(GameObject(x, 0, RockSymbol));
	}
	++frameCounter;
}

void Draw()
{
	ClearScreen(consoleHandle);
	//   if(!Collision)
	for (const_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Draw(consoleHandle);
	}

	for (const_iterator rock = rocks.begin(); rock != rocks.end(); ++rock)
	{
		rock->Draw(consoleHandle);
	}

}

int main()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	int dwarfY = WindowHeight;
	//  int dwarfY = WindowHeight - 1;
	int dwarfX = WindowWidth / 2;

	char dwarfSymbol = '*';

	//  Dwarf shape 1
	//  dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol));

	//  Dwarf shape 2
	char dwarfSymbol1 = '#';
	char dwarfSymbol2 = '^';
	dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol2));
	dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol2));
	dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol1));
	dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol1));
	dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol));
	dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol));
	dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol));

	//  The original shape ot the dwarf
	//	dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 1, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 1, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX, dwarfY, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX - 1, dwarfY + 1, dwarfSymbol));
	//	dwarf.push_back(GameObject(dwarfX + 1, dwarfY + 1, dwarfSymbol));

	ShowMenu();
	inGame = true;
	while (Stay)
	{
		//Stay = Update();
	    Update();
		if (Stay == false)
		{
			break;
		}
		Draw();
		Sleep(sleepDuration);
	}

	return 0;
}
