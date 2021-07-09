#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx_macos/mlx.h"

# define RESOLUTION_X 1920
# define RESOLUTION_Y 1080
# define ZOOM 10

typedef struct s_point
{
	float	x;
	float	y;
	float	z;

}			t_point;

typedef struct s_fdf
{
	int		width;
	int		height;
	int		**z_matrix;
	float	zoom;
	int		color;
	int		shift_x;
	int		shift_y;
	float	sin;
	float	cos;
	float	shift_zoom;
	int		flag_mv_mouse;
	int		flag_iso;
	int		flag_left_button;
	float	flatten;
	double	rotation_x;
	double	rotation_y;
	double	rotation_z;

	void	*mlx_ptr;
	void	*win_ptr;

	void	*img_ptr;
	char	*xpm_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		mouse_x;
	int		mouse_y;

}				t_fdf;

float	ft_mod(float i);
float	ft_max(float x, float y);
void	ft_man(t_fdf *data);
void	rotate_x(t_point *p, t_point *p1, double alpha, t_fdf *data);
void	rotate_y(t_point *p, t_point *p1, double alpha, t_fdf *data);
void	rotate_z(t_point *p, t_point *p1, double alpha, t_fdf *data);
void	coordination(t_point *p, t_point *p1, t_fdf *data);
void	isometric (t_point *p, t_point *p1, t_fdf *data);
int		mouse_move(int x, int y, t_fdf *data);
int		mouse_key(int key, int x, int y, t_fdf *data);
int		press_key(int key, t_fdf *data);
void	ft_init(t_fdf *data);
int		ft_close(void);
void	ft_error(char *s);
void	read_file(char *file_name, t_fdf *data);
void	bresenham(t_point p, t_point p1, t_fdf *data);
void	draw(t_fdf *data);
int	ft_init_paralel(t_fdf *data);

#endif