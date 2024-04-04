/* Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------
Write a function named `ft_printf` that will mimic the real printf but 
it will manage only the following conversions: s,d and x.
Your function must be declared as follows:
int ft_printf(const char *, ... );
Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.
Exemples of the function output:
call: ft_printf("%s\n", "toto");
out: toto$
call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%
call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$
Obs: Your function must not have memory leaks. Moulinette will test that. */

#include <stdarg.h> // va_start, va_end, va_arg
#include <unistd.h> // write
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#define HEX "0123456789abcdef"

int dx_out(unsigned int ui, int base, int flag)
{
    static int i = 0;
    
    if (flag)
        i = 0;
    if (ui / base)
        dx_out (ui / base, base, 0);
    i += write(1, &HEX[ui % base], 1);
    return (i);
}

int ft_printf(const char *str, ... )
{
    int i = 0;
    int counter = 0;
    va_list ap;
    char *s = NULL;
    int d = 0;

    if (!*str || !str)
        return (0);
    va_start(ap, str);
    while(str[i])
    {
        if (str[i] == '%' && str[++i])
        {
            if (str[i] == '%')
                counter += write(1, &str[i], 1);
            else if (str[i] == 's')
            {
                s = va_arg(ap, char *);
                if (!s)
                    s = "(null)";
                while(*s)
                    counter += write(1, s++, 1);
            }
            else if (str[i] == 'd')
            {
                d = va_arg(ap, int);
                if (d == -2147483648)
                    counter += write(1, "-2147483648", 11);
                else
                {
                    if (d < 0)
                    {
                        counter += write(1, "-", 1);
                        d = -d;
                    }
                    counter += dx_out((unsigned int)d, 10, 1);
                }
            }
            else if (str[i] == 'x')
                counter += dx_out(va_arg(ap, unsigned int), 16, 1);
        }
        else
            counter += write(1, &str[i], 1);
        i++;
    }
    va_end(ap);
    return(counter);
}