#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Random.h"
#include "Constants.h"
#include "Game.h"

using Position = Game::Board::Position;

Game::Board::Board() {
	randomize();
}

void Game::Board::randomize() {
	for (int i = 0; i < 1000; ++i) {
		Position blankPos{ getTilePos(0) };
		{
			switch (Random::get(1, 4))
			{
			case 1:
				swapIfValid(
					blankPos,
					{ blankPos.row + 1, blankPos.column }
				);
				break;
			case 2:
				swapIfValid(
					blankPos,
					{ blankPos.row, blankPos.column + 1 }
				);
				break;
			case 3:
				swapIfValid(
					blankPos,
					{ blankPos.row - 1, blankPos.column }
				);
				break;
			case 4:
				swapIfValid(
					blankPos,
					{ blankPos.row, blankPos.column - 1 }
				);
				break;
			}
		}
	}
}

Position Game::Board::getTilePos(int value) {
	assert(value >= 0 && value <= 15);

	auto found = std::find(m_tiles.begin(), m_tiles.end(), value);

	int index = static_cast<int>(found - m_tiles.begin());

	return Position{
		index / Constants::maxRow,
		index % Constants::maxColumn
	};
}

int& Game::Board::get(const Position& pos) {
	return m_tiles[static_cast<std::size_t>((pos.row * Constants::maxRow) + pos.column)];
}

bool Game::Board::isInBounds(const Position& pos) {
	bool maxBound = pos.column < Constants::maxColumn && pos.row < Constants::maxRow;
	bool minBound = pos.column >= 0 && pos.row >= 0;

	return maxBound && minBound;
}

bool Game::Board::swapIfValid(const Position& pos1, const Position& pos2) {
	if (!isInBounds(pos1) || !isInBounds(pos2))
		return false;

	std::swap(get(pos1), get(pos2));
	return true;
}

bool Game::Board::isSorted() {
	return std::is_sorted(m_tiles.begin(), m_tiles.end() - 1);
}


void Game::render(Game::Board& gb) {
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