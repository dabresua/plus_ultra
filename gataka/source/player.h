#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player {
private:
	int x; /*< x coordinate */
	int y; /* y coordinate */
public:
	public Player(int x, int y);
	public set_event(SDL_Event *e);

}

#endif /* PLAYER_H_INCLUDED */
