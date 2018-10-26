#pragma once

#include <vector>
#include <string>

class Piece
{
private:
	std::vector<std::string> m_sides;
	bool m_corner;
	bool m_border;
	int m_id;
	const size_t m_numsides = 4;
public:
	Piece(const std::string& sides, char delim, int id);
	virtual ~Piece();
	void rotate();
	bool isCorner() const;
	bool isBorder() const;
	size_t getNumSides() const;
	std::string getSide(int index) const;
	bool tryFitting(const std::vector<std::string>& hole);

	int getID() const;
	
private:
	void classify(int ceroCount, int separation);
};
