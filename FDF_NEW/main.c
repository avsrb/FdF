#include "fdf.h"

int	deal_key(int key, void *data)
{
	(void)data;
	ft_printf("%d", key);
	return (0);
}

int main(int argc, char **argv)
{
	fdf	*data;
	(void)argc;

	data = (fdf*)malloc(sizeof(fdf));
	read_file(argv[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	
	bresenham(10, 10, 600, 600, data);
	mlx_key_hook(data->win_ptr, deal_key, NULL);
	mlx_loop(data->mlx_ptr);
}