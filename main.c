#include "fdf.h"

int	ft_close(void *param)
{
	// mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	(void)param;
	exit(0);
}

void	ft_error(void)
{
	write (1, "Error\n", 6);
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
	if (key == 92 || key == 85)
	{
		data->sin -= 0.1;
		data->cos -= 0.1;
	}
	if (key == 83 || key == 89)
	{
		data->sin += 0.1;
		data->cos += 0.1;
	}
	if (key == 43)
		data->flatten -= 1;
	if (key == 47)
		data->flatten += 1;
	if (key == 35)
		data->sin = data->cos = 0;
	if (key == 34)
		data->sin = data->cos = 0.523599;
	if (key == 84)
		data->sin += 0.1;
	if (key == 91)
		data->sin -= 0.1;
	if (key == 86)
		data->cos += 0.1;
	if (key == 88)
		data->cos -= 0.1;
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

	if (argc > 2 || argc == 1)
		ft_error();
	read_file(argv[1], &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		ft_error();
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
	data->flatten = 1;
	data->shift_x = RESOLUTION_X/2;
	data->shift_y = RESOLUTION_Y/3;
	//data->sin = 0.523599;
	//data->cos = 0.523599;
	data->sin = 0.8;
	data->cos = 0.8;

	data->zoom = ZOOM;

	data->shift_z = 0;
	data->shift_zoom = 0;
	data->flag_mv_mouse = 0;
}