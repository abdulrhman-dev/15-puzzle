#include <iostream>
#include <iomanip>

#include "Random.h"
#include "Game.h"
#include "Command.h"
#include "Console.h"

int main()
{
	Game::Board gb;

	char command{};
	int moves{};

	do {
		if (moves > 0) {
			std::cout << "\n\n";
		}

		std::cout << "--------------" << "15 Puzzle Move("
			<< std::setfill('0') << std::setw(3) << std::right << moves + 1 << ")"
			<< "--------------\n";

		render(gb);

		std::cout << "Enter a valid command (w, a, s, d) or q to quit: ";
		std::cin >> command;
		
		if (Console::failure()) {
			std::cout << "Encountered invalid input please try again!\n";
			continue;
		}
		
		if (Console::hasUnExtractedInput()) {
			std::cout << "Please input one character only (w, a, s, d) or q to quit.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (!Command::isValid(command)) {
			std::cout << "(" << command  << ") is not a valid command please enter (w, a, s, d) or q to quit.\n";
			continue;
		}

		if (!Command::execute(gb, command)) {
			std::cout << "Invalid operation!\n";
			continue;
		}

		++moves;
	} while (command != 'q' && !gb.isSorted());

	if (gb.isSorted()) {
		std::cout << "\n\nYou solved the puzzle in " << moves + 1 << " moves\n";
		render(gb);
	}

	std::cout << "Thanks for playing!\n";

	return 0;
}