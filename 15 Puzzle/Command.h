#ifndef COMMAND_H
#define COMMAND_H
#include "Game.h"
namespace Command {
	bool isValid(char input);

	bool execute(Game::Board& gb, char input);
}
#endif