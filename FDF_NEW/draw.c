#include "fdf.h"

#define MAX(a, b) ((a > b) ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

float	ft_mod(float i)
{
	return (i < 0) ? -i : i;
}

float	ft_max(float x, float y)
{
	if (x > y)
		return (x);
	else
		return (y);
}
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
	int	max;
	int	z;
	int	z1;

	z = data->z_matrix[(int)y][(int)x];
	z1 = data->z_matrix[(int)y1][(int)x1];

	x *=data->zoom;
	y *=data->zoom;
	x1 *=data->zoom;
	y1 *=data->zoom;

	data->color = (z) ? 0xe80c0c : 0xffffff;
	x_step = x1 - x;
	y_step = y1 - y;
	
	max = ft_max((ft_mod(x_step)), (ft_mod(y_step)));
	x_step /= max;
	y_step /= max;
	// printf("LOC %f %f, %f %f\n", x, y, x1, y1);
	// printf("x_step %f   y_step %f\n", x_step, y_step);
	// printf("MAX %f\n", max);

	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	draw(fdf *data)
{
	int x;
	int y;

	y = 0;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresenham(x, y, x + 1, y, data);
			if (y < data->height - 1)
			bresenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
