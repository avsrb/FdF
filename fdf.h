#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <string.h> // удалить
#include <errno.h>
#include <stdlib.h>
#include <stdio.h> //удалить
#include <math.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include "minilibx_macos/mlx.h"

#define RESOLUTION_X 1920
#define RESOLUTION_Y 1080
#define ZOOM 1


typedef struct
{
	int	width;
	int	height;
	int	**z_matrix;
	float	zoom;
	int	color;
	int	shift_x;
	int	shift_y;
	float	sin;
	float	cos;
	int shift_z;
	int	shift_zoom;
	int	flag_mv_mouse;
	float	flatten;

	void	*mlx_ptr;
	void	*win_ptr;
}				fdf;

typedef struct
{
	void	*img_ptr;
	char	*xpm_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

void	ft_init(fdf *data);
int		ft_close(void *param);
void	ft_error(char *s);
void	read_file(char *file_name, fdf *data);
void	bresenham(float x, float y, float x1, float y1, fdf *data, t_img *img);
void	draw(fdf *data);

#endif
