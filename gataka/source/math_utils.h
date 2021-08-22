#ifndef MATH_UTILS_H_INCLUDED
#define MATH_UTILS_H_INCLUDED

namespace math_utils
{
	#define PI 3.14159265
	
	/**
	 * @brief converts sexagesimal angle into radians
	 * @param the angle in sexagesimal
	 * @returns the angle in radians
	 */
	const static inline double toRads(double sex)
	{
		return sex * PI / 180.0;
	}

	/**
	 * @brief converts sexagesimal angle into radians
	 * @param the angle in sexagesimal
	 * @returns the angle in radians
	 */
	const static inline double toSexa(double rads)
	{
		return rads * 180.0 / PI;
	}
};

#endif /* MATH_UTILS_H_INCLUDED */
