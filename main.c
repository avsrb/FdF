#include "fdf.h"

int	ft_close(void)
{
	exit(0);
}

void	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	ft_init(t_fdf *data)
{
	data->flatten = 0;
	data->shift_x = RESOLUTION_X / 2;
	data->shift_y = RESOLUTION_Y / 3;
	data->sin = 0;
	data->cos = 0;
	data->zoom = ZOOM;
	data->shift_zoom = 0;
	data->rotation_x = 0;
	data->rotation_y = 0;
	data->rotation_z = 0;
	data->flag_mv_mouse = 0;
	data->flag_iso = 0;
	data->flag_left_button = 0;
}

int	mouse_release(int key, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	(void)key;
	data->flag_left_button = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	if (argc == 2)
	{
		read_file(argv[1], &data);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			ft_error(NULL);
		data.win_ptr = mlx_new_window(data.mlx_ptr, RESOLUTION_X, \
										RESOLUTION_Y, "FDF");
		ft_init_paralel(&data);
		draw(&data);
		mlx_hook(data.win_ptr, 2, 0, press_key, &data);
		mlx_hook(data.win_ptr, 4, 0, mouse_key, &data);
		mlx_hook(data.win_ptr, 5, 0, mouse_release, &data);
		mlx_hook(data.win_ptr, 6, 0, mouse_move, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
		mlx_loop(data.mlx_ptr);
	}
	ft_error(NULL);
	return (0);
}
