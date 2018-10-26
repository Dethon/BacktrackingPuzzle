// PuzzleAldor.cpp: define el punto de entrada de la aplicación de consola.
//

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include "Puzzle.h"

int main()
{
	const int height = 5;
	const int width = 5;
	std::vector<std::string> stringpieces =
	{{
	{"9 3 8 0"},{"0 3 5 10"},{"1 0 7 9"},{"7 2 9 1"},{"9 2 0 2"},
	{"9 10 8 3"},{"9 4 8 6"},{"5 9 9 4"},{"2 0 0 1"},{"9 0 4 1"},
	{"8 10 0 0"},{"7 0 5 8"},{"0 2 1 9"},{"0 8 6 3"},{"0 9 9 2"},
	{"7 2 3 8"},{"8 3 8 5"},{"0 10 8 5"},{"7 4 8 10"},{"6 2 4 0"},
	{"0 10 5 1"},{"1 5 8 4"},{"0 0 1 6"},{"7 2 5 8"},{"0 0 2 8"}
	}};

	/*const int height = 4;
	const int width = 4;
	std::vector<std::string> stringPieces =
	{{
	{"2 5 4 0"},{"2 1 4 2"},{"0 1 1 0"},{"4 4 0 3"},
	{"0 0 4 3"},{"0 0 1 1"},{"1 4 0 0"},{"4 4 3 5"},
	{"5 5 2 4"},{"1 1 0 5"},{"4 1 0 4"},{"1 0 2 4"},
	{"3 5 1 2"},{"1 4 2 0"},{"0 1 5 2"},{"1 5 0 4"}
	}};*/

	/*const int height = 3;
	const int width = 3;
	std::vector<std::string> stringPieces =
	{{
	{"0 0 1 2"},{"1 0 3 4"},{"3 0 0 5"},
	{"0 2 6 7"},{"6 4 8 9"},{"8 5 0 10"},
	{"0 7 11 0"},{"11 9 12 0"},{"12 10 0 0"}
	}};*/

	/*const int height = 2;
	const int width = 2;
	std::vector<std::string> stringPieces =
	{{
	{"4 3 0 0"},{"0 0 8 1"},
	{"0 1 4 0"},{"8 0 0 3"}
	}};*/

	auto starttime = std::chrono::steady_clock::now();
	Puzzle puzzle(height, width, stringpieces);
	bool result = puzzle.solveAll();
	auto endtime = std::chrono::steady_clock::now();

	auto elapsedtime = endtime - starttime;

	std::cout << "Puzzle resolved in " << std::chrono::duration <double, std::milli>(elapsedtime).count() << " ms" << std::endl;
	puzzle.print();

    return 0;
}
