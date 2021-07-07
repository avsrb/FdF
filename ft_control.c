#include "fdf.h"

int ft_init_paralel(t_fdf *data)
{
	data->flag_iso = 0;
	data->flatten = 0;
	data->shift_x = RESOLUTION_X/2;
	data->shift_y = RESOLUTION_Y/3;
	data->zoom = ZOOM;
	data->shift_zoom = 0;
	data->rotation_x = 0;
	data->rotation_y = 0;
	data->rotation_z = 0;
	return (0);
}

int mouse_move(int x, int y, t_fdf *data)
{
	if (data->flag_mv_mouse == 1)
	{
		data->shift_x = x;
		data->shift_y = y;
	}
	draw(data);
	return (0);
}

int	mouse_key(int key, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	// ft_printf("%d\n", key);
	if (key == 1)
		data->flag_mv_mouse = 1;
	if (key == 2)
		data->flag_mv_mouse = 0;
	if (key == 3)
		ft_init(data);
	if (key == 4)
		data->zoom += 2;
	if (key == 5)
		data->zoom -= 2;
	draw(data);
	return (0);
}

int	ft_control_rotation(int key, t_fdf *data)
{
	if (key == 34)
	{
		ft_init(data);
		data->sin = data->cos = 0.523599;
		data->flag_iso = 1;
		data->flatten = 1;
	}
	if (key == 87)
		ft_init_paralel(data);
	if (key == 91)
		data->rotation_x -= 0.05;
	if (key == 84)
		data->rotation_x += 0.05;
	if (key == 86)
		data->rotation_y -= 0.05;
	if (key == 88)
		data->rotation_y += 0.05;
	if (key == 92 || key == 85)
		data->rotation_z -= 0.05;
	if (key == 83 || key == 89)
		data->rotation_z += 0.05;
	return (0);
}

int	press_key(int key, t_fdf *data)
{
	//	printf("%d\n", key);
	if (key == 126)
		data->shift_y -= 10;
	if (key == 125)
		data->shift_y += 10;
	if (key == 123)
		data->shift_x -= 10;
	if (key == 124)
		data->shift_x += 10;
	if (key == 24 || key == 69)
		data->zoom += 2;
	if (key == 27 || key == 78)
		data->zoom -= 2;
	if (key == 53)
		ft_close(data);
	if (key == 43)
		data->flatten -= 0.1;
	if (key == 47)
		data->flatten += 0.1;
	if (key == 34 || key == 87 || key == 34 || key == 87 || \
		key == 91 || key == 84 || key == 86 || key == 88 || \
		key == 92 || key == 85 ||key == 83 || key == 89)
			ft_control_rotation(key, data);
	
	draw(data);
	return (0);
}