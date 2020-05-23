#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED

#include <string>

class Gol {
public:
	Gol(int w, int h);
	int getW();
	int getH();
	std::string toString();
	void set(int c, int r);
	//void clr(int c, int r);

private:
	unsigned int width, height;
	int *world;
};

#endif /* GOL_H_INCLUDED */
