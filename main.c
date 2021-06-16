#include "fdf.h"

int	deal_key(int key, void *data)
{
	ft_printf("%d", key);
	return (0);
}

int main (int argc, char **argv)
{
	fdf *data;

	data = (fdf*)malloc(sizeof(fdf));
	read_file(argv[1], data);

	int	i;
	int	j;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			ft_printf("%3d", data->z_matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}