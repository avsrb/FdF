#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*mem;

	i = 0;
	mem = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!mem)
		return (0);
	while (s1[i])
	{
		mem[i] = s1[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	if (!s1 || !s2)
		return (0);
	mem = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!mem)
		return (0);
	while (s1[i1])
	{
		mem[i1] = s1 [i1];
		i1++;
	}
	while (s2[i2])
	{
		mem[i1 + i2] = s2[i2];
		i2++;
	}
	mem[i1 + i2] = '\0';
	return (mem);
}

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

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	while (size > 0)
		str[size--] = '\0';
	str[0] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}
