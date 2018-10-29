#pragma once

#include <array>
#include <string>


class Piece
{
private:
	static constexpr size_t m_numsides = 4u;
	std::array<std::string, m_numsides> m_sides;
	bool m_corner;
	bool m_border;
	int m_id;
	
public:
	Piece(const std::string& sides, char delim, int id);
	virtual ~Piece();
	void rotate();
	bool isCorner() const;
	bool isBorder() const;
	std::string side(size_t index) const;
	bool tryFitting(const std::array<std::string, m_numsides>& hole);
	int getID() const;
	static constexpr size_t numSides()
	{
		return m_numsides;
	}
	
private:
	void classify(int ceroCount, int separation);
};
