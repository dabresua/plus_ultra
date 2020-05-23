#include <gol.h>

#define GOL_DEFAULT_W 10
#define GOL_DEFAULT_H 10

Gol::Gol(int w, int h)
{
	width = w;
	height = h;
	world = new int[w*h/sizeof(int)];
}

int Gol::getW()
{
	return width;
}

int Gol::getH()
{
	return height;
}

void Gol::set(int c, int r)
{
	int pos = (c*r)/sizeof(int);
	int loc = (c*r)%sizeof(int);
	int masc = 1 << loc;
	world[pos] |= masc;
}

std::string Gol::toString()
{
	std::string str = "";
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			int pos = (i*j)/sizeof(int);
			int loc = (i*j)%sizeof(int);
			int masc = 1 << loc;
			str+= ((world[pos] & masc) > 0)?"x":" ";
		}
	}
	return str;
}
