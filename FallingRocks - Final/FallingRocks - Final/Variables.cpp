#include "Variables.h"
#include <vector>
#include "ConsoleGaming.h"

// Window constants
const int WindowWidth = 80;
const int WindowHeight = 26;

// Rock variables
char rockSymbol = '#';
int rockSpeed = 1;

// Dwarf variables

int dwarfSpeed = 3;
int lastDwarfSpeed = 3;
int dwarfShape = 1;
int lastDwarfShape = 1;
int enlargeX = WindowWidth / 2;
int enlargeY = WindowHeight - 2;
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
unsigned long sleepDuration = 150;
int difficulty = 1;

//Powups variables
char powupSymbol1 = 'F';
char powupSymbol2 = 'S';
char powupSymbol;
int  powupSpeed = 1;
int fastBonusDurtion = 0;


//Skill variables
bool phaseShiftAvailable = false;
bool phaseShift = false;
unsigned int phaseShiftDuration = 0;
bool andromedaSkillOn = false;
int lastUsedAndroSkill = 0;
bool fire = false;
int lastUsedFireSkill = 5;
unsigned int fireDuration = 0;
bool fireAvailable = false;

//If the dwarf is shrinked
bool isShrinked = false;

//To use the arrow keys
bool useArrowKeys = false;

//Level variables
int score = 0;
int highScore = 0;
int levelCount = 1; 

unsigned int frameCounter = 0;
unsigned int copyOfFrameCounter = 0;
unsigned int rockSpawnInterval = 10;


typedef std::vector<GameObject>::iterator randomAccess_iterator;
typedef std::vector<GameObject>::const_iterator const_iterator;

//dwarf,rocks,powups vectors
std::vector<GameObject> dwarf;
std::vector<GameObject> rocks;
std::vector<GameObject> powups;
std::vector<GameObject> missiles;
