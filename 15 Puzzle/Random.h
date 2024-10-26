#ifndef RANDOM_H
#define RANDOM_H
#include <random>
#include <chrono>
class Random {
private:
	static std::mt19937 generate() {
		std::random_device rd{};

		std::seed_seq ss { 
			rd(), rd(), rd(), rd(), rd(), rd(), rd(),
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()) 
		};
		
		return std::mt19937{ ss };
	}

	
public:
	static inline std::mt19937 mt{ generate() };

	static int get(int min, int max) {
		return std::uniform_int_distribution{ min, max }(mt);
	}
};
#endif