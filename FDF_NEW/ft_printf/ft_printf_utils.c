#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == 0)
		return ((char *)s + i);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		negative;
	int		i;
	int		convert;

	negative = 1;
	i = 0;
	convert = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		convert = convert * 10 + (str[i] - '0');
		i++;
	}
	return (convert * negative);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}
