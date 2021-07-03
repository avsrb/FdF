#include "fdf.h"

int	ft_close(void *param)
{
	// mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	(void)param;
	exit(0);
}

void	ft_error(void)
{
	write (1, "Check_arguments\n", 16);
	exit(-1);
}

int mouse_move(int x, int y, fdf *data)
{
	if (data->flag_mv_mouse == 1)
	{
		data->shift_x = x;
		data->shift_y = y;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	// ft_printf("%d\n%d\n", x, y);
	return (0);
}

int	mouse_key(int key, int x, int y, fdf *data)
{
	(void)x;
	(void)y;
	ft_printf("%d\n", key);
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
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

int	press_key(int key, fdf *data)
{
	//ft_printf("%d\n", key);
	if (key == 13)
		data->shift_y -= 10;
	if (key == 1)
		data->shift_y += 10;
	if (key == 0)
		data->shift_x -= 10;
	if (key == 2)
		data->shift_x += 10;
	if (key == 24)
		data->zoom += 2;
	if (key == 27)
		data->zoom -= 2;
	if (key == 53 || key == 17)
		ft_close(data);
	if (key == 14)
	{
		data->shift_z -= 0.1;
	}
		printf("%f\n", data->shift_z);
	if (key == 12)
		data->shift_z += 0.1;
	if (key == 6)
		data->shift_z1 -= 30;
	if (key == 8)
		data->shift_z1 += 30;

	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

#define RESOLUTION_X 1920
#define RESOLUTION_Y 1080
#define ZOOM 10

int main(int argc, char **argv)
{
	fdf	data;

	// проверка на файл а не папку!!!!!!!!!!!!!!!!
	if (argc > 2 || argc == 1)
		ft_error();
	read_file(argv[1], &data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, RESOLUTION_X, RESOLUTION_Y, "FDF");
	ft_init(&data);
	draw(&data);
	mlx_hook(data.win_ptr, 2, 0, press_key, &data);
	mlx_hook(data.win_ptr, 4, 0, mouse_key, &data);
	mlx_hook(data.win_ptr, 6, 0, mouse_move, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}


void	ft_init(fdf *data)
{
	// data->width = 0;
	// data->height = 0;
	// data->zoom = 0;
	data->shift_x = RESOLUTION_X/2;
	data->shift_y = RESOLUTION_Y/2;
	data->shift_z = 0.523599;
	data->zoom = ZOOM;

	data->shift_z1 = 0;
	data->shift_zoom = 0;
	data->flag_mv_mouse = 0;
}