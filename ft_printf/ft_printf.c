#include <unistd.h>
#include <stdarg.h>

void	putstring(char *s, int *length)
{
	if (!s)
		s = "(null)";
	while (*s)
		*length += write(1, s++, 1);
}

void	put_digit(long long num, int base, int *length)
{
	char	*hexadec = "0123456789abcdef";

	if (num < 0)
	{
		num *= -1;
		*length += write(1, "-", 1);
	}
	if (num >= base)
		put_digit(num / base, base, length);
	*length += write(1, &hexadec[num % base], 1);
}

int	ft_printf(const char *s, ...)
{
	int length = 0;

	va_list	list;
	va_start(list, s);

	while (*s)
	{
		if ((*s == '%') && (*(s + 1) == 's' || *(s + 1) == 'd' || *(s + 1) == 'x'))
		{
			s++;
			if (*s == 's')
				put_string(va_arg(list, char *), &length);
			else if (*s == 'd')
				put_digit((long long)va_arg(list, int), 10, &length);
			else if (*s == 'x')
				put_digit((long long)va_arg(list, unsigned int), 16, &length);
		}
		else
			length += write(1, s, 1);
		s++;
	}
	return (va_end(list), length);
}
