#include "Variables.h"
#include "Skills.h"
#include<iostream>


// Show that Andromeda skill is ready to be used
void OutputOfAndromedaSkill()
{
	if (levelCount > 9 && levelCount == lastUsedAndroSkill + 2)
	{
		std::cout << "AndromedaSkill is On. Press 'e' or 'x' to use" << std::endl;
		andromedaSkillOn = true;
	}
}
// Show that Fire skill is ready to be used
void OutputOfFireSkill()
{
	if (levelCount > 1 && levelCount == (lastUsedFireSkill + 2))
	{
		std::cout << "Fire is available press 'f' to use" << std::endl;
		fireAvailable = true;
	}
}
void OutputOfPhaseShiftSkill()
{
	if (levelCount > 4 && levelCount % 2 == 1)
	{
		std::cout << "Phase Shift is now available";
		phaseShiftAvailable = true;
	}
}

// Creates the Andromeda skill effect . If the level is above 10 and if the skill is availiable
void AndromedaSkill()
{
	if (levelCount > 9 && andromedaSkillOn)
	{
		lastUsedAndroSkill = levelCount;
		system("CLS");
		std::cout << "Boom" << std::endl;
		Sleep(500);
		rocks.clear();
		andromedaSkillOn = false;
	}
}
//Checks if the Fire Skill has expired
void FireDuration()
{
	if (fire && frameCounter == (fireDuration + 50))
	{
		fire = false;
	}
}

void SkillDuration()
{
	if (phaseShift && frameCounter == (phaseShiftDuration + (40 + difficulty * 20)))
	{
		phaseShift = false;
		system("CLS");
		std::cout << "Phase Shift has expired! You better watch out for those rocks!!!" << std::endl;
		Sleep(2000);
	}
}

// When the FIRE_CHAR is clicked
void OnFireClick()
{
	if (levelCount > 6 && !fire && fireAvailable)
	{
		fire = true;
		lastUsedFireSkill = levelCount;
		fireDuration = frameCounter;
		fireAvailable = false;
	}
}
