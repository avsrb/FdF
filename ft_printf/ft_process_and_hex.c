#include "ft_printf.h"

int	ft_process(const char *format, t_flag *spec, va_list ap)
{
	if (format[spec->i] == 'c')
		ft_process_char(spec, va_arg(ap, int));
	else if (format[spec->i] == '%')
		ft_process_char(spec, '%');
	else if (format[spec->i] == 's')
		ft_process_str(spec, va_arg(ap, char *));
	else if (format[spec->i] == 'd' || format[spec->i] == 'i')
		ft_process_int(spec, va_arg(ap, int));
	else if (format[spec->i] == 'u')
		ft_process_int_unsigned(spec, va_arg(ap, unsigned int));
	else if (format[spec->i] == 'x' || format[spec->i] == 'X')
	{
		spec->base = 16;
		if (format[spec->i] == 'X')
			spec->hex_up = 1;
		ft_process_hex(spec, va_arg(ap, unsigned int));
	}
	else if (format[spec->i] == 'p')
	{
		spec->base = 16;
		ft_process_point(spec, va_arg(ap, unsigned long));
	}
	else
		return (-1);
	return (0);
}

void	ft_process_hex(t_flag *spec, unsigned int nbr)
{
	int	nbrlen;

	nbrlen = ft_nbrlen(nbr, spec);
	if (spec->precision == 0 && nbr == 0)
		return (ft_out(spec));
	if (spec->precision > -1)
		spec->zero = 0;
	if (spec->precision < nbrlen)
		spec->precision = nbrlen;
	if (!spec->minus)
	{
		if (spec->zero)
			ft_zero_space(spec, spec->width - spec->precision + 1, '0');
		else
			ft_zero_space(spec, spec->width - spec->precision + 1, ' ');
	}
	if (spec->space)
		ft_putchar_len(' ', spec);
	else if (spec->plus)
		ft_putchar_len('+', spec);
	ft_zero_space(spec, spec->precision - nbrlen + 1, '0');
	ft_putnbr(nbr, spec);
	if (spec->minus)
		ft_zero_space(spec, spec->width - spec->precision + 1, ' ');
}

void	ft_process_point(t_flag *spec, unsigned long nbr)
{
	int	nbrlen;

	nbrlen = ft_nbrlen(nbr, spec);
	spec->width = spec->width - 2;
	if ((ft_workaround (spec, nbr)) == -1)
		return ;
	if (spec->precision > -1)
		spec->zero = 0;
	if (spec->precision < nbrlen)
		spec->precision = nbrlen;
	if (!spec->minus)
	{
		if (spec->zero)
			ft_zero_space(spec, spec->width - spec->precision + 1, '0');
		else
			ft_zero_space(spec, spec->width - spec->precision + 1, ' ');
	}
	ft_address(spec);
	ft_zero_space(spec, spec->precision - nbrlen + 1, '0');
	ft_putnbr(nbr, spec);
	if (spec->minus)
		ft_zero_space(spec, spec->width - spec->precision + 1, ' ');
}

int	ft_workaround(t_flag *spec, unsigned long nbr)
{
	if (spec->precision == 0 && nbr == 0)
	{
		if (spec->width)
			ft_zero_space(spec, spec->width - spec->precision + 1, ' ');
		spec->precision = 1;
		ft_address(spec);
		return (-1);
	}
	return (0);
}

void	ft_address(t_flag *spec)
{
	if (spec->precision >= 1)
	{
		ft_putchar_len('0', spec);
		ft_putchar_len('x', spec);
	}
}
