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
	for (auto i = 0u; i < m_remainingpieces.size(); i++) {
		if (m_currentposition < m_numpieces && isRuleCompilant(m_currentposition, m_pieces[m_remainingpieces[i]]))
		{
			m_puzzle.push_back(m_remainingpieces[i]);
			m_remainingpieces.erase(m_remainingpieces.begin() + i);
			m_currentposition++;
		
			if (auto result = solve(allSolutions); result && !allSolutions)
			{
				return result;
			}

			m_remainingpieces.insert(m_remainingpieces.begin() + i, m_puzzle.back());
			m_puzzle.pop_back();
			m_currentposition--;
		}
	}
	if (m_currentposition == m_numpieces)
	{
		storeSolution();
		return true;
	}
	
	return false;
}

bool Puzzle::isRuleCompilant(int position, Piece& piece)
{
	auto row = position / m_width;
	auto column = position % m_width;
	if ((!piece.isBorder() && !piece.isCorner() && row != 0 && row != m_height - 1 && column != 0 && column != m_width - 1) ||
		(piece.isBorder() && ((row == 0 || row == m_height - 1) != (column == 0 || column == m_width - 1))) ||
		(piece.isCorner() && (row == 0 || row == m_height - 1) && (column == 0 || column == m_width - 1)))
	{
		return trySides(row, column, piece);
	}	

	return false;
}

bool Puzzle::trySides(int row, int column, Piece& piece)
{
	constexpr auto numsides = Piece::numSides();
	auto hole = std::array<std::string_view, numsides>{};
	auto surrounding_positions = std::array<std::array<int, 2>, numsides> {{{ row, column - 1 },
																			{ row - 1, column },
																			{ row, column + 1 },
																			{ row + 1, column }}};

	for (auto i = 0u; i < surrounding_positions.size(); i++)
	{
		auto r = surrounding_positions[i][0];
		auto c = surrounding_positions[i][1];
		auto l = (r * m_width) + c;
		if (c < m_width &&
			r < m_height &&
			c >= 0 && 
			r >= 0 &&
			l <= m_currentposition) 
		{
			constexpr auto halfpiece = numsides / 2;
			auto index = (i + halfpiece) % numsides;
			hole[i] = m_pieces[m_puzzle[l]].side(index);
		}
		else 
		{
			if (c >= m_width ||
				r >= m_height || 
				c < 0 || 
				r < 0)
			{
				hole[i] = "0";
			}
			else
			{
				hole[i] = "-";
			}
		}
	}
	return piece.tryFitting(hole);
}

void Puzzle::storeSolution()
{
	auto solution = std::vector<int>{};
	solution.reserve(m_numpieces);
	for (const auto& piece : m_puzzle)
	{
		solution.push_back(m_pieces[piece].getID());
	}
	m_solutions.push_back(std::move(solution));
}
