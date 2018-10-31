#pragma once
#include <vector>
#include <memory>
#include "Piece.h"

class Puzzle
{
private:
	int m_height;
	int m_width;
	int m_currentposition;
	int m_numpieces;
	std::vector<Piece> m_pieces;
	std::vector<unsigned int> m_remainingpieces;
	std::vector<unsigned int> m_puzzle;
	std::vector<std::vector<int>> m_solutions;

public:
	template<class ForwardIterator>
	Puzzle(ForwardIterator begin, ForwardIterator end, int height, int width, char separator = ' ') :
		m_height{ height }, m_width{ width }, m_numpieces{ height * width }, m_currentposition{ 0 }
	{
		static_assert(std::is_same<std::iterator_traits<ForwardIterator>::value_type, std::string>::value, 
					  "The container must provide std::String encoded pieces");
		m_puzzle.reserve(m_numpieces);
		m_pieces.reserve(m_numpieces);
		m_remainingpieces.reserve(m_numpieces);
		for (auto i = 0u; begin != end; i++, begin++)
		{
			m_pieces.emplace_back(*begin, separator, i + 1);
			m_remainingpieces.emplace_back(i);
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
	bool isRuleCompilant(int position, Piece& piece);
	bool trySides(int row, int column, Piece& piece);
	void storeSolution();
};
