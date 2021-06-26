#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include "minilibx_macos/mlx.h"

typedef struct 
{
	int	width;
	int	height;
	int	**z_matrix;

	void	*mlx_ptr;
	void	*win_ptr;
}				fdf;

void	read_file(char *file_name, fdf *data);
void	bresenham(int x, int y, int x1, int y1, fdf *data);

#endif
