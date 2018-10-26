#include "Piece.h"
#include <sstream>
#include <stdexcept>


Piece::Piece(const std::string & sides, char delim, int id) : 
	m_id(id)
{
	m_sides.reserve(m_numsides);
	std::stringstream ss;
	ss.str(sides);
	std::string item;
	auto ceroCount = 0, separationCounter = 0, separation = 0, nonCeroCount = 0;
	while (std::getline(ss, item, delim)) {
		m_sides.push_back(item);
		if (item == "0") {
			if (ceroCount == 0)
				separationCounter = 0;
			else
				separation = separationCounter;
			ceroCount++;
		}
		else
			separationCounter++;
	}
	if (m_sides.size() != m_numsides)
		throw std::invalid_argument("Wrong number of sides!!! (" + std::to_string(m_sides.size()) + ")");

	classify(ceroCount, separation);
}

Piece::~Piece()
{
}

void Piece::rotate()
{
	m_sides.push_back(m_sides.front());
	m_sides.erase(m_sides.begin());
}

bool Piece::isCorner() const
{
	return m_corner;
}

bool Piece::isBorder() const
{
	return m_border;
}

size_t Piece::getNumSides() const
{
	return m_sides.size();
}

std::string Piece::getSide(int index) const
{
	if (index >= m_sides.size())
		throw std::invalid_argument("The argument is bigger than the array size!!!");
	return m_sides[index];
}


bool Piece::tryFitting(const std::vector<std::string>& hole) 
{
	if (getNumSides() != hole.size())
		return false;

	auto tries = 0;
	for (auto i = 0u; i < m_sides.size(); i++) {
		if (m_sides[i] != hole[i] && hole[i] != "-") {
			if (tries < m_sides.size()){
				i = -1;
				tries++;
				rotate();
			}
			else
				return false;
		}
	}
	return true;
}

int Piece::getID() const
{
	return m_id;
}



void Piece::classify(int ceroCount, int separation)
{
	switch (ceroCount) {
	case 0:
		m_corner = false;
		m_border = false;
		break;
	case 1:
		m_corner = false;
		m_border = true;
		break;
	case 2:
		if (separation == 1) {
			m_corner = false;
			m_border = true;
		}
		else {
			m_corner = true;
			m_border = false;
		}
		break;
	case 3:
		m_corner = true;
		m_border = false;
		break;
	};
}
