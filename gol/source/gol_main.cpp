#include <gol.h>
#include <coordinates.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Gol g(180, 70);
	//Gol g(3, 10);
	cout << "w [" << g.getW() << "] h [" << g.getH() << "]" << endl;

	Coordinates c = {.x = 2, .y = 3};
	g.set(c);
	c.set(0,0);
	g.set(c);
	c.set(20-1, 30-1);
	g.set(c);
	//cout << g.to_hex() << endl;
	cout << g.to_string() << endl;

	g.generate(30);
	cout << g.to_hex() << endl;
	cout << g.to_string() << endl;

	do {
		g.run();
		cout << g.to_string() << endl;
	} while(1);

	return 0;
}
