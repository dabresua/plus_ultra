#include <actor.h>
#include <actor_bullet.h>
#include <actor_ship.h>
#include <iostream>
#include <exception>

std::atomic_long Actor::idCounter(0);

class BadActor : public Actor
{
public:
	/**
	 * @brief constructor
	 */
	BadActor() : Actor()
	{
		std::cout << "but I'm bad by default" << std::endl;
	}

	/**
	 * @brief constructor
	 * @param coordinates
	 */
	BadActor(Coordinates c) : Actor(c)
	{
		std::cout << "but I'm bad" << std::endl;
	}

	/**
	 * @brief main function of an actor, all actors act
	 * @override Actor::act()
	 */
	void act()
	{
		std::cout << "I'm bad at acting" << std::endl;
	}
};

int main()
{
	using namespace std;
	int tmp = Actor::getIdCounter();

	BadActor a;
	cout << a << endl;
	cout << Actor::getIdCounter() << endl;


	BadActor b = BadActor({3,4});
	cout << b << endl;

	b.setX(80);
	b.setY(90);
	cout << b.getX() << " " << b.getY() << endl;
	b.act();

	cout << endl;
	cout << "------------------ Bullet -------------------" << endl;

	ActorBullet bullet1;
	cout << bullet1 << endl;
	bullet1.act();
	cout << bullet1 << endl;

	bullet_params_t bpar = {.attack = 3, .speed = 10.0};
	ActorBullet bullet2 = ActorBullet({50,50}, bpar, 30);
	cout << bullet2 << endl;
	for (size_t i = 0; i < 20; i++) {
		bullet2.act();
		cout << bullet2 << endl;
	}

	cout << endl;
	cout << "------------------ Ship -------------------" << endl;

	ActorShip ship1;
	cout << ship1 << endl;
	ship1.act();
	cout << ship1.shootsInQueue() << endl;
	shoot_params_t sp;
	try {
		sp = ship1.popShoot();
		cout << sp << endl;
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}
	cout << ship1.shootsInQueue() << endl;

	cout << "------------------ Ship 2 -------------------" << endl;
	bullet_params_t bp = {30, 10};
	ActorShip ship2 = ActorShip({200,150}, bp, 30);
	cout << ship2 << endl;
	ship2.shoot();
	cout << ship2.shootsInQueue() << endl;
	try {
		sp = ship2.popShoot();
		cout << sp << endl;
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}
	cout << sp << endl;
	cout << ship2.shootsInQueue() << endl;
	cout << ship2.getBulletParams() << endl;

	return 0;
}
