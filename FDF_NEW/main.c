#include "fdf.h"

int	ft_close(void *param)
{
	// mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	(void)param;
	exit(0);
}

int mouse_move(int x, int y, fdf *data)
{
	data->shift_x = x;
	data->shift_y = y;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	// ft_printf("%d\n%d\n", x, y);
	return (0);
}

int	mouse_key(int key, int x, int y, fdf *data)
{
	// ft_printf("%d\n", key);
	if (key == 4)
		data->zoom += 5;
	if (key == 5)
		data->zoom -= 5;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

int	press_key(int key, fdf *data)
{
	// ft_printf("%d\n", key);
	if (key == 126)
		data->shift_y -= 10;
	if (key == 125)
		data->shift_y += 10;
	if (key == 123)
		data->shift_x -= 10;
	if (key == 124)
		data->shift_x += 10;
	if (key == 24)
		data->zoom += 5;
	if (key == 27)
		data->zoom -= 5;
	if (key == 53 || key == 17)
	 	ft_close(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}


int main(int argc, char **argv)
{
	fdf	*data;
	(void)argc;

	data = (fdf*)malloc(sizeof(fdf));
	// проверка на файл а не папку
	read_file(argv[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	data->zoom = 20;
	draw(data);
	//mlx_key_hook(data->win_ptr, press_key, data);
	mlx_hook(data->win_ptr, 2, 0, press_key, data);
	mlx_hook(data->win_ptr, 4, 0, mouse_key, data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0, ft_close, data);
	mlx_loop(data->mlx_ptr);
}
