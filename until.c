#include "fdf.h"

float	ft_mod(float i)
{
	if (i < 0)
		return (i * -1);
	return (i);
}

float	ft_max(float x, float y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

void	rotate_x(t_point *p, t_point *p1, double alpha, t_fdf *data)
{
	float	y_last;
	float	y_last1;

	y_last = p->y - ((data->height - 1) / 2);
	p->y = y_last * cos(alpha) + p->z * sin(alpha);
	p->z = -y_last * sin(alpha) + p->z * cos(alpha);
	y_last1 = p1->y - ((data->height - 1) / 2);
	p1->y = y_last1 * cos(alpha) + p1->z * sin(alpha);
	p1->z = -y_last1 * sin(alpha) + p1->z * cos(alpha);
}

void	rotate_y(t_point *p, t_point *p1, double alpha, t_fdf *data)
{
	float	x_last;
	float	x_last1;

	x_last = p->x - ((data->width - 1) / 2);
	p->x = x_last * cos(alpha) + p->z * sin(alpha);
	p->z = -x_last * sin(alpha) + p->z * cos(alpha);
	x_last1 = p1->x - ((data->width - 1) / 2);
	p1->x = x_last1 * cos(alpha) + p1->z * sin(alpha);
	p1->z = -x_last1 * sin(alpha) + p1->z * cos(alpha);
}

void	rotate_z(t_point *p, t_point *p1, double alpha, t_fdf *data)
{
	float	x_last;
	float	y_last;
	float	x_last1;
	float	y_last1;

	(void)data;
	x_last = p->x;
	y_last = p->y;
	p->x = x_last * cos(alpha) + y_last * sin(alpha);
	p->y = -x_last * sin(alpha) + y_last * cos(alpha);
	x_last1 = p1->x;
	y_last1 = p1->y;
	p1->x = x_last1 * cos(alpha) + y_last1 * sin(alpha);
	p1->y = -x_last1 * sin(alpha) + y_last1 * cos(alpha);
}
