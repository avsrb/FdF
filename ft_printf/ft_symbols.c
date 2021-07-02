#include "ft_printf.h"

void	ft_putchar_len(char c, t_flag *spec)
{
	write (1, &c, 1);
	spec->len++;
}

void	ft_putstr_len(char *s, t_flag *spec)
{
	int	lenstr;

	lenstr = 0;
	if (s)
	{
		if (spec->precision == -1)
			lenstr = ft_strlen(s);
		else
			lenstr = spec->precision;
		while (*s && lenstr > 0)
		{
			ft_putchar_len(*s, spec);
			s++;
			lenstr--;
		}
	}
}

void	ft_process_char(t_flag *spec, char c)
{
	if (spec->minus == 1)
	{
		ft_putchar_len(c, spec);
		ft_zero_space(spec, spec->width, 0);
	}
	else
	{
		ft_zero_space(spec, spec->width, 0);
		ft_putchar_len(c, spec);
	}
}

void	ft_process_str(t_flag *spec, char *str)
{
	int	lenstr;

	lenstr = 0;
	if (!str)
		str = "(null)";
	while (str[lenstr])
		lenstr++;
	if (spec->precision < 0)
		spec->precision = -1;
	else if (spec->precision < lenstr && spec->dot == 1)
		lenstr = spec->precision;
	if (spec->minus == 1)
	{
		ft_putstr_len(str, spec);
		ft_zero_space(spec, spec->width - lenstr + 1, 0);
	}
	else
	{
		ft_zero_space(spec, spec->width - lenstr + 1, 0);
		ft_putstr_len(str, spec);
	}
}

void	ft_zero_space(t_flag *spec, int num, int c)
{
	if (c)
	{
		while (num-- && num > 0)
			ft_putchar_len(c, spec);
		return ;
	}
	while (num-- && num > 0)
	{
		if (!spec->minus && spec->zero)
			ft_putchar_len ('0', spec);
		else
			ft_putchar_len (' ', spec);
	}
}
