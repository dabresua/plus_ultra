#include <actor.h>
#include <iostream>

long Actor::idCounter;

int main()
{
	using namespace std;
	Coordinates c;
	cout << c << endl;

	c.setX(2);
	c.setY(3);
	cout << c << endl;
	cout << c.getX() << " " << c.getY() << endl;

	Coordinates d = Coordinates(c);
	cout << d << endl;

	Coordinates e = Coordinates(10, 20);
	cout << e << endl;

	e += {33, 45};
	cout << e << endl;

	return 0;
}
