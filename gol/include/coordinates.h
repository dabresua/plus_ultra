#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED

class Coordinates {
public:
	unsigned int x;
	unsigned int y;

	inline void set(unsigned int x, unsigned int y)
	{
		this->x = x;
		this->y = y;
	}
};

#endif /* COORDINATES_H_INCLUDED */
