#ifndef SHOOT_PARAMS_H_INCLUDED
#define SHOOT_PARAMS_H_INCLUDED

/**
 * @file shoot_params.h
 * @brief Initial parameters for shoots.
 *        In adition to @ref bullet_params_t contains all the information to
 *        create a new bullet
 */

 /** Shoot parameters */
 typedef struct shoot_params_t {
 	Coordinates c; /**< Initial coordinates */
 	double angle;  /**< Initial angle */
 } shoot_params_t;

 std::ostream& operator<<(std::ostream& os, const shoot_params_t &sp)
 {
 	os << "Coords " << sp.c << ", angle [" << sp.angle << "]";
 	return os;
 }

#endif /* SHOOT_PARAMS_H_INCLUDED */
