#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <conio.h>
#include "Random.h"

namespace Constants {
	constexpr int maxRow{ 4 };
	constexpr int maxColumn{ 4 };
	constexpr int tilesSize { maxRow * maxColumn };
}

namespace Game {
	class Board {
	public:
		struct Position {
			int row{};
			int column{};
		};

		Board() {
			std::shuffle(m_tiles.begin(), m_tiles.end(), Random::mt);
		}

		Position getTilePos(int value) {
			assert(value >= 0 && value <= 15);

			auto found = std::find(m_tiles.begin(), m_tiles.end(), value);

			int index = static_cast<int>(found - m_tiles.begin());

			return Position{
				index / Constants::maxRow,
				index % Constants::maxColumn
			};
		}

		int& get(const Position& pos) {
			return m_tiles[static_cast<std::size_t>((pos.row * Constants::maxRow) + pos.column)];
		}

		bool isInBounds(const Position& pos) {
			bool maxBound = pos.column < Constants::maxColumn && pos.row < Constants::maxRow;
			bool minBound = pos.column >= 0 && pos.row >= 0;

			return maxBound && minBound;
		}

		bool swapIfValid(const Position& pos1, const Position& pos2) {
			if (!isInBounds(pos1) || !isInBounds(pos2))
				return false;

			std::swap(get(pos1), get(pos2));
			return true;
		}

		bool isSorted() {
			return std::is_sorted(m_tiles.begin(), m_tiles.end() - 1);
		}

		friend void render(Board& gb);

	private:
		std::array<int, Constants::tilesSize> m_tiles = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
	};

	void render(Board& gb) {
		std::cout << std::setfill(' ');
		std::cout << "\n\n";

		for (std::size_t i = 0; i < gb.m_tiles.size(); ++i) {
			if (gb.m_tiles[i] != 0)
				std::cout << std::setw(3) << std::right << gb.m_tiles[i];
			else
				std::cout << std::setw(3) << std::right << "##";

			if ((i + 1) % Constants::maxRow == 0) {
				std::cout << '\n';
			}
		}

		std::cout << "\n\n";
	}
}


namespace Command {
	bool isValid(char input) {
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

	bool execute(Game::Board& gb, char input) {
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

}

namespace Console {
	bool failure() {
		bool failure{ !std::cin };

		if (failure) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		return failure;
	}

	bool hasUnExtractedInput() {
		return !std::cin.eof() && std::cin.peek() != '\n';
	}

	void print_if(bool condition, std::string_view) {

	}
}

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
	std::cin.get();
	return 0;
}