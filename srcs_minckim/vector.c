#include "minckim_cub3d.h"
#include "minckim_macros.h"

t_vec	vec_new(double x, double y)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vec	vec_rot_min_ccw(t_vec a)
{
	static double	sin_unit;
	static double	cos_unit;
	t_vec			result;

	sin_unit = sin_unit ? sin_unit : sin(M_PI * ANGLE_MIN / 180);
	cos_unit = cos_unit ? cos_unit : cos(M_PI * ANGLE_MIN / 180);
	result.x = cos_unit * a.x - sin_unit * a.y;
	result.y = cos_unit * a.y + sin_unit * a.x;
	return (a);
}

t_vec	vec_rot_min_cw(t_vec a)
{
	static double	sin_unit;
	static double	cos_unit;
	t_vec			result;

	sin_unit = sin_unit ? sin_unit : -sin(M_PI * ANGLE_MIN / 180);
	cos_unit = cos_unit ? cos_unit : cos(M_PI * ANGLE_MIN / 180);
	result.x = cos_unit * a.x - sin_unit * a.y;
	result.y = cos_unit * a.y + sin_unit * a.x;
	return (a);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vec	vec_mul(t_vec a, double b)
{
	a.x *= b;
	a.y *= b;
	return (a);
}
