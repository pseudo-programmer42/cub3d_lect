#include "minckim_cub3d.h"

t_vec	equation_solver(t_vec *coeff0, t_vec *coeff1, t_vec *constant)
{
	t_vec	result;
	double	det;

	det = coeff0->x * coeff1->y - coeff1->x * coeff0->y;
	result.x = (coeff1->y * constant->x - coeff1->x * constant->y) / det;
	result.y = (coeff0->x * constant->y - coeff0->y * constant->x) / det;
	return (result);
}