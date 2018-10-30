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
	template<class ForwardIterator>
	Puzzle(ForwardIterator begin, ForwardIterator end, size_t height, size_t width, char separator = ' ') :
		m_height(height), m_width(width), m_numPieces(height * width), m_currentPosition(0)
	{
		static_assert(std::is_same<std::iterator_traits<ForwardIterator>::value_type, std::string>::value, 
					  "The container must provide std::String encoded pieces");
		m_puzzle.reserve(m_numPieces);
		m_pieces.reserve(m_numPieces);
		for (auto i = 1u; begin != end; i++, begin++)
		{
			m_pieces.emplace_back(std::make_unique<Piece>(*begin, separator, i));
		}
	}
	virtual ~Puzzle();
	bool solveOne();
	bool solveAll();
	void print() const;
	size_t height() const noexcept;
	size_t width() const noexcept;

private:
	bool solve(bool allSolutions);
	bool isRuleCompilant(int position, Piece* piece);
	bool trySides(int row, int column, Piece* piece);
	void storeSolution();
};
