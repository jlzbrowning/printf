#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>

int _putchar(char c)
{
    return (write(1, &c, 1));
}

int _print_int(int n)
{
    unsigned int m, digit, length = 0;

    if (n < 0)
    {
        _putchar('-');
        length++;
        m = -n;
    }
    else
    {
        m = n;
    }

    digit = m / 10;
    if (digit > 0)
    {
        length += _print_int(digit);
    }
    _putchar((m % 10) + '0');
    length++;

    return (length);
}

int _print_uint(unsigned int n)
{
    unsigned int digit, length = 0;

    digit = n / 10;
    if (digit > 0)
    {
        length += _print_uint(digit);
    }
    _putchar((n % 10) + '0');
    length++;

    return (length);
}

int _print_octal(unsigned int n)
{
    unsigned int digit, length = 0;

    digit = n / 8;
    if (digit > 0)
    {
        length += _print_octal(digit);
    }
    _putchar((n % 8) + '0');
    length++;

    return (length);
}

int _print_hex(unsigned int n, int upper_case)
{
    unsigned int digit, length = 0;
    char symbols[] = "0123456789abcdef";
    char upper_symbols[] = "0123456789ABCDEF";

    digit = n / 16;
    if (digit > 0)
    {
        length += _print_hex(digit, upper_case);
    }

    if (upper_case)
        _putchar(upper_symbols[n % 16]);
    else
        _putchar(symbols[n % 16]);
    length++;

    return (length);
}

int _print_S(char *str)
{
    int count = 0;

    while (*str)
    {
        if ((*str >= 0 && *str < 32) || *str >= 127)
        {
            _putchar('\\');
            _putchar('x');
            count += 2;
            if (*str < 16)
                _putchar('0');
            count += _print_hex(*str, 1);
        }
        else
        {
            _putchar(*str);
            count++;
        }
        str++;
    }

    return (count);
}

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int i;
    char *str;

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%') /* this means a specifier is coming */
        {
            i++; /* skip the '%' */

            /* Now we check for our known specifiers */
            switch (format[i])
            {
            case 'c': /* char */
                _putchar(va_arg(args, int));
                count++;
                break;
            case 's': /* string */
                str = va_arg(args, char*);
                while (*str)
                {
                    _putchar(*str++);
                    count++;
                }
                break;
            case 'S': /* Custom conversion specifier 'S' */
                count += _print_S(va_arg(args, char *));
                break;
            case '%': /* literal '%' */
                _putchar('%');
                count++;
                break;
            case 'd': /* decimal (base 10) */
            case 'i': /* integer (base 10) */
                count += _print_int(va_arg(args, int));
                break;
            case 'u': /* unsigned int */
                count += _print_uint(va_arg(args, unsigned int));
                break;
            case 'o': /* octal */
                count += _print_octal(va_arg(args, unsigned int));
                break;
            case 'x': /* hexadecimal */
                count += _print_hex(va_arg(args, unsigned int), 0);
                break;
            case 'X': /* hexadecimal (upper case) */
                count += _print_hex(va_arg(args, unsigned int), 1);
                break;
            default:
                /* If the character isn't one we know, ignore it */
                break;
            }
        }
        else /* if it's not a '%', just print the character */
        {
            _putchar(format[i]);
            count++;
        }
    }

    va_end(args);

    return (count);
}
#endif
