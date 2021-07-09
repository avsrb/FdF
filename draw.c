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
	int	y;

	y = 10;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 60, y, 0xffffff, "How to Use");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 30, 0xffffff, "Zoom: Scroll or +/-");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Move: Arrows");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Flatten: </>");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Rotate: Press mouse button");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Rotate:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "X-Axis - 2/8");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "Y-Axic - 4/6");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "Z-Axic - 1(3)/7(9)");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, 0xffffff, "Projection");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "ISO: I Key");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, 0xffffff, "Parallel: 5 Key");
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

void	rotate_x(t_point *p, t_point *p1, double alpha, t_fdf *data)
{
	float	y_last;
	float	y_last1;

	y_last = p->y - ((data->height - 1) / 2);
	p->y = y_last * cos(alpha) + p->z * sin(alpha);
	p->z = -y_last * sin(alpha) + p->z * cos(alpha);
	y_last1 = p1->y - ((data->width - 1) / 2);
	p1->y = y_last1 * cos(alpha) + p1->z * sin(alpha);
	p1->z = -y_last1 * sin(alpha) + p1->z * cos(alpha);
}

void	rotate_y(t_point *p, t_point *p1, double alpha, t_fdf *data)
{
	float	x_last;
	float	x_last1;

	x_last = p->x - ((data->width - 1) / 2);
	p->x = x_last * cos(alpha) + p->z * sin(alpha);
	p->z = -x_last * sin(alpha) + p->z * cos(alpha);
	x_last1 = p1->x - ((data->width - 1) / 2);
	p1->x = x_last1 * cos(alpha) + p1->z * sin(alpha);
	p1->z = -x_last1 * sin(alpha) + p1->z * cos(alpha);
}

void	rotate_z(t_point *p, t_point *p1, double alpha, t_fdf *data)
{
	float	x_last;
	float	y_last;
	float	x_last1;
	float	y_last1;

	x_last = p->x;
	y_last = p->y;
	p->x = x_last * cos(alpha) + y_last * sin(alpha);
	p->y = -x_last * sin(alpha) + y_last * cos(alpha);
	x_last1 = p1->x;
	y_last1 = p1->y;
	p1->x = x_last1 * cos(alpha) + y_last1 * sin(alpha);
	p1->y = -x_last1 * sin(alpha) + y_last1 * cos(alpha);
}

void	bresenham(t_point p, t_point p1, t_fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;

	p.z = data->z_matrix[(int)p.y][(int)p.x];
	p1.z = data->z_matrix[(int)p1.y][(int)p1.x];
	data->color = (p.z || p1.z) ? 0xe80c0c : 0xffffff;
	if (p1.z > 0.00001 || p.z > 0.00001)
	{
		p.z *= data->flatten;
		p1.z *= data->flatten;
	}
	rotate_x(&p, &p1, data->rotation_x, data);
	rotate_y(&p, &p1, data->rotation_y, data);
	rotate_z(&p, &p1, data->rotation_z, data);
	if (data->flag_iso == 1)
	{
		isometric(&p.x, &p.y, &p.z, data);
		isometric(&p1.x, &p1.y, &p1.z, data);
	}
	if (data->zoom <= 2)
		data->zoom = 2;
	p.x *=data->zoom;
	p.y *=data->zoom;
	p1.x *=data->zoom;
	p1.y *=data->zoom;

	p.x += data->shift_x;
	p.y += data->shift_y;
	p1.x += data->shift_x;
	p1.y += data->shift_y;

	x_step = p1.x - p.x;
	y_step = p1.y - p.y;
	max = ft_max((ft_mod(x_step)), (ft_mod(y_step)));
	x_step /= max;
	y_step /= max;
	while ((int)(p.x - p1.x) || (int)(p.y - p1.y))
	{
		pixel_put(data, p.x, p.y, data->color);
		p.x += x_step;
		p.y += y_step;
	}
}

void	draw(t_fdf *data)
{
	t_point	p;
	t_point	p1;

	data->img_ptr = mlx_new_image(data->mlx_ptr, RESOLUTION_X, RESOLUTION_Y);
	data->xpm_data = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel, &data->size_line, &data->endian);

	p.y = 0;
	while (p.y < data->height)
	{
		p.x = 0;
		while (p.x < data->width)
		{
			if (p.x < data->width - 1)
			{
				p1.x = p.x + 1;
				p1.y = p.y;
				bresenham(p, p1, data);
			}
			if (p.y < data->height - 1)
			{
				p1.x = p.x;
				p1.y = p.y + 1;
				bresenham(p, p1, data);
			}
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	ft_man(data);
}
