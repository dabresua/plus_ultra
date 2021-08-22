#ifndef ACTOR_BULLET_H_INCLUDED
#define ACTOR_BULLET_H_INCLUDED

#include <math.h>
#include <bullet_params.h>
#include <math_utils.h>

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
		Coordinates tmp = Coordinates(par.speed * cos(angle),
		                              par.speed * sin(angle));
		this->coordinates += tmp;
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
		par.attack = params.attack;
		par.speed = params.speed;
		angle = math_utils::toRads(ang);
	}

	/**
	 * @brief act for bullet
	 */
	void act()
	{
		move();
	}

	friend std::ostream& operator<<(std::ostream& os, const ActorBullet &ab);
};

std::ostream& operator<<(std::ostream& os, const ActorBullet &ab)
{
	ab.Actor::print(os);
	os << ", angle " << math_utils::toSexa(ab.angle) << " ";
	os << ab.par;
	return os;
}

#endif /* ACTOR_BULLET_H_INCLUDED */
