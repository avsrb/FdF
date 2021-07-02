#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

# define ALL "cspdiuxX%-+.*0123456789"
# define DIGIT "-0123456789"

typedef struct s_flag
{
	int				minus;
	int				negative;
	int				plus;
	int				zero;
	int				space;
	int				dot;
	int				width;
	int				precision;
	unsigned int	base;
	int				hex_up;
	int				i;
	int				len;
}				t_flag;

int		ft_printf(const char *format, ...);

void	ft_putchar_len(char c, t_flag *spec);
void	ft_putstr_len(char *s, t_flag *spec);

char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		ft_nbrlen(long long n, t_flag *spec);
void	ft_zero_space(t_flag *spec, int num, int c);

void	ft_putnbr(unsigned long long n, t_flag *spec);
void	ft_init_flag(t_flag *spec);
void	ft_parsing(const char *format, t_flag *spec, va_list ap);
void	ft_parce_flag(const char *format, t_flag *spec);
void	ft_parce_width(const char *format, t_flag *spec, va_list ap);
void	ft_parce_precision(const char *format, t_flag *spec, va_list ap);

int		ft_process(const char *format, t_flag *spec, va_list ap);
void	ft_process_char(t_flag *spec, char c);

void	ft_process_str(t_flag *spec, char *str);
void	ft_process_int(t_flag *spec, long long nbr);
void	ft_process_int_unsigned(t_flag *spec, unsigned int nbr);
void	ft_process_int_signed(t_flag *spec, long long nbr);
void	ft_out(t_flag *spec);
void	ft_process_hex(t_flag *spec, unsigned int nbr);
void	ft_process_point(t_flag *spec, unsigned long nbr);
void	ft_address(t_flag *spec);
int		ft_workaround(t_flag *spec, unsigned long nbr);

#endif
