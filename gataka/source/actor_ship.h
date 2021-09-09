#ifndef ACTOR_SHIP_H_INCLUDED
#define ACTOR_SHIP_H_INCLUDED

#include <bullet_params.h>
#include <shoot_params.h>
#include <actor_bullet.h>
#include <queue>
#include <string>
#include <exceptions.h>

class ActorShip : public Actor
{
private:
	//int life; //TODO
	//int shield; //TODO
	//double mass; //TODO
	//double force; //TODO
	bullet_params_t bpar;
	double angle;
	std::queue <shoot_params_t> shoots; // TODO: thread safe or atomic
public:
	/**
	 * @brief Default constructor
	 */
	ActorShip() : Actor()
	{
		angle = 0;
	}

	/**
	 * @brief constructor
	 * @param c       Initial coordinates
	 * @param params  Bullet parameters
	 * @param angle   Initial angle
	 */
	ActorShip(Coordinates c, const bullet_params_t& params,
	          double angle = 0.0) : Actor(c)
	{
		bullet_params_copy(params, bpar);
		this->angle = angle;
	}

	/**
	 * @brief gets the bullet parameters
	 */
	const bullet_params_t& getBulletParams() const
	{
		/* TODO: const reference? */
		return bpar;
	}

	/**
	 * @brief Gets the number of bullets in queue
	 */
	size_t shootsInQueue() const
	{
		return shoots.size();
	}

	/**
	 * @brief pops the first shoot in queue
	 */
	shoot_params_t popShoot()
	{
		if (shoots.size() <= 0) {
			using namespace exceptions;
			throw std::underflow_error(message("No shoots on queue",
			                                   __FILE__, __LINE__));
		}
		shoot_params_t first = shoots.front();
		shoots.pop();
		return first;
	}

	/**
	 * @brief adds new shoot to the queue.
	 *        This function can be called internally and externally
	 */
	void shoot()
	{
		shoot_params_t sp = {this->coordinates, this->angle};
		shoots.push(sp);
	}

	void act()
	{
		std::cout << "I'm a ship" << std::endl;
	}
	//void accelerate(); //TODO

	friend std::ostream& operator<<(std::ostream& os, const ActorShip &ab);
};

std::ostream& operator<<(std::ostream& os, const ActorShip &as)
{
	as.Actor::print(os);
	os << ", angle " << math_utils::toSexa(as.angle) << " ";
	os << as.shootsInQueue() << "shoots " << as.bpar;
	return os;
}

#endif /* ACTOR_SHIP_H_INCLUDED */
