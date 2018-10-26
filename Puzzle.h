#pragma once
#include <vector>
#include <memory>
#include "Piece.h"

class Puzzle
{
private:
	size_t m_height;
	size_t m_width;
	size_t m_numPieces;
	int m_currentPosition;
	std::vector<std::unique_ptr<Piece>> m_pieces;
	std::vector<std::unique_ptr<Piece>> m_puzzle;
	std::vector<std::vector<int>> m_solutions;

public:
	Puzzle(size_t height, size_t width, const std::vector<std::string>& pieces);
	virtual ~Puzzle();
	bool solveOne();
	bool solveAll();
	void print() const;

	size_t getHeight() const;
	size_t getWidth() const;

private:
	bool solve(bool allSolutions);
	bool isRuleCompilant(int position, Piece* piece);
	bool trySides(int row, int column, Piece* piece);
	void storeSolution();
};
