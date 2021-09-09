#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED

/**
 * @file coordinates.h
 * @brief 2D coordinates definition and utils.
 *        Holded data is atomic, so is thread safe
 *        std::atomic (c++11) intruduces atomic accesses without much overhead
 */
#include <iostream>
#include <atomic>

class Coordinates
{
private:
	std::atomic_ushort x; /**< atomic variables */
	std::atomic_ushort y; /**< atomic variables */
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
		this->x = c.x.load();
		this->y = c.y.load();
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
		return this->x.load();
	}

	/**
	 * @brief gets y coordinate
	 * @returns y coordinate
	 */
	inline unsigned int getY() const
	{
		return this->y.load();
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
	 * @brief c  source coordinates
	 */
	Coordinates& operator+=(const Coordinates& c)
	{
		this->x += c.getX();
		this->y += c.getY();
		return *this;
	}

	/**
	 * @brief Copy operator overload for atomic implementation
	 * @brief c  source coordinates
	 */
	 Coordinates& operator=(const Coordinates& c)
 	{
 		this->x = c.getX();
 		this->y = c.getY();
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
