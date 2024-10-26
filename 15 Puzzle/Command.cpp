#include "Command.h"

bool Command::isValid(char input) {
	switch (input)
	{
	case 'w':
	case 'a':
	case 's':
	case 'd':
	case 'q':
		return true;
	default:
		return false;
	}
}

bool Command::execute(Game::Board& gb, char input) {
	auto blankPos = gb.getTilePos(0);

	switch (input)
	{
	case 'w':
		return gb.swapIfValid(
			blankPos,
			{ blankPos.row + 1, blankPos.column }
		);
	case 'a':
		return gb.swapIfValid(
			blankPos,
			{ blankPos.row, blankPos.column + 1 }
		);
	case 's':
		return gb.swapIfValid(
			blankPos,
			{ blankPos.row - 1, blankPos.column }
		);
	case 'd':
		return gb.swapIfValid(
			blankPos,
			{ blankPos.row, blankPos.column - 1 }
		);
	}

	return false;
}

