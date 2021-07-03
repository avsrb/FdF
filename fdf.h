#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> //удалить
#include <math.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include "minilibx_macos/mlx.h"

typedef struct 
{
	int	width;
	int	height;
	int	**z_matrix;
	int	zoom;
	int	color;
	int	shift_x;
	int	shift_y;
	float	sin;
	float	cos;
	int	flatten;
	float shift_z;
	int	shift_zoom;
	int	flag_mv_mouse;

	void	*mlx_ptr;
	void	*win_ptr;
}				fdf;

void	ft_init(fdf *data);
int		ft_close(void *param);
void	read_file(char *file_name, fdf *data);
void	bresenham(float x, float y, float x1, float y1, fdf *data);
void	draw(fdf *data);

#endif
