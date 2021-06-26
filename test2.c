#include "minilibx_macos/mlx.h"
#include <stdio.h>
int x = 0;
int y = 0;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst; 

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_data *vars)
{
		x +=100;
		y +=100;
	printf("Hello from key_hook!\n");
	printf("%d\n%d\n", x, y);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	img.bits_per_pixel = 10;
	img.line_length = 10;
	img.endian = 10;
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// while(++i < 600)
	// 	my_mlx_pixel_put(&img, i, j, (0xFFFFFFF));
	// while(++j < 600)
	// 	my_mlx_pixel_put(&img, i, j, (0xFFFFFFF));
	// while(--i > 100)
	// 	my_mlx_pixel_put(&img, i, j, (0xFFFFFFF));
	// while(--j > 100)
	my_mlx_pixel_put(&img, x, y, (0xFFFFFFF));
	while (1)
	{
	//Обратите внимание, что 0x00FF0000это шестнадцатеричное представление ARGB(0,255,0,0)
	mlx_put_image_to_window(mlx, mlx_win, img.img, x, y);
	mlx_key_hook(mlx_win, key_hook, &img);
	mlx_loop(mlx);
	}
}
