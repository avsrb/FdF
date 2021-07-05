#include "fdf.h"

#define MAX(a, b) ((a > b) ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

float	ft_mod(float i)
{
	if (i < 0)
		return (i * -1);
	return (i);
}

float	ft_max(float x, float y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

void	ft_man(fdf *data)
{
	int y; 
	y = 10;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 60, y, 0xffffff, "How to Use");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 30, 0xffffff, "Zoom: Scroll or +/-");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Move: Arrows");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Flatten: </>");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Rotate: Press left on or right off mouse button"); ///хуета
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Rotate:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "X-Axis - 2/8");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "Y-Axic - 4/6");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "Z-Axic - 1(3)/7(9)");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Projection");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "ISO: I Key");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "Parallel: P Key");
}

void	isometric (float *x, float *y, int z, fdf *data)
{
	*x = (*x - *y) * cos(data->cos);
	*y = (*x + *y) * sin(data->sin) - z * data->flatten;
	//*x = *x * cos(data->cos) - *y * sin(data->sin);
	//*y = *y * sin(data->sin) + *y * cos(data->cos) - z * data->flatten;


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
		z1 += data->shift_z;
		z += data->shift_z;
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
	//t_img	imp;

	ft_man(data);
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
