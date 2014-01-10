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


using namespace std;
using namespace ConsoleColors;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 80;
const int WindowHeight = 26;

// Rock variables
char RockSymbol = '#';
int rockSpeed = 1;

// Dwarf variables
int dwarfSpeed = 3;
int lastdwarfSpeed = 3;
int dwarfShape = 1 ;
int lastDwarfShape = 1 ;
int EnlargeX = WindowWidth / 2;
int EnlargeY = WindowHeight - 2;
int dwarfColor = 8 ; 

//Counts the number of the stones
int stoneCounter = 0;

//Color variable
unsigned char colour = 0xF;

//Variables to help menu navigation,start and quit game
bool quit=false;
bool start=false;
bool tobreak=true;
bool toprint=false;

// Game variables
unsigned long sleepDuration = 200;

//Powups variables
char PowupSymbol1 = 'F';
char PowupSymbol2= 'S';
char PowupSymbol;
int  powupSpeed = 1 ;

//If the dwarf is shrinked
bool isShrinked = false;

//Level variables
int lvlCount = 1 ; 
int score = 0 ; 

//dwarf,rocks,powups vectors
vector<GameObject> dwarf;
vector<GameObject> rocks;
vector<GameObject> powups;

unsigned int frameCounter = 0;
unsigned int copyofframeCounter = 0;
unsigned int rockSpawnInterval = 10;

//Prints Character selection menu
void CharacterSelection()
{
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline (myfile,line))
	{
		if(line=="marker6") 
		{
			toprint=false;
			break;
		} 
		if(toprint==true) 
		{
			cout<<line<<endl;
		}
		if(line=="marker5") 
		{
			toprint=true;
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
	while (getline (myfile,line))
	{
		if(line=="marker7") 
		{
			toprint=false; 
			break;
		} 
		if(toprint) 
		{
			cout<<line<<endl;
		}
		if(line=="marker6") 
		{
			toprint=true;
		} 
	}
}

//Resets important global variables on starting a new game 
void Reset()
{
	dwarfSpeed = 5;
	lastdwarfSpeed = 5 ;
	dwarfShape = 1 ;
	lastDwarfShape = 1 ;
	EnlargeX = WindowWidth / 2;
	EnlargeY = WindowHeight - 2;
	stoneCounter = 0;
	colour = 0xF;
	sleepDuration = 200;
	isShrinked = false;
	lvlCount = 1 ; 
	frameCounter = 0;
	copyofframeCounter = 0;
	rockSpawnInterval = 10;
	score=0;
	dwarf.clear();
	rocks.clear();
	powups.clear();
}

//Paints the dwarf in the chosen color
void ChangeColor()
{
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		switch(dwarfColor)
		{
		case 1: dwarfBody->Color = Blue;break;
		case 2: dwarfBody->Color = Green;break;
		case 3: dwarfBody->Color = Red;break;
		case 4: dwarfBody->Color = Yellow;break;
		case 5: dwarfBody->Color = Purple;break;
		case 6: dwarfBody->Color = Cyan;break;
		case 7: dwarfBody->Color = Smth;break;
		case 8: dwarfBody->Color = White;break;
		}
	}
}

// Builds/Rebuilds dwarf shape
void UpdateDwarf()
{  
	int dwarfY = EnlargeY;  
	int dwarfX = EnlargeX;
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
	if(isShrinked)
	{
		lastDwarfShape=0;
	}

	switch(lastDwarfShape)
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
		dwarf.push_back(GameObject(dwarfX -1, dwarfY, dwarfSymbol7));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol6));//head
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body 
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol9));//legs
		break;
	case 2:
		// shape 2-Small
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX -1, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol1));//head
		dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol2));//legs
		dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
		dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body

		break;
	case 3:
		// shape 1-Big
		dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol4));//hands
		dwarf.push_back(GameObject(dwarfX -2, dwarfY, dwarfSymbol2));//legs
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
		dwarf.push_back(GameObject(dwarfX -2, dwarfY, dwarfSymbol7));//legs
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
		dwarf.push_back(GameObject(dwarfX -2, dwarfY, dwarfSymbol7));//legs
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
	while (getline (myfile,line))
	{
		if(line=="marker3") 
		{
			toprint=false; 
			break;
		} 
		if(toprint) 
		{
			cout<<line<<endl;
		}
		if(line=="marker2") 
		{
			toprint=true;
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
	while (getline (myfile,line))
	{
		if(line=="marker4") 
		{
			toprint=false; 
			break;
		}
		if(toprint) 
		{
			cout<<line<<endl;
		}
		if(line=="marker3") 
		{
			toprint=true;
		}        
	}
}

//Waiting for the rigth key to be pressed in order to choose character
void KeyToChooseModel()
{
	while(true)
	{
		if(_kbhit)
		{
			while(true)
			{
				char model;
				model=_getch();

				if(model>48 && model<54)
				{
					dwarfShape=model-48;
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
	while(true)
	{
		if(_kbhit)
		{
			while(true)
			{
				char color;
				color=_getch();

				if(color>48 && color<57)
				{
					dwarfColor=color-48;
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
	start=true;
	UpdateDwarf();
}

//User will return to  menu if secondary menu is called
void ReturnToMenu();

//Program waits for the user to press one of the following keys
void MainMenuKey()
{
	while(true)
	{
		if(_kbhit())
		{                        
			char mainmenukey=_getch();
			switch (mainmenukey)
			{
			case NEW_GAME_CHAR:
				PicksDwarfProperties();
				break;
			case CREDITS_CONTINUE_CHAR:
				Credits();
				break;
			case INSTRUCTIONS_CHAR:
				Instructions();
				break;
			case QUIT_CHAR:
				quit=true;
				break;
			default :         
				tobreak=false;
			}
			if(tobreak) 
			{
				break;
			}   
			else 
			{
				tobreak=true;
			}              
		}
	}
}

// Prints the MainMenu from "main menu.text". Markers serve as CheckPionts in the text file
void PrintmainMenu()
{
	system("CLS");
	string line;
	ifstream myfile("main menu.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			if(line=="marker1") 
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
	start=false;
	quit=false;
	while(true)
	{
		PrintmainMenu();	
		MainMenuKey();
		if(start)
		{ 
			start=false; 
			break; 
		} 
		if(quit) 
		{
			break;
		}                        
		ReturnToMenu();  
	}
}

// Writes on the screen the level on which is the game
void OutputofchangeLvl()
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
		OutputofchangeLvl();
	}
	if (frameCounter % 100 == 0 && frameCounter!=0)
	{
		lvlCount++;
		OutputofchangeLvl();
		if (sleepDuration>10)
		{
			sleepDuration-=10;
		}
		if (rockSpawnInterval > 1)
		{
			rockSpawnInterval--;
		}
		if (dwarfSpeed > 1 && lvlCount%5 == 0)
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

//InGameMenu manipulation
void InGameMenu();

//Regulates dwarf movement+shows menu, updates dwarf position
void UpdateDwarfCOORDS()
{
	COORD direction = { 0, 0 };
	if (_kbhit())
	{
		char key = getch();
		switch(key)
		{
		case LEFT_CHAR:
			if(dwarf[0].Coordinates.X - dwarfSpeed > 0 )
			{
				direction.X = - dwarfSpeed;
				direction.Y = 0 ;
			}
			else
			{
				direction.X = -dwarf[0].Coordinates.X;
				direction.Y = 0 ;
			}
			break ;
		case UP_CHAR:
			if(dwarf[3].Coordinates.Y - dwarfSpeed > 0 )
			{
				direction.X = 0 ;
				direction.Y =-dwarfSpeed;
			}
			else
			{
				direction.X = 0;
				direction.Y = -dwarf[3].Coordinates.Y;
			}
			break;
		case  RIGHT_CHAR:
			if(dwarf[1].Coordinates.X + dwarfSpeed < WindowWidth )
			{
				direction.X = dwarfSpeed ;
				direction.Y = 0;
			}
			else
			{
				direction.X = WindowWidth - dwarf[1].Coordinates.X - 1;
				direction.Y = 0 ; 
			}
			break;
		case  DOWN_CHAR:
			if(dwarf[2].Coordinates.Y + dwarfSpeed < (WindowHeight-1) )
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
		case MENU_CHAR:
			{
				InGameMenu();
			}
			break;
		};
	}
	if(quit)
	{
		return;
	}
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Coordinates.X += direction.X;
		dwarfBody->Coordinates.Y += direction.Y;
	}
	EnlargeX=dwarf[4].Coordinates.X;
	EnlargeY=dwarf[4].Coordinates.Y;
}

// Adds new elements to powup vector
void AddingPowupWithDifShapes()
{
	if (frameCounter % 50 == 0 && frameCounter != 0)
	{
		int x = rand() % WindowWidth;
		if (frameCounter % 100 == 0)
		{
			powups.push_back(GameObject(x, 0, PowupSymbol1));
			PowupSymbol = PowupSymbol1;
		}
		else
		{
			powups.push_back(GameObject(x, 0, PowupSymbol2));
			PowupSymbol = PowupSymbol2;
		}
	}
}

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
		case 0: RockSymbol = static_cast<char>(177); break;
		case 1: RockSymbol = static_cast<char>(176); break;
		case 2: RockSymbol = static_cast<char>(219); break;
		case 3: RockSymbol = static_cast<char>(220); break;
		case 4: RockSymbol = static_cast<char>(222); break;
		case 5: RockSymbol = static_cast<char>(178); break;
		case 6: RockSymbol = static_cast<char>(254); break;
		}
		stoneCounter++;
		rocks.push_back(GameObject(x, 0, RockSymbol));

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

	if(quit)
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
	for(const_iterator powup = powups.begin();powup!=powups.end();++powup)
	{
		powup->Draw(consoleHandle);
	}

}

//After a rock hits you
void AfterCollision();

//Checks for collision with rock
void Collision();

// Returns the dwarf to his previous speed or shape, after powups had expired
void DwarfPrevstatus()
{
	if(frameCounter == (copyofframeCounter+30))
	{
		if(dwarfSpeed == 13)
		{
			dwarfSpeed = lastdwarfSpeed;
		}
		if(isShrinked)
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
	dwarfSpeed = 13 ;
	system("CLS");
	cout<<"Faster"<<endl;
	Sleep(2000);
}

//Changes dwarfShape
void OutputOfShrinkBonus()
{
	isShrinked = true;
	system("CLS");
	cout<<"Shrink"<<endl;
	Sleep(2000);
	dwarf.clear();
	UpdateDwarf();
}

//Checks the bonus, changes shape or speed
void OnPowupsCollision() 
{
	copyofframeCounter = frameCounter;

	if( PowupSymbol == PowupSymbol1)
	{
		OutputOfFasterBonus(); 
	}
	if( PowupSymbol == PowupSymbol2 && !isShrinked)
	{
		OutputOfShrinkBonus();
	}
}

// Check if the dwarf has catch a powup
void PowUpCollsion()
{
	DwarfPrevstatus();
	for( const_iterator dwarfBody = dwarf.begin(); dwarfBody!=dwarf.end(); ++dwarfBody)
	{
		int dwarfX = dwarfBody->Coordinates.X;
		int dwarfY = dwarfBody->Coordinates.Y;
		for(const_iterator powup = powups.begin(); powup != powups.end();++powup )
		{
			int powupX = powup->Coordinates.X;
			int powupY= powup->Coordinates.Y;
			if( dwarfX==powupX && dwarfY==powupY)
			{
				score +=75;
				OnPowupsCollision();
				if(!powups.empty())
				{
					powups.erase(powup);
					break;
				}
			}
		}
		if(powups.empty())
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

int main()
{
	MainMenu();
	if(quit) 
	{
		return 0;
	}
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	while (true)
	{
		Update();
		if(quit) 
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
	score=stoneCounter * 15 + score; 
	system("CLS");
	cout<<"Good Game Well Played"<<endl;
	cout<<"Your score is "<<score<<endl;
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
		while(getline(myfile,line))
		{
			if(line=="marker5") 
			{
				toprint=false;
				break;
			}
			if(toprint) 
			{
				cout<<line<<endl;
			}
			if(line=="marker4") 
			{
				toprint=true;
			}
		}
	}
}

void InGameMenuKey()
{
	while(true)
	{
		if(_kbhit())
		{

			char mainmenukey=_getch();
			switch (mainmenukey)
			{
			case CREDITS_CONTINUE_CHAR:
				start=true;
				break;
			case INSTRUCTIONS_CHAR:
				Instructions();
				break;
			case MENU_CHAR:
				Reset();
				quit=true;
				start=true;
				break;
			case QUIT_CHAR:
				quit=true;
				break;
			default :                               
				tobreak=false;
			}
			if(tobreak) 
			{
				break; 
			}        
			else 
			{
				tobreak=true;
			}                
		}
	}
}

void ReturnToMenu()
{
	while(true)
	{                                
		char ingamemainmenukey=_getch();
		if(ingamemainmenukey=='q') 
		{
			break;
		}                        
	}
}

void Collision()
{
	
	for (const_iterator dwarfBody = dwarf.cbegin(); dwarfBody != dwarf.cend(); ++dwarfBody)
	{
		int testdwarfX=dwarfBody->Coordinates.X;
		int testdwarfY=dwarfBody->Coordinates.Y;
		for (const_iterator rock = rocks.cbegin(); rock != rocks.cend(); ++rock)
		{
			int testrockX=rock->Coordinates.X;
			int testrockY=rock->Coordinates.Y;
			if(testdwarfX==testrockX && testdwarfY==testrockY)
			{
				AfterCollision();
				if(quit) 
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
	while(true)
	{
		PrintInGameMenu();
		InGameMenuKey();

		if(start==true && quit==false) 
		{
			start=false;
			break;
		} 
		if(quit==true && start==false) 
		{
			break; 
		}                  
		if(quit==true && start==true) 
		{
			break; 
		}                  
		ReturnToMenu();		
	}
	if(quit==true && start==true)
	{
		main();
	}
}
