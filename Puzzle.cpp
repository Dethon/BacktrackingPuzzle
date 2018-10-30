#include "Puzzle.h"
#include <array>
#include <iostream>


Puzzle::~Puzzle()
{
}

bool Puzzle::solveAll()
{
	return solve(true);
}

bool Puzzle::solveOne()
{
	return solve(false);
}

void Puzzle::print() const
{
	for (const auto& solution : m_solutions) 
	{
		for (auto i = 0u; i < solution.size(); i++) 
		{
			if (i != 0 && i % m_width == 0)
			{
				std::cout << std::endl;
			}
			std::cout << solution[i] << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

size_t Puzzle::height() const noexcept
{
	return m_height;
}

size_t Puzzle::width() const noexcept
{
	return m_width;
}

bool Puzzle::solve(bool allSolutions)
{
	for (auto i = m_pieces.begin(); i != m_pieces.end(); i++) {
		if (m_currentPosition < m_numPieces && isRuleCompilant(m_currentPosition, (*i).get())) 
		{
			m_puzzle.push_back(std::move(*i));
			m_pieces.erase(i);
			m_currentPosition++;
			auto result = solve(allSolutions);
			if (result && !allSolutions)
			{
				return result;
			}
			m_pieces.insert(i, std::move(m_puzzle.back()));
			m_puzzle.pop_back();
			m_currentPosition--;
		}
	}
	if (m_currentPosition == m_numPieces) 
	{
		storeSolution();
		return true;
	}
	
	return false;
}

bool Puzzle::isRuleCompilant(int position, Piece* piece)
{
	int row = position / static_cast<int>(m_width);
	int column = position % static_cast<int>(m_width);
	if ((!piece->isBorder() && !piece->isCorner() && row != 0 && row != m_height - 1 && column != 0 && column != m_width - 1) ||
		(piece->isBorder() && ((row == 0 || row == m_height - 1) != (column == 0 || column == m_width - 1))) ||
		(piece->isCorner() && (row == 0 || row == m_height - 1) && (column == 0 || column == m_width - 1)))
	{
		return trySides(row, column, piece);
	}	

	return false;
}

bool Puzzle::trySides(int row, int column, Piece* piece)
{
	constexpr auto numsides = Piece::numSides();
	auto hole{ std::array<std::string, numsides>{} };
	auto surroundingPositions{ 
		std::array<std::array<int, 2>, numsides> {{{row, column - 1},
												{row - 1, column}, 
												{row, column + 1}, 
												{row + 1, column}}} 
	};

	for (auto i = 0u; i < surroundingPositions.size(); i++) 
	{
		int r = surroundingPositions[i][0];
		int c = surroundingPositions[i][1];
		int l = (r * static_cast<int>(m_width)) + c;
		if (r >= 0 && r < m_height && c >= 0 && c < m_width && l <= m_currentPosition) 
		{
			constexpr auto halfpiece = numsides / 2;
			auto index = (i + halfpiece) % numsides;
			hole[i] = m_puzzle[l]->side(index);
		}
		else {
			if (r < 0 || r >= m_height || c < 0 || c >= m_width)
			{
				hole[i] = "0";
			}
			else
			{
				hole[i] = "-";
			}
		}
	}
	return piece->tryFitting(hole);
}

void Puzzle::storeSolution()
{
	auto solution{ std::vector<int>{} };
	solution.reserve(m_numPieces);
	for (const auto& piece : m_puzzle)
	{
		solution.push_back(piece->getID());
	}
	m_solutions.push_back(std::move(solution));
}
