#include "minckim_cub3d.h"

void		img_put_color(t_img *img, int x, int y, int color)
{
	int		*point;

	point = (int*)((char*)img->addr + img->size_line * y \
			+ img->bits_per_pixel / 8 * x);
	*point = color;
}

unsigned int	img_pick_color(t_img *img, int x, int y)
{
	int		*point;

	point = (int*)((char*)img->addr + img->size_line * y \
			+ img->bits_per_pixel / 8 * x);
	return *point;
}

t_pixel		**init_pixel(int w, int h, t_img *img)
{
	t_pixel	**pixel;
	int		x;
	int		y;

	pixel = malloc(sizeof(t_pixel*) * w);
	x = -1;
	while (++x < w)
	{
		y = -1;
		pixel[x] = malloc(sizeof(t_pixel) * h);
		while (++y < h)
		{
			pixel[x][y].distance = INFINITY;
			pixel[x][y].color = (unsigned int*)((char*)img->addr\
			 + img->size_line * y + img->bits_per_pixel / 8 * x);
		}
	}
	return (pixel);
}
