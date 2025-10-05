#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

int ft_putstr(char *s)
{
    int len;

    len = 0;
    while (*s)
    {
        len += ft_putchar(*s);
        s++;
    }
    return (len);
}

int ft_putnbr(int n)
{
    int count;

    count = 0;
    if (n == -2147483648)
    {
        count += ft_putstr("-2147483648");
        return (count);
    }

    if (n < 0)
    {
        count += ft_putchar('-');
        n = -n;
    }
    if (n > 9)
        count += ft_putchar(n % 10 + '0');
    count += ft_putchar(n % 10 + '0');
    return (count);
}

int ft_putunbr(unsigned int n)
{
    int count;

    count = 0;
    if (n > 9)
        count += ft_putunbr(n / 10);
    count += ft_putchar(n % 10 + '0');
    return (count);
}


int ft_puthex(unsigned long n, char spec)
{
    int count;

    char *base;

    count = 0;
    if (spec == 'x')
        base = "0123456789abcdef";
    else
        base = "0123456789ABCDEF";
    if (n > 15)
        count += ft_puthex(n / 16, spec);
    count += ft_putchar(base[n % 16]);
    return (count);
}

int ft_printf(char *format, ...)
{
    int count;
    count = 0;
    va_list args;
    va_start(args, format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'c')
                count += ft_putchar(va_arg(args, int));
            else if (*format == 'd' || (*format == 'i'))
                count += ft_putnbr(va_arg(args, int));
            else if (*format == 's')
                count += ft_putstr(va_arg(args, char *));
            else if (*format == 'u')
                count += ft_putunbr(va_args(args, unsigned int));
            else if (*format == 'x' || *format == 'X')
                count += ft_puthex(va_arg(args, unsigned long), *format);
            else if (*format == 'p')
            {
                count += ft_putstr("0x");
                count += ft_puthex((unsigned long)va_arg(args, void *), 'x');// fais attention pour le type
            }
            else if (*format == '%')
                count += ft_putchar('%');
        }
        else
            count += ft_putchar(*format);
        format++;
    }
    va_end(args);
    return (count);
}