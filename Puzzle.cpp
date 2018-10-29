#include "Puzzle.h"
#include <array>
#include <iostream>


Puzzle::Puzzle(size_t height, size_t width, const std::vector<std::string>& pieces) : 
	m_height(height), m_width(width), m_numPieces(height * width), m_currentPosition(0)
{
	m_puzzle.reserve(m_numPieces);
	m_pieces.reserve(m_numPieces);
	for (auto i = 0u; i < pieces.size(); i++)
	{
		m_pieces.emplace_back(std::make_unique<Piece>(pieces[i], ' ', i + 1));
	}
}

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
	for (auto solution : m_solutions) 
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

size_t Puzzle::getHeight() const
{
	return m_height;
}

size_t Puzzle::getWidth() const
{
	return m_width;
}

bool Puzzle::solve(bool allSolutions)
{
	for (auto i = 0u; i < m_pieces.size(); i++) {
		if (m_currentPosition < m_numPieces && isRuleCompilant(m_currentPosition, m_pieces[i].get())) 
		{
			m_puzzle.push_back(std::move(m_pieces[i]));
			m_pieces.erase(m_pieces.begin() + i);
			m_currentPosition++;
			auto result = solve(allSolutions);
			if (result && !allSolutions)
			{
				return result;
			}
			m_pieces.insert(m_pieces.begin() + i, std::move(m_puzzle.back()));
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
	auto hole{ std::array<std::string, Piece::numSides()>{} };
	auto surroundingPositions{ 
		std::array<std::array<int, 2>, 4> {{{row, column - 1}, 
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
			auto index = (i + 2) % 4;
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
	for (const auto& piece : m_puzzle)
	{
		solution.push_back(piece->getID());
	}
	m_solutions.push_back(solution);
}
