#include "fdf.h"

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

void	ft_man(t_fdf *data)
{
	int y; 
	y = 10;
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					60, y, 0xffffff, "How to Use");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					20, y += 30, 0xffffff, "Zoom: Scroll or +/-");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					20, y += 25, 0xffffff, "Move: Arrows");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					20, y += 25, 0xffffff, "Flatten: </>");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					20, y += 25, 0xffffff, "Rotate: Press left on or right off mouse button"); ///хуета
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					20, y += 25, 0xffffff, "Rotate:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					40, y += 20, 0xffffff, "X-Axis - 2/8");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					40, y += 20, 0xffffff, "Y-Axic - 4/6");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					40, y += 20, 0xffffff, "Z-Axic - 1(3)/7(9)");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					20, y += 25, 0xffffff, "Projection");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					40, y += 20, 0xffffff, "ISO: I Key");
	mlx_string_put(data->mlx_ptr, data->win_ptr, \
					40, y += 20, 0xffffff, "Parallel: 5 Key");
}


void	isometric (float *x, float *y, float *z, t_fdf *data)
{
	*x = (*x - *y) * cos(data->cos);
	*y = (*x + *y) * sin(data->sin) - *z;
}

void	pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;
	if (x > 0 && x < RESOLUTION_X)
	{
		if (y > 0 && y < RESOLUTION_Y)
		{
			dst = data->xpm_data + (y * data->size_line + x * (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

void	rotate_x(float *y, float *z, double alpha)
{
	float y_last;

	y_last = *y;
	*y = y_last * cos(alpha) + *z * sin(alpha);
	*z = -y_last * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(float *x, float *z, double alpha)
{
	float x_last;

	x_last = *x;
	*x = x_last * cos(alpha) + *z * sin(alpha);
	*z = -x_last * sin(alpha) + *z * cos(alpha);
}

void	rotate_z(float *x, float *y, double alpha)
{
	float x_last;
	float y_last;

	x_last = *x;
	y_last = *y;
	*x = x_last * cos(alpha) + y_last * sin(alpha);
	*y = -x_last * sin(alpha) + y_last * cos(alpha);
}

void	bresenham(float x, float y, float x1, float y1, t_fdf *data)
{
	float	x_step; 
	float	y_step;
	float	max;
	float	z;
	float	z1;
	
	z = data->z_matrix[(int)y][(int)x];
	z1 = data->z_matrix[(int)y1][(int)x1];
	
	data->color = (z || z1) ? 0xe80c0c : 0xffffff;
	
	if (z1 > 0.000001 || z > 0.000001)
	{
		z *= data->flatten;
		z1 *= data->flatten;
	}

	rotate_x(&y, &z, data->rotation_x);
	rotate_x(&y1, &z1, data->rotation_x);
	rotate_y(&x, &z, data->rotation_y);
	rotate_y(&x1, &z1, data->rotation_y);
	rotate_z(&x, &y, data->rotation_z);
	rotate_z(&x1, &y1, data->rotation_z);
	if (data->flag_iso == 1)
	{
		isometric(&x, &y, &z, data);
		isometric(&x1, &y1, &z1, data);
	}

	if (data->zoom <= 2)
		data->zoom = 2;
	x *=data->zoom;
	y *=data->zoom;
	x1 *=data->zoom;
	y1 *=data->zoom;

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
		pixel_put(data, x, y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *data)
{
	int x;
	int y;

	data->img_ptr = mlx_new_image(data->mlx_ptr, RESOLUTION_X, RESOLUTION_Y);
	data->xpm_data = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel, &data->size_line, &data->endian);

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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	ft_man(data);
}
