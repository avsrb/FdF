#include "fdf.h"

void	coordination(t_point *p, t_point *p1, t_fdf *data)
{
	if (p->z > 0.000001 || p1->z > 0.000001)
	{
		p->z *= data->flatten;
		p1->z *= data->flatten;
	}
	rotate_x(p, p1, data->rotation_x, data);
	rotate_y(p, p1, data->rotation_y, data);
	rotate_z(p, p1, data->rotation_z, data);
	if (data->flag_iso == 1)
		isometric(p, p1, data);
	if (data->zoom <= 2)
		data->zoom = 2;
	p->x *=data->zoom;
	p->y *=data->zoom;
	p1->x *=data->zoom;
	p1->y *=data->zoom;
	p->x += data->shift_x;
	p->y += data->shift_y;
	p1->x += data->shift_x;
	p1->y += data->shift_y;
}

void	ft_man(t_fdf *data)
{
	int	y;

	y = 10;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 60, y, 0xffffff, "How to Use");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 30, \
							 0xffffff, "Zoom: Scroll or +/-");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, \
							 0xffffff, "Move: Arrows");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, \
							 0xffffff, "Flatten: </>");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, \
							 0xffffff, "Rotate:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, \
							 0xffffff, "X-Axis - 2/8");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, \
							 0xffffff, "Y-Axic - 4/6");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, \
							 0xffffff, "Z-Axic - 1(3)/7(9)");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, y += 25, \
							 0xffffff, "Projection");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, \
							 0xffffff, "ISO: I Key");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, y += 20, \
							 0xffffff, "Parallel: 5 Key");
}
