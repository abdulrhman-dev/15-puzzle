#ifndef GAME_H
#define GAME_H
#include <array>
#include "Constants.h"
namespace Game {
	class Board {
	public:
		struct Position {
			int row{};
			int column{};
		};

		Board();
		Position getTilePos(int value);
		int& get(const Position& pos);
		bool isInBounds(const Position& pos);
		bool swapIfValid(const Position& pos1, const Position& pos2);
		bool isSorted();

		friend void render(Board& gb);
	private:
		std::array<int, Constants::tilesSize> m_tiles = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
	};

	
}
#endif 

