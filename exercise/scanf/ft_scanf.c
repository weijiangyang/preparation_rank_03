#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int match_space(FILE *f)
{
    int c;

    c = fgetc(f);
    if (c != EOF && isspac(c))
        c = fgetc(f);
    if (c == EOF)
        return (-1);
    ungetc(c, f);
    return (1);  
}

int match_char(FILE *f, char c)
{
   char fc = fgetc(f);
   if (fc == c)
        return (1);
   if (fc == EOF)
        return (-1);
   if (fc != EOF)
   {
        ungetc(c, f);
        return (0); // return est 0 (not -1)
   }
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if (c == EOF)
        return (-1);
    char *p = va_arg(ap, int);
    *p = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int result = 0;
    int sign;
    int digit_scanned = 0;

    sign = 1;
    int c = fget(f);
    if (c == '+' || c == '-')
    {
        if (c == '-')
            sign = -1;
        c = fget(f);
    }
    if (c != EOF && isdigit(c))
    {
        result = result * 10 + (c - '0');
        digit_scanned++;
        c = fgetc(f);
    }
    if (c != EOF)
        unget(c, f);
    if (digit_scanned == 0)
        return (0); // si no digit, return 0
    int *ptr = va_arg(ap, int*);
    *ptr = sign * result;
    
    return (1);

    
}

int scan_string(FILE *f, va_list ap) 
{
    char *str = va_arg(ap, char *);
    int c = fgetc(f);
    int char_scanned = 0;
    while (c != EOF && !isspace(c))
    {
        str[char_scanned] = c;
        char_scanned++;
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);
    str[char_scanned] = '\0';
    if (char_scanned == 0)
        return (0);
    return (1);
    
}

int match_conv(FILE *f, const char **format, va_list ap) {
    switch (**format) {
        case 'c':
            return scan_char(f, ap);
        case 'd':
            return scan_int(f, ap);
        case 's':
            return scan_string(f, ap);
        default:
            return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap) {
    int nconv = 0;
    int ret;

    while (*format) {
        if (*format == '%') {
            format++;
            ret = match_conv(f, &format, ap);
            if (ret == -1) {
                return (nconv == 0) ? -1 : nconv;
            } else if (ret == 0) {
                return nconv;
            } else {
                nconv++;
            }
        } else if (isspace(*format)) {
            if (match_space(f) == -1) {
                return (nconv == 0) ? -1 : nconv;
            }
        } else {
            ret = match_char(f, *format);
            if (ret == -1) {
                return (nconv == 0) ? -1 : nconv;
            } else if (ret == 0) {
                return nconv;
            }
        }
        format++;
    }
    if (ferror(f)) {
        return -1;
    }
    return nconv;
}

int ft_scanf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}