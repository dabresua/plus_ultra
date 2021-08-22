#ifndef BULLET_PARAMS_H_INCLUDED
#define BULLET_PARAMS_H_INCLUDED

/**
 * @file bullet_params.h
 * @brief Defines bullet parameters structure
 */

/** Bullet parameters */
typedef struct bullet_params_t {
	int attack;   /**< Attack: Basic damage that deals to ships */
	double speed; /**< Speed: movement amount every tick */
} bullet_params_t;

/**
 * @brief copies the contents of one structure into another
 * @param from  source data
 * @param to    destination object
 */
static inline
void bullet_params_copy(const bullet_params_t& from,  bullet_params_t& to)
{
	to.attack = from.attack;
	to.speed = from.speed;
}

std::ostream& operator<<(std::ostream& os, const bullet_params_t &bp)
{
	os << "Atk[" << bp.attack << "], spd[" << bp.speed << "]";
	return os;
}

#endif /* BULLET_PARAMS_H_INCLUDED */
