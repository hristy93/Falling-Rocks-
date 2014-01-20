#include "Variables.h"
#include "UpdateDwarf.h"
//Changes dwarfspeed
void OutputOfFasterBonus()
{
	dwarfSpeed += 2;
	fastBonusDurtion = (30 + difficulty * 15);
	system("CLS");
	std::cout << "You are now moving faster, but just for a few seconds !" << std::endl;
	Sleep(2000);
}

//Changes dwarfShape
void OutputOfShrinkBonus()
{
	isShrinked = true;
	system("CLS");
	std::cout << "You are now shrinked, but just for a few seconds !" << std::endl;
	Sleep(2000);
	dwarf.clear();
	UpdateDwarf();
}
