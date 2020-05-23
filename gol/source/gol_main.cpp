#include <gol.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Gol g(20, 30);
	cout << "w [" << g.getW() << "] h [" << g.getH() << "]" << endl;

	g.set(2, 0);
	cout << g.toString() << endl;
	return 0;
}
