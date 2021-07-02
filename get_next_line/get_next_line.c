#include "get_next_line.h"

static int	ft_result (char **line, char **remainder)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*remainder)[i] != '\n' && (*remainder)[i] != '\0')
		i++;
	if ((*remainder)[i] == '\n')
	{
		(*remainder)[i] = '\0';
		*line = ft_strdup(*remainder);
		tmp = ft_strdup(*remainder + (i + 1));
		free(*remainder);
		*remainder = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (0);
}

int	ft_check (char **line, char **remainder, int bwr)
{
	if (!bwr && !remainder)
	{
		*line = ft_strnew(0);
		return (0);
	}
	if (bwr < 0)
		return (-1);
	return (ft_result(line, &*remainder));
}

int	get_next_line (int fd, char **line)
{
	static char		*remainder[1024];
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;
	int				bwr;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || (read(fd, buf, 0) < 0))
		return (-1);
	bwr = 1;
	while (bwr > 0)
	{
		bwr = read(fd, buf, BUFFER_SIZE);
		buf[bwr] = '\0';
		if (remainder[fd] == NULL)
			remainder[fd] = ft_strdup(buf);
		else
		{	
			tmp = ft_strjoin(remainder[fd], buf);
			free (remainder[fd]);
			remainder[fd] = tmp;
		}
		if (ft_strchr(remainder[fd], '\n'))
			break ;
	}
	return (ft_check(line, &remainder[fd], bwr));
}
