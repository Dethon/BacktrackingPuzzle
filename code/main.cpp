// PuzzleAldor.cpp: define el punto de entrada de la aplicación de consola.
//

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include "Puzzle.h"

int main()
{
	/*constexpr auto height = 2u;
	constexpr auto width = 2u;
	const auto stringpieces = std::array<std::string, 4>
	{{
		{ "4 3 0 0" }, { "0 0 8 1" },
		{ "0 1 4 0" }, { "8 0 0 3" }
	}};*/

	/*constexpr auto height = 3u;
	constexpr auto width = 3u;
	const auto stringpieces = std::array<std::string, 9>
	{{
		{ "0 0 1 2" }, { "1 0 3 4" }, { "3 0 0 5" },
		{ "0 2 6 7" }, { "6 4 8 9" }, { "8 5 0 10" },
		{ "0 7 11 0" }, { "11 9 12 0" }, { "12 10 0 0" }
	}};*/

	/*constexpr auto height = 4u;
	constexpr auto width = 4u;
	const auto stringpieces = std::array<std::string, 16>
	{{
		{ "2 5 4 0" }, { "2 1 4 2" }, { "0 1 1 0" }, { "4 4 0 3" },
		{ "0 0 4 3" }, { "0 0 1 1" }, { "1 4 0 0" }, { "4 4 3 5" },
		{ "5 5 2 4" }, { "1 1 0 5" }, { "4 1 0 4" }, { "1 0 2 4" },
		{ "3 5 1 2" }, { "1 4 2 0" }, { "0 1 5 2" }, { "1 5 0 4" }
	}};*/

	constexpr auto height = 5u;
	constexpr auto width = 5u;
	const auto stringpieces = std::array<std::string, 25>
	{{
		{ "9 3 8 0" }, { "0 3 5 10" }, { "1 0 7 9" }, { "7 2 9 1" }, { "9 2 0 2" },
		{ "9 10 8 3" }, { "9 4 8 6" }, { "5 9 9 4" }, { "2 0 0 1" }, { "9 0 4 1" },
		{ "8 10 0 0" }, { "7 0 5 8" }, { "0 2 1 9" }, { "0 8 6 3" }, { "0 9 9 2" },
		{ "7 2 3 8" }, { "8 3 8 5" }, { "0 10 8 5" }, { "7 4 8 10" }, { "6 2 4 0" },
		{ "0 10 5 1" }, { "1 5 8 4" }, { "0 0 1 6" }, { "7 2 5 8" }, { "0 0 2 8" }
	}};

	auto starttime = std::chrono::steady_clock::now();
	Puzzle puzzle(stringpieces.begin(), stringpieces.end(), height, width);
	bool result = puzzle.solveAll();
	auto endtime = std::chrono::steady_clock::now();

	auto elapsedtime = endtime - starttime;

	std::cout << "Puzzle resolved in " << std::chrono::duration <double, std::milli>(elapsedtime).count() << " ms" << std::endl;
	puzzle.print(std::cout);

    return 0;
}
