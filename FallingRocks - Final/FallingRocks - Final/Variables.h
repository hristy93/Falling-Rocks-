#pragma once
#include <vector>
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
#define ANDROMEDA_CHAR 'e'
#define PhaseShift_CHAR2 'z'
#define ANDROMEDA_CHAR2 'x'
#define FIRE_CHAR 'f'
#define FIRE_CHAR2 'c'

// Window constants
extern const int WindowWidth;
extern const int WindowHeight;

// Rock variables
extern char rockSymbol;
extern int rockSpeed;

// Dwarf variables
extern int dwarfSpeed;
extern int lastDwarfSpeed;
extern int dwarfShape;
extern int lastDwarfShape;
extern int enlargeX;
extern int enlargeY;
extern int dwarfColor;

//Counts the number of the stones
extern int stoneCounter;

//Color variable
extern unsigned char colour;

//Variables to help menu navigation,start and quit game
extern bool quit;
extern bool start;
extern bool toBreak;
extern bool toPrint;

// Game variables
extern unsigned long sleepDuration;
extern int difficulty;

//Powups variables
extern char powupSymbol1;
extern char powupSymbol2;
extern char powupSymbol;
extern int  powupSpeed;
extern int fastBonusDurtion;


//Skill variables
extern bool phaseShiftAvailable;
extern bool phaseShift;
extern unsigned int phaseShiftDuration;
extern bool andromedaSkillOn;
extern int lastUsedAndroSkill;
extern bool fire;
extern int lastUsedFireSkill;
extern unsigned int fireDuration;
extern bool fireAvailable;

//If the dwarf is shrinked
extern bool isShrinked;

//To use the arrow keys
extern bool useArrowKeys;

//Level variables
extern int levelCount;
extern int score;
extern int highScore;

extern unsigned int frameCounter;
extern unsigned int copyOfFrameCounter;
extern unsigned int rockSpawnInterval;


typedef std::vector<GameObject>::iterator randomAccess_iterator;
typedef std::vector<GameObject>::const_iterator const_iterator;

//dwarf,rocks,powups vectors
extern std::vector<GameObject> dwarf;
extern std::vector<GameObject> rocks;
extern std::vector<GameObject> powups;
extern std::vector<GameObject> missiles;
