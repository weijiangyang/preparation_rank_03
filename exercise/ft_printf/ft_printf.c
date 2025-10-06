#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>


int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putstr(char *s)
{
    int count;

    count = 0;
    if (!s)
        return (ft_putstr("(null)"));// oublie pas
    while(*s)
    {
        count += ft_putchar(*s);
        
        s++;
    }
    return (count);
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
        count += ft_putnbr(n / 10);
    count += ft_putchar (n % 10 + '0');
    return (count);
}

int ft_puthex(unsigned int n) // fais attention ici le type est unsigned int au lieu de unsigned long
{
    int count;

    count = 0;
    char *base = "0123456789abcdef";
    if (n > 15)
        count += ft_puthex(n / 16);
    count += ft_putchar(base[n % 16]);
    return (count);
}

int ft_printf(const char *format, ... )
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
            if (*format == 's')
                count += ft_putstr(va_arg(args, char *));
            if (*format == 'd')
                count += ft_putnbr(va_arg(args, int));
            if (*format == 'x')
                count += ft_puthex(va_arg(args, unsigned int));
        }
        else
            count += ft_putchar(*format);
        format++;
    }
    
    va_end(args);
    return (count);
}

/*#include <stdio.h>

int main(void)
{
    int count;

    count = ft_printf("Magic %s is %d", "number", 42);
    printf("%d\n", count);
  
    return (0);
}*/