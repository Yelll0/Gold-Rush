#pragma once

#include "stdafx.h"


int main ( int argc, char *argv[] )
{
	Game Game;
	if ( Game.Init() ) 
	{
		std::cout << "Failed to initialize game." << std::endl;
		return -1;
	}
	Game.RunLoop();
	Game.Quit();
	return 0; // 0 = Success, <0 = Error
}
