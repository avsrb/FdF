#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

	void	*mlx_ptr;
	void	*win_ptr;
}				fdf;

void	read_file(char *file_name, fdf *data);
void	bresenham(float x, float y, float x1, float y1, fdf *data);
void	draw(fdf *data);

#endif
