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
	Game.~Game();
	return 0; // 0 = Success, <0 = Error
}

// TODO: Win/lose screen
// TODO: Dialogue boxes
// TODO: SFX??
// TODO: Website
