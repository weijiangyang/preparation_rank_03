#include <unistd.h>

#include <stdio.h>
void putnbr(int n)
{
    char buf[12];
    char tmp[12];
    int tlen;
    int len;

    tlen = 0;
    len = 0;
    if (n == 0)
        buf[len ++] = '0';
    if (n < 0)
    {
        buf[len++] = '-';
        n = -n;
    }
    while (n > 0)
    {
        tmp[tlen] = n % 10 + '0';
        tlen++;
        n /= 10;
    }
    while (tlen > 0)
    {
        tlen--;
        buf[len] = tmp[tlen];
        len++;
    }
    buf[len] = '\0';
    printf("%s\n", buf);
    

}

int main(void)
{
    putnbr(0);
    return (0);
}