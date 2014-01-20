#include "Variables.h"
#include "Menus.h"
#include "Skills.h"
#include <conio.h>

//Paints the dwarf in the chosen color
void ChangeColor()
{
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		switch (dwarfColor)
		{
		case 1:
			dwarfBody->Color = ConsoleColors::Blue;
			break;
		case 2:
			dwarfBody->Color = ConsoleColors::Green;
			break;
		case 3:
			dwarfBody->Color = ConsoleColors::Red;
			break;
		case 4:
			dwarfBody->Color = ConsoleColors::Yellow;
			break;
		case 5:
			dwarfBody->Color = ConsoleColors::Purple;
			break;
		case 6:
			dwarfBody->Color = ConsoleColors::Cyan;
			break;
		case 7:
			dwarfBody->Color = ConsoleColors::Smth;
			break;
		case 8:
			dwarfBody->Color = ConsoleColors::White;
			break;
		}
	}
}

//Regulates dwarf movement+shows menu, updates dwarf position
void UpdateDwarfCoordinates()
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
				if (dwarf[1].Coordinates.X + dwarfSpeed < WindowWidth)
				{
					direction.X = dwarfSpeed;
					direction.Y = 0;
				}
				else
				{
					direction.X = WindowWidth - dwarf[1].Coordinates.X - 1;
					direction.Y = 0;
				}
				break;
			case  DOWN_CHAR:
				if (dwarf[2].Coordinates.Y + dwarfSpeed < (WindowHeight - 1))
				{
					direction.X = 0;
					direction.Y = dwarfSpeed;
				}
				else
				{
					direction.X = 0;
					direction.Y = WindowHeight - 1 - dwarf[2].Coordinates.Y - 1;
				}
				break;
			case QUIT_CHAR:
				if (phaseShiftAvailable && levelCount > 4)
				{
					phaseShiftAvailable = false;
					phaseShift = true;
					phaseShiftDuration = frameCounter;
					system("CLS");
					std::cout << "You are now phase shifted ";
					Sleep(1500);
				}
				break;
			case ANDROMEDA_CHAR:
				AndromedaSkill();
				break;
			case FIRE_CHAR:
				OnFireClick();
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
				if (dwarf[2].Coordinates.Y + dwarfSpeed < (WindowHeight - 1))
				{
					direction.X = 0;
					direction.Y = dwarfSpeed;
				}
				else
				{
					direction.X = 0;
					direction.Y = WindowHeight - 1 - dwarf[2].Coordinates.Y - 1;
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
				if (dwarf[1].Coordinates.X + dwarfSpeed < WindowWidth)
				{
					direction.X = dwarfSpeed;
					direction.Y = 0;
				}
				else
				{
					direction.X = WindowWidth - dwarf[1].Coordinates.X - 1;
					direction.Y = 0;
				}
				break;
			case PhaseShift_CHAR2:
				if (phaseShiftAvailable && levelCount > 4)
				{
					phaseShiftAvailable = false;
					phaseShift = true;
					phaseShiftDuration = frameCounter;
					system("CLS");
					std::cout << "You are now phase shifted ";
					Sleep(1500);
				}
				break;
			case ANDROMEDA_CHAR2:
				AndromedaSkill();
				break;
			case FIRE_CHAR2:
				OnFireClick();
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
