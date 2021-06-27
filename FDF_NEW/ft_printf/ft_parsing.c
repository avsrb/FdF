#include "ft_printf.h"

void	ft_init_flag(t_flag *spec)
{
	spec->minus = 0;
	spec->plus = 0;
	spec->zero = 0;
	spec->space = 0;
	spec->dot = 0;
	spec->width = 0;
	spec->precision = -1;
	spec->base = 10;
	spec->hex_up = 0;
}

void 	ft_parsing(const char *format, t_flag *spec, va_list ap)
{
	ft_init_flag(spec);
	ft_parce_flag(format, spec);
	ft_parce_width(format, spec, ap);
	ft_parce_precision(format, spec, ap);
}

void	ft_parce_flag(const char *format, t_flag *spec)
{
	while (1)
	{
		if (format[spec->i] == '-')
			spec->minus = 1;
		else if (format[spec->i] == '+')
			spec->plus = 1;
		else if (format[spec->i] == '0')
			spec->zero = 1;
		else if (format[spec->i] == ' ')
			spec->space = 1;
		else
			break ;
		spec->i++;
	}
}

void	ft_parce_width(const char *format, t_flag *spec, va_list ap)
{
	if (format[spec->i] == '*')
	{
		spec->width = va_arg(ap, int);
		if (spec->width < 0)
		{
			spec->minus = 1;
			spec->width = -spec->width;
		}
		spec->i++;
		return ;
	}
	spec->width = ft_atoi(format + spec->i);
	while (ft_strchr(DIGIT, format[spec->i]))
		spec->i++;
}

void	ft_parce_precision(const char *format, t_flag *spec, va_list ap)
{
	if (format[spec->i] == '.')
	{
		spec->dot = 1;
		spec->i++;
	}
	else
		return ;
	if (format[spec->i] == '*')
	{
		spec->precision = va_arg(ap, int);
		spec->i++;
		return ;
	}
	spec->precision = ft_atoi(format + spec->i);
	while (ft_strchr(DIGIT, format[spec->i]))
		spec->i++;
}
