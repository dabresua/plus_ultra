#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

/**
 * @file actor.h
 * @brief abstract class that represents every entity that exists in the game
 */

#include <coordinates.h>
#include <iostream>
#include <atomic>

class Actor
{
private:
	static std::atomic_long idCounter;   /*< Actor counter. Thread safe */
protected:
	Coordinates coordinates; /*< coordinates of the actor. Thread safe */
	long id;                 /*< Identifier, unique for every actor */
public:
	/**
	 * @brief Default constructor
	 */
	Actor()
	{
		coordinates = Coordinates(0,0);
		id = idCounter;
		idCounter++;
		std::cout << "I'm an default actor" << std::endl;
	}

	/**
	 * @brief constructor
	 * @param c  Initial coordinates
	 */
	Actor(Coordinates c)
	{
		coordinates = Coordinates(c);
		id = idCounter;
		idCounter++;
		std::cout << "I'm an coordinated actor" << std::endl;
	}

	/**
	 @brief getter
	 */
	inline unsigned int getX()
	{
		return coordinates.getX();
	}

	/**
	 @brief getter
	 */
	inline unsigned int getY()
	{
		return coordinates.getY();
	}

	/**
	 @brief getter
	 */
	inline long getId()
	{
		return this->id;
	}

	/**
	 @brief getter
	 */
	static inline long getIdCounter()
	{
		return idCounter;
	}

	/**
	 @brief setter
	 */
	inline void setX(unsigned int x)
	{
		this->coordinates.setX(x);
	}

	/**
	 @brief setter
	 */
	inline void setY(unsigned int y)
	{
		this->coordinates.setY(y);
	}

	/**
	 * @brief main function of an actor, all actors act
	 */
	virtual void act() = 0;

	/**
	 * @brief prints the contents
	 */
	void print(std::ostream& os) const
	{
		os << this->coordinates;
		os << " " << this->id << "/" << this->idCounter;
	}
};

std::ostream& operator<<(std::ostream& os, const Actor &a)
{
	a.print(os);
	return os;
}

#endif /* ACTOR_H_INCLUDED */
