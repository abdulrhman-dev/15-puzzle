#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include "Random.h"

namespace Constants {
	constexpr int maxRow{ 4 };
	constexpr int maxColumn{ 4 };
	constexpr int tilesSize { maxRow * maxColumn };
}

class GameBoard {
public:
	struct Position {
		int row{};
		int column{};
	};

	GameBoard() {
		std::shuffle(m_tiles.begin(), m_tiles.end(), Random::mt);
	}

	Position getTilePos(int value) {
		assert(value >= 0 && value <= 15);

		auto found = std::find(m_tiles.begin(), m_tiles.end(), value);

		int index = found - m_tiles.begin();

		return Position { 
			index / Constants::maxRow, 
			index % Constants::maxColumn 
		};
	}

	bool isInBounds(const Position& pos) {
		bool maxBound = pos.column < Constants::maxColumn && pos.row < Constants::maxRow;
		bool minBound = pos.column >= 0 && pos.row >= 0;

		return maxBound && minBound;
	}

	const int& operator()(const Position& pos) {
		return m_tiles[static_cast<std::size_t>(pos.row * pos.column)];
	}

	friend void render(GameBoard& gb);

private:
	std::array<int, Constants::tilesSize> m_tiles = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
};


void render(GameBoard& gb) {
	for (std::size_t i = 0; i < gb.m_tiles.size(); ++i) {
		if (gb.m_tiles[i] != 0)
			std::cout << std::setw(3) << std::right << gb.m_tiles[i];
		else
			std::cout << std::setw(3) << std::right << "##";

		if ((i + 1) % Constants::maxRow == 0) {
			std::cout << '\n';
		}
	}
}
int main()
{
	GameBoard gb;
	
}
