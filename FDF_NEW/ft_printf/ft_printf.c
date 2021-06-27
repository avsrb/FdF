#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_flag		spec;

	spec.i = 0;
	spec.len = 0;
	va_start(ap, format);
	while (format[spec.i] != '\0')
	{
		if (format[spec.i] == '%' && ft_strchr(ALL, format[spec.i]))
		{
			ft_parsing(format + 1, &spec, ap);
			if ((ft_process(++format, &spec, ap)) == -1)
				return (-1);
		}
		else
			ft_putchar_len(format[spec.i], &spec);
		spec.i++;
	}
	va_end(ap);
	return (spec.len);
}
