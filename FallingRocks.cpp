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
int dwarfSpeed = 5;
int lastdwarfSpeed = 5;

//Counts the number of the stones
int stoneCounter = 0;

//Color variable
unsigned char colour = 0xF;

// Game variables
unsigned long sleepDuration = 200;

//Collision detection
bool Collision = false;

//If the cmd will close
bool Stay = true;

//If the game is running
bool inGame = false;

//Powups variables
char PowupSymbol1 = 'F';
char PowupSymbol2= 'S';
char PowupSymbol;
int powupSpeed = 1 ;

//Level variables
int lvlCount = 1 ; 

vector<GameObject> dwarf;
vector<GameObject> rocks;
vector<GameObject> powups;

unsigned int frameCounter = 0;
unsigned int copyofframeCounter = 0;
unsigned int rockSpawnInterval = 10;

//void CheckCollision (int rockXCoord, int rockYCoord)
//{
//   for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
//   {
//       if(dwarfBody->Coordinates.X == rockXCoord && dwarfBody->Coordinates.Y == rockYCoord)
//       {
//			Collision = true;
//			break;
//       }
//   }
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
                cout << "2 - Game intructions" << endl;
                cout << "3 - Show your highest score" << endl;
                cout << "4 - Exit the game" << endl;
                cout << "You can always retun to this menu by pressing the M key" << endl;
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
	if (_kbhit())
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
			//CheckCollision(rock->Coordinates.X, rock->Coordinates.Y);
		}
		else
		{
			++rock;
			//CheckCollision((rock - 1)->Coordinates.X, (rock - 1)->Coordinates.Y);
		}
		
	}

	if (frameCounter % rockSpawnInterval == 0)
	{
		// Spawn a new rock at every x frames
		int x = rand() % WindowWidth;
		//		The original RockSymbol
		//		rocks.push_back(GameObject(x, 0, RockSymbol));

		//      Rocks in defferent shapes
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
		GameObject go = GameObject(x, 0, RockSymbol);
		rocks.push_back(go);
		
		if (stoneCounter == 2) rocks[0].Color = colour;

		//It makes stones colorful

		//[BUG] The first stone changes it's color after the second one appears - partly resolved
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

		//rocks.push_back(GameObject(x, 0, RockSymbol));
	}


	//  Creating Power Ups similar to the rock Object
	for (randomAccess_iterator powup = powups.begin(); powup != powups.end(); /* Empty clause so we can delete elements */)
	{
		powup->Coordinates.Y += powupSpeed;
		if (powup->Coordinates.Y > WindowHeight - 1)
		{
			powup = powups.erase(powup);
		}
		else
		{
			++powup;
		}
		// CheckCollision(rock->Coordinates.X,rock->Coordinates.Y);
	}
	if (frameCounter % 50 == 0 && frameCounter != 0)
	{
		// Spawn a new powup at every x frames
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

		// Change Level
		if (frameCounter == 0)
		{
			system("CLS");
			cout << "Level " << lvlCount << endl;
			system("pause");
		}
		if (frameCounter % 100 == 0)
		{
			lvlCount++;
			system("CLS");
			cout << "Level " << lvlCount << endl;
			system("pause");
			rockSpeed++;
			if (rockSpawnInterval > 1)
			{
				rockSpawnInterval--;
			}
			if (dwarfSpeed > 1)
			{
				dwarfSpeed--;
			}
		}
	}
	frameCounter++;
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
       // Drawing the PowUps
         for(const_iterator powup = powups.begin();powup!=powups.end();++powup)
        {
                powup->Draw(consoleHandle);
        }

}
void PowUpCollsion()
{
    if(frameCounter == (copyofframeCounter+30))
    {
       if(dwarfSpeed == 10)
       {
           dwarfSpeed = lastdwarfSpeed;
       }
    }
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
                copyofframeCounter = frameCounter;
                if( PowupSymbol == PowupSymbol1)
                {
                 dwarfSpeed = 10 ;
                 system("CLS");
                 cout<<"Faster"<<endl;
                 system("pause");
                }
                if( PowupSymbol == PowupSymbol2)
                {
                    system("CLS");
                    cout<<"Shrink"<<endl;
                    system("pause");
                }
            }
        }
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
        char dwarfSymbol1 = '0';
        char dwarfSymbol2 = '^';
        char dwarfSymbol3 = '|';
        char dwarfSymbol4 = '~';
        char dwarfSymbol5 = '^^';
        char dwarfSymbol6 = '#';
        char dwarfSymbol7 = '/';
        char dwarfSymbol8 = '-';
        char dwarfSymbol9 = '\\';
        //  Dwarf shape 1-Small
        /*
               dwarf.push_back(GameObject(dwarfX - 1, dwarfY, dwarfSymbol7));
                dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol9));
                dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));
                dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));
                dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol2));
                dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol2));
                dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol1));

        //Shape 1-Big
        
        dwarf.push_back(GameObject(dwarfX -2, dwarfY, dwarfSymbol7));//legs
        dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol9));//legs
        dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol));//Body
        dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol2));//hands
        dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol2));//hands
        dwarf.push_back(GameObject(dwarfX, dwarfY - 4, dwarfSymbol1));//head
        
        // shape 2-Small
     */
       dwarf.push_back(GameObject(dwarfX -1, dwarfY, dwarfSymbol2));//legs
        dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol2));//legs
        dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol4));//hands
        dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol4));//hands
        dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol1));//head
        
        
       /*   // shape 2-Big
        dwarf.push_back(GameObject(dwarfX -2, dwarfY, dwarfSymbol2));//legs
        dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol2));//legs
        dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol4));//hands
        dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol4));//hands
        dwarf.push_back(GameObject(dwarfX, dwarfY - 4, dwarfSymbol1));//head 


        //Shape 3-small
        dwarf.push_back(GameObject(dwarfX -1, dwarfY, dwarfSymbol7));//legs
        dwarf.push_back(GameObject(dwarfX + 1, dwarfY, dwarfSymbol9));//legs
        dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol8));//hands
        dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol8));//hands
        dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol6));//head
        
    
        //Shape 3-Big
        dwarf.push_back(GameObject(dwarfX -2, dwarfY, dwarfSymbol7));//legs
        dwarf.push_back(GameObject(dwarfX + 2, dwarfY, dwarfSymbol9));//legs
        dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX - 2, dwarfY - 2, dwarfSymbol8));//hands
        dwarf.push_back(GameObject(dwarfX + 2, dwarfY - 2, dwarfSymbol8));//hands
        dwarf.push_back(GameObject(dwarfX, dwarfY - 4, dwarfSymbol6));//head  
        */   
        ShowMenu();
        inGame = true;
        while (Stay)
        {
                //Stay = Update();
            Update();
			PowUpCollsion();
                if (Stay == false)
                {
                        break;
                }
                Draw();
				//if (Collision) break;
                Sleep(sleepDuration);
        }

        return 0;
}

