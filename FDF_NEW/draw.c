#include "fdf.h"

#define MAX(a, b) ((a > b) ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

// float	ft_mod(float i)
// {
// 	return (i < 0) ? -i : i;
// }

// float	ft_max(float x, float y)
// {
// 	if (x > y)
// 		return (x);
// 	else
// 		return (y);
// }
/*
void	get_step(float *x, float *y, t_point p2, t_point p1)
{
	*x = p2.x - p1.x;
	*y = p2.y - p1.y;
}
*/
float	mod(float a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}

float	max_mod(float a, float b)
{
	if (mod(a) > mod(b))
		return (mod(a));
	else
		return (mod(b));
}

void	bresenham(float x, float y, float x1, float y1, fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;

	x_step = x1 - x;
	y_step = y1 - y;
	
	max = MAX((MOD(x_step)), (MOD(y_step)));
	x_step /= max;
	y_step /= max;
	printf("LOC %f %f, %f %f\n", x, y, x1, y1);
	printf("x_step %f   y_step %f\n", x_step, y_step);
	printf("MAX %f\n", max);

	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xffffff);
		x += x_step;
		y += y_step;
	}
	printf("LOC %f %f, %f %f\n", x, y, x1, y1);
	printf("x_step %f   y_step %f\n", x_step, y_step);
	printf("MAX %f\n", max);

}
