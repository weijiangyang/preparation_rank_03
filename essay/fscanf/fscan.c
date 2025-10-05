/*Assignment name  : ft_scanf
Expected files   : ft_scanf.c
Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------


Write a function named `ft_scanf` that will mimic the real scanf with the following constraints:

- It will manage only the following conversions: s, d, and c
- You don't have to handle the options *, m and '
- You don't have to handle the maximum field width
- You don't have to handle the types modifier characters (h, hh, l, etc.)
- You don't have to handle the conversions beginning with %n$

Your function must be declared as follows:

int ft_scanf(const char *, ... );

You will find in this directory a file containing a part of the code you will need, you just have to complete it.

To test your program compare your results with the real scanf.

Hint : You may need to read the man of scanf.*/

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    c = fgetc(f);
    while (c != EOF && isspace(c))
        c = fgetc(f);
    if (c == EOF)
        return (-1);
    ungetc(c, f);
    return (1);
}

int match_char(FILE *f, char c)
{
    int fc;

    fc = fgetc(f);
    if (fc == EOF)
        return (-1);
    if (fc == c)
        return (1);
    ungetc(c, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int c;

    c = fgetc(f);
    if (c == EOF)
        return (-1);
    char *ptr = va_arg(ap, char *);
    *ptr = (char)c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int result = 0;
    int sign;
    int read = 0;;

    sign = 1;
    match_space(f);
    int c = fgetc(f);
    if (c == EOF)
        return (-1);
    if (c == '+' || c == '-')
    {
        if (c == '-')
            sign = -1;
        c = fgetc(f);
    }
    if (!isdigit(c))
    {
        if (c != EOF)
            ungetc(c, f);
        return (-1); 
    }
    while (isdigit(c))
    {
        result = result * 10 + (isdigit(c) - '0');
        read = 1;
        c = fgetc(f);
    }
    if (c != EOF)
        unget(c, f);
    if (!read)
        return (-1);
    int *ptr = va_arg(ap, int *);
    *ptr = result * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
   int read = 0;
   match_space(f);
   char *p = va_arg(ap, char *);
   int c;
   while ((c = fgetc(f)) != EOF && !isspace(c))
   {
        *p = c;
        p++;
        read = 1;
   }
   if (c != EOF)
    ungetc(c, f);
   *p = '\0';
   if (read == 1)
    return (1);
   else 
    return (-1);
}

int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
    case 'c':
        return scan_char(f, ap);
    case 'd':
        match_space(f);
        return scan_int(f, ap);
    case 's':
        match_space(f);
        return scan_string(f, ap);
    case EOF:
        return -1;
    default:
        return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;

    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (match_conv(f, &format, ap) != 1)
                break;
            else
                nconv++;
        }
        else if (isspace(*format))
        {
            if (match_space(f) == -1)
                break;
        }
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }

    if (ferror(f))
        return EOF;
    return nconv;
}

int ft_scanf(const char *format, ...)
{
    // ...
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}