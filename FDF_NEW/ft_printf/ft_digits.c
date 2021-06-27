#include "ft_printf.h"

void	ft_out(t_flag *spec)
{
	if (spec->width == 0)
		return ;
	else if (spec->zero && spec->negative && spec->dot)
		ft_zero_space(spec, spec->width + 1, ' ');
	else
		ft_zero_space(spec, spec->width + 1, 0);
}

void	ft_process_int(t_flag *spec, long long nbr)
{
	if (spec->precision == 0 && nbr == 0)
		return (ft_out(spec));
	if (nbr >= 0)
		ft_process_int_unsigned(spec, nbr);
	else
	{
		nbr = -nbr;
		spec->negative = 1;
		ft_process_int_signed(spec, nbr);
	}
}

void	ft_process_int_unsigned(t_flag *spec, unsigned int nbr)
{
	int	nbrlen;

	nbrlen = ft_nbrlen (nbr, spec);
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

void	ft_process_int_signed(t_flag *spec, long long nbr)
{
	int	nbrlen;

	nbrlen = ft_nbrlen(nbr, spec);
	if (spec->precision > -1)
		spec->zero = 0;
	if (spec->precision < nbrlen)
		spec->precision = nbrlen;
	if (spec->zero)
		ft_putchar_len('-', spec);
	if (!spec->minus)
	{
		if (spec->zero)
			ft_zero_space(spec, spec->width - spec->precision, '0');
		else
			ft_zero_space(spec, spec->width - spec->precision, ' ');
	}
	if (!spec->zero)
		ft_putchar_len('-', spec);
	ft_zero_space(spec, spec->precision - nbrlen + 1, '0');
	ft_putnbr(nbr, spec);
	if (spec->minus)
		ft_zero_space(spec, spec->width - spec->precision, ' ');
}
