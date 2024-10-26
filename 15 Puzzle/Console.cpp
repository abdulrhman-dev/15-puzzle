#include "Console.h"
#include "iostream"

bool Console::failure() {
	bool failure{ !std::cin };

	if (failure) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return failure;
}

bool Console::hasUnExtractedInput() {
	return !std::cin.eof() && std::cin.peek() != '\n';
}