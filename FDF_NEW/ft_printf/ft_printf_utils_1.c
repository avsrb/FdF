#include "ft_printf.h"

int	ft_nbrlen(long long n, t_flag *spec)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	n /= spec->base;
	while (n)
	{
		i++;
		n /= spec->base;
	}
	return (i);
}

void	ft_putnbr(unsigned long long n, t_flag *spec)
{
	if (n >= spec->base)
	{
		ft_putnbr ((n / spec->base), spec);
		ft_putnbr ((n % spec->base), spec);
	}
	else if (n >= 10 && spec->hex_up)
		ft_putchar_len(n + '0' + 7, spec);
	else if (n >= 10)
		ft_putchar_len(n + '0' + 39, spec);
	else if (n <= 10)
		ft_putchar_len(n + '0', spec);
}
