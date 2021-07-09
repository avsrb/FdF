#include "fdf.h"

void	isometric (t_point *p, t_point *p1, t_fdf *data)
{
	p->x = (p->x - p->y) * cos(data->cos);
	p->y = (p->x + p->y) * sin(data->sin) - p->z;
	p1->x = (p1->x - p1->y) * cos(data->cos);
	p1->y = (p1->x + p1->y) * sin(data->sin) - p1->z;
}

void	pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < RESOLUTION_X)
	{
		if (y > 0 && y < RESOLUTION_Y)
		{
			dst = data->xpm_data + (y * data->size_line + x * \
									(data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

void	bresenham(t_point p, t_point p1, t_fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;

	p.z = data->z_matrix[(int)p.y][(int)p.x];
	p1.z = data->z_matrix[(int)p1.y][(int)p1.x];
	if (p.z || p1.z)
		data->color = 0xe80c0c;
	else
		data->color = 0xffffff;
	coordination(&p, &p1, data);
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

void	line (t_point *p, t_point *p1, t_fdf *data)
{
	if (p->x < data->width - 1)
	{
		p1->x = p->x + 1;
		p1->y = p->y;
		bresenham(*p, *p1, data);
	}
	if (p->y < data->height - 1)
	{
		p1->x = p->x;
		p1->y = p->y + 1;
		bresenham(*p, *p1, data);
	}
}

void	draw(t_fdf *data)
{
	t_point	p;
	t_point	p1;

	data->img_ptr = mlx_new_image(data->mlx_ptr, RESOLUTION_X, RESOLUTION_Y);
	data->xpm_data = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel, \
	&data->size_line, &data->endian);
	p.y = 0;
	while (p.y < data->height)
	{
		p.x = 0;
		while (p.x < data->width)
		{
			line(&p, &p1, data);
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	ft_man(data);
}
