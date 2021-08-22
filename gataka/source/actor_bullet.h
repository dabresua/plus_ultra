#ifndef ACTOR_BULLET_H_INCLUDED
#define ACTOR_BULLET_H_INCLUDED

#include <math.h>
#include <bullet_params.h>

class ActorBullet : public Actor
{
private:
	bullet_params_t par; /**< Bullet parameters */
	double angle;  /*< Angle of movement */

	/**
	 * @brief moves the bullet
	 */
	void move()
	{
		this->coordinates.move(par.speed * cos(angle), par.speed * sin(angle));
	}
public:
	/*
	 * @brief Default constructor
	 */
	 ActorBullet() : Actor()
	 {
		 /* Just calling the base class default constructor */
	 }

	/**
	 * @brief constructor
	 * @param c       initial coordinates
	 * @param params  bullet properties
	 * @param ang     initial angle of movement
	 */
	ActorBullet(Coordinates c, const bullet_params_t& params, double ang)
	: Actor(c)
	{
		#define PI 3.14159265
		par.attack = params.attack;
		par.speed = params.speed;
		angle = ang * PI / 180.0;
	}

	/**
	 * @brief act for bullet
	 */
	void act()
	{
		move();
	}
};

#endif /* ACTOR_BULLET_H_INCLUDED */
