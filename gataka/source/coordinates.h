#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED

/**
 * @file coordinates.h
 * @brief 2D coordinates definition and utils
 */
#include <iostream>

class Coordinates
{
private:
	unsigned int x;
	unsigned int y;
public:
	/**
	 * @brief default constructor
	 */
	Coordinates()
	{
		this->x = 0;
		this->y = 0;
	}

	/**
	 * @brief copy constructor
	 */
	Coordinates(const Coordinates &c)
	{
		this->x = c.x;
		this->y = c.y;
	}

	/**
	 * @brief constructor
	 * @param x coordinate to set
	 * @param y coordinate to set
	 */
	Coordinates(unsigned int x, unsigned int y)
	{
		this->x = x;
		this->y = y;
	}

	/**
	 * @brief gets x coordinate
	 * @returns x coordinate
	 */
	inline unsigned int getX() const
	{
		return this->x;
	}

	/**
	 * @brief gets y coordinate
	 * @returns y coordinate
	 */
	inline unsigned int getY() const
	{
		return this->y;
	}

	/**
	 * @brief sets x coordinate
	 * @param x coordinate to set
	 */
	inline void setX(unsigned int x)
	{
		this->x = x;
	}

	/**
	 * @brief sets y coordinate
	 * @param y coordinate to set
	 */
	inline void setY(unsigned int y)
	{
		this->y = y;
	}

	/**
	 * @briefs Increments the coordinates by another coordinate
	 * @brief ix  x increment
	 * @brief iy  y increment
	 */
	Coordinates& operator+=(const Coordinates& c)
	{
		this->x += c.getX();
		this->y += c.getY();
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Coordinates &c);
};

std::ostream& operator<<(std::ostream& os, const Coordinates &c)
{
	os << "[" << c.x << ", " << c.y << "]";
	return os;
}

#endif /* COORDINATES_H_INCLUDED */
