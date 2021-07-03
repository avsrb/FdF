#include "fdf.h"

#define MAX(a, b) ((a > b) ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

float	ft_mod(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

float	ft_max(float x, float y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

void	isometric (float *x, float *y, int z, fdf *data)
{
	*x = (*x - *y) * cos(data->shift_z);
	*y = (*x + *y) * sin(data->shift_z) - z;
	// *x = *x * cos(data->shift_z) - *y * sin(data->shift_z);
	// *y = *y * sin(data->shift_z) + *y * cos(data->shift_z) - z;


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
	
	if (data->zoom <= 2)
		data->zoom = 2;
	x *=data->zoom;
	y *=data->zoom;
	x1 *=data->zoom;
	y1 *=data->zoom;

	data->color = (z || z1) ? 0xe80c0c : 0xffffff;
	if (z1 > 0)
	{
		z1 += data->shift_z1;
		z += data->shift_z1;
	}
	isometric(&x, &y, z, data);
	isometric(&x1, &y1, z1, data);

	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;

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
