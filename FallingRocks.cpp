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

using namespace std;
using namespace ConsoleColors;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 80;
const int WindowHeight = 25;

// Rock variables
char RockSymbol = '#';
int rockSpeed = 1;

// Dwarf variables
int dwarfSpeed = 3;
int lastdwarfSpeed = 5;
int dwarfShape = 1 ;
int lastDwarfShape = 1 ;
int EnlargeX=WindowWidth / 2;
int EnlargeY=WindowHeight;

//Counts the number of the stones
int stoneCounter = 0;

//Color variable
unsigned char colour = 0xF;

//Variables to help menu navigation,start and quit game
bool quit=0;
bool start=0;
bool tobreak=1;
bool toprint=0;

// Game variables
unsigned long sleepDuration = 200;

//Collision detection
//incompetable with void Collision had to remove it

//If the cmd will close
bool Stay = true;  //change Stay to quit or vice versa, discusss on next team metting
		   //not used in current build

//If the game is running
bool inGame = false;  //change inGame to start or vice versa, discusss on next team metting
		      //not used in current build

//Powups variables
char PowupSymbol1 = 'F';
char PowupSymbol2= 'S';
char PowupSymbol;
int powupSpeed = 1 ;

//If the dwarf is shrinked
bool isShrinked = false;

//Level variables
int lvlCount = 1 ; 

//dwarf,rocks,powups vectors
vector<GameObject> dwarf;
vector<GameObject> rocks;
vector<GameObject> powups;

//Stack for saving the dwarfs vectors
unsigned int frameCounter = 0;
unsigned int copyofframeCounter = 0;
unsigned int rockSpawnInterval = 10;

void Reset()
{
// Dwarf variables
dwarfSpeed = 3;
lastdwarfSpeed = 5;
dwarfShape = 1 ;
lastDwarfShape = 1 ;
EnlargeX=WindowWidth / 2;
EnlargeY=WindowHeight;
//Counts the number of the stones
stoneCounter = 0;

//Color variable
colour = 0xF;

// Game variables
sleepDuration = 200;

//Collision detection
//incompetable with void Collision had to remove it

//If the cmd will close
Stay = true;  //change Stay to quit or vice versa, discusss on next team metting
		   //not used in current build

//If the game is running
inGame = false;  //change inGame to start or vice versa, discusss on next team metting
		      //not used in current build

//If the dwarf is shrinked
isShrinked = false;

//Level variables
lvlCount = 1 ; 

//Counts frames;
frameCounter = 0;
copyofframeCounter = 0;
rockSpawnInterval = 10;
dwarf.clear();
rocks.clear();
powups.clear();
}

// Chosing dwarf and returing the lastdwarf after shrink
void LastDwarf()
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
		//   int  dwarfX = dwarf->Coordinates.X;
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
        //Shape 1-Big
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
        // shape 2-Big
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
        //Shape 3-small    
		dwarf.push_back(GameObject(dwarfX - 1, dwarfY - 2, dwarfSymbol8));//hands
        dwarf.push_back(GameObject(dwarfX + 1, dwarfY - 2, dwarfSymbol8));//hands
        dwarf.push_back(GameObject(dwarfX -1, dwarfY, dwarfSymbol7));//legs
        dwarf.push_back(GameObject(dwarfX, dwarfY - 3, dwarfSymbol6));//head
        dwarf.push_back(GameObject(dwarfX, dwarfY - 1, dwarfSymbol3));//Body
        dwarf.push_back(GameObject(dwarfX, dwarfY - 2, dwarfSymbol3));//Body 
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
}

void Credits()
{
	// Prints the Credits from "main menu.text". Markers serve as CheckPionts in the text file
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline (myfile,line))
	{
		if(line=="marker3") {toprint=0; break;} // cycle ends whene marker3 is reached
		if(toprint==1) {cout<<line<<endl;}
		if(line=="marker2") {toprint=1;} // Prints everyline below marker2
	}

}

void Instructions()
{
	// Prints the Credits from "main menu.text". Markers serve as CheckPionts in the text file
	string line;
	ifstream myfile("main menu.txt");
	system("CLS");
	myfile.seekg(ios::beg);
	while (getline (myfile,line))
	{
		if(line=="marker4") {toprint=0; break;} // cycle ends whene marker4 from the text  file is reached
		if(toprint==1) {cout<<line<<endl;}
		if(line=="marker3") {toprint=1;}	// Prints everyline below marker3 in the text  file
	}
}

void MainMenu()
{
    //PlaySound(TEXT("kamanitepadat.wav"), NULL, SND_FILENAME|SND_ASYNC);
	//reseting Global variables if MainMenu() is called from InGameMenu()
	start=0;
	quit=0;
	while(true)
	{

		// Prints the MainMenu from "main menu.text". Markers serve as CheckPionts in the text file
		system("CLS");
		string line;
		ifstream myfile("main menu.txt");
		if (myfile.is_open())
		{
			while ( getline (myfile,line) )
			{
				if(line=="marker1") {break;} // cycle ends whene marker1 from the text  file is reached
				cout << line << endl;
			}
		    //Printing ends

			//Program waits for the user to press one of the following keys
			while(true)
			{
				if(_kbhit())
				{			
					char mainmenukey=_getch();
					switch (mainmenukey)
					{
					case 'n':
							//make a function for reseting every game variable
							//make a function to empty the dwarf,rock and powup vectors if not empty
							//include a "choose a character" function here maybe
							//see if this works
						    Reset();
						    cin >> dwarfShape;
							lastDwarfShape = dwarfShape;
							start=1;
							LastDwarf();
							break;
					case 'c':
							Credits();
							break;
					case 'i':
							Instructions();
							break;
					case 'q':
							quit=true;
							break;
					default :              //preventinf a bug part 1   
							tobreak=false;
					}
					if(tobreak) {break;}   //preventing a bug
					else {tobreak=1;}		  //part 2
				}
			}
		}

		if(start) { start=0; break; } // Game starts, first way to end cycle
		if(quit)  {break;}			 // cycle ends, game will quit to windows

		//user will return to main menu if credits() or instructions() is called
		while(true)
		{				
			char mainmenukey=_getch();
			if(mainmenukey==QUIT_CHAR) {break;}			
		}	
	}
}

void InGameMenu()
{
//	PlaySound(TEXT("kamanitepadat.wav"), NULL, SND_FILENAME|SND_ASYNC);
	while(true)
	{
		
		// Prints the MainMenu from "main menu.text". Markers serve as CheckPionts in the text file
		system("CLS");
		string line;
		ifstream myfile("main menu.txt");
		if (myfile.is_open())
		{
			while(getline(myfile,line))
			{
				if(line=="marker5") {toprint=0; break;} // cycle ends whene marker5 from the text  file is reached
				if(toprint==1) {cout<<line<<endl;}
				if(line=="marker4") {toprint=1;}
			}
			//Printing ends

			//Program waits for the user to press one of the following keys
			while(true)
			{
				if(_kbhit())
				{
				
					char mainmenukey=_getch();
					switch (mainmenukey)
					{
					case 'c':
							start=1;
							break;
					case 'i':
							Instructions();
							break;
					case 'm':
							quit=1;
							start=1;
							break;
					case 'q':
							quit=1;
							break;
					default :				 //preventinf a bug part 1 
							tobreak=0;
					}
					if(tobreak!=0) {break;}	//preventing a bug
					else {tobreak=1;}		//part 2
				}
			}
		}
		if(start==1 && quit==0) {start=0; break;} //game will contunie
		if(quit==1 && start==0) {break;}		  //game will quit
		if(quit==1 && start==1) {break;}		  //game will return to main menu

		//user will return to main menu if instructions() is called
		while(true)
		{				
			char ingamemainmenukey=_getch();
			if(ingamemainmenukey=='q') {break;}			
		}
	}
	if(quit==1 && start==1) MainMenu();		//game returns to main menu
}
// Writes on the screen the level on which is the game
void outputofchangeLvl()
{
		system("CLS");
		cout << "Level " << lvlCount << endl;
		Sleep(2000);
}
// Change Level
void changeLvl()
{
	if (frameCounter == 0)
		{
		   outputofchangeLvl();
		}
		if (frameCounter % 100 == 0 && frameCounter!=0)
		{
			lvlCount++;
		    outputofchangeLvl();
			if (sleepDuration>10)
			{
                sleepDuration-=10;
			}
			if (rockSpawnInterval > 1)
			{
				rockSpawnInterval--;
			}
			if (dwarfSpeed > 3)
			{
				dwarfSpeed--;
			}
		}
}
void creatingPowups()
{
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
	}
}
void addingPowupWithDifShapes()
{
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
     }
}
void Update()
{
	COORD direction = { 0, 0 };
	if (_kbhit())
	{
		char key = getch();
		switch(key)
	{
	         case 'a':
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
		case 'w':
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
		case  'd':
			    if(dwarf[1].Coordinates.X + dwarfSpeed < WindowWidth )
			    {
						 direction.X = dwarfSpeed ;
						 direction.Y = 0;
				}
				else
				{
						direction.X = WindowWidth-dwarf[1].Coordinates.X-1;
						direction.Y = 0 ; 
				}
				 break;
		case  's':
			     if(dwarf[2].Coordinates.Y + dwarfSpeed < WindowHeight )
			     {
						 direction.X = 0;
						 direction.Y = dwarfSpeed;
				 }
				 else
				 {
                         direction.X = 0; 
						 direction.Y = WindowHeight - dwarf[2].Coordinates.Y - 1;
				 }
				 break;
		case 'm':
			InGameMenu();
			break;
		};
	}
	for (randomAccess_iterator dwarfBody = dwarf.begin(); dwarfBody != dwarf.end(); ++dwarfBody)
	{
		dwarfBody->Coordinates.X += direction.X;
		dwarfBody->Coordinates.Y += direction.Y;
		
		//dwarfBody->Color = Green;
	}
	EnlargeX=dwarf[4].Coordinates.X;
	EnlargeY=dwarf[4].Coordinates.Y;
	
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
	}
    //  Creating Power Ups similar to the rock Object
	creatingPowups();
	// Adding powups with shape F or S 
	addingPowupWithDifShapes();
		// Change Level
	changeLvl();
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

void Collision();
//void eventDispatcher(int now)
//{
//	// Enlarge moment
//	//if(enlargeMoments.size())
//	//{
//	//if(now >= enlargeMoments.top())
//	//{
//	//	enlargeMoments.pop();
//	//	enlargeDwarf();
//	//}}
//
//	//// Speed up rocks
//	//if(now >= )
//	//{
//	//	speedUpRocks();
//	//}
//
//	//Stack<Dwarf> dwarfHistory;
//
//
//	//// shrink
//	//Dwarf d = new Dwarf(currentDwarf.size()-1);
//	//dH.push(currentDwarf);
//	//currentDwarf = d;
//	stack
//
//	// enlarge
//	if(!d.size()) return;
//	Dwarf d = dH.top();
////	dH.pop();
////
//	// Other events
//
//}

// Returns the dwarf to his previous speed or shape, after powups had expired
void dwarfPrevstatus()
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
		   LastDwarf();
		   
	   }
    }
}
// Change what happens on collision with powup
void onPowupsCollision()
{
	 copyofframeCounter = frameCounter;
                if( PowupSymbol == PowupSymbol1)
                {
                 dwarfSpeed = 13 ;
                 system("CLS");
                 cout<<"Faster"<<endl;
                 Sleep(2000);
                }
                if( PowupSymbol == PowupSymbol2 && !isShrinked)
                {
					isShrinked = true;
                    system("CLS");
                    cout<<"Shrink"<<endl;
                    Sleep(2000);
					dwarf.clear();
					LastDwarf();
                }
           
}
// Check if the dwarf has catch a powup
void PowUpCollsion()
{
  
	dwarfPrevstatus();
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
               onPowupsCollision();
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

int main()
{
		MainMenu();
		if(quit==1) 
		{
			return 0;
		}

        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        srand(time(NULL));
        int dwarfY = WindowHeight;
        int dwarfX = WindowWidth / 2;
        inGame = true; //Delete? Where is this used?//It's better to have a variable
        while (inGame)
        {
		Update();
		if(quit==1) 
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

void Collision()
{
	//Checks for elemetns with matching coordintaes from the dwarf and rock vector
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
				system("CLS");
				cout<<"GG WP"<<endl; //include a "Angry Video Game Nerd" game over quote later
				Sleep(2000);     
				//MainMenu();
				main();
			}
		}
	}
}

