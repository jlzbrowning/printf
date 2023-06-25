#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>

int _putchar(char c)
{
    return (write(1, &c, 1));
}

int _print_int(int n, int plus_flag, int space_flag)
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
        if (plus_flag)
        {
            _putchar('+');
            length++;
        }
        else if (space_flag)
        {
            _putchar(' ');
            length++;
        }
    }

    digit = m / 10;
    if (digit > 0)
    {
        length += _print_int(digit, 0, 0);
    }
    _putchar((m % 10) + '0');
    length++;

    return (length);
}

int _print_uint(unsigned int n, int hash_flag)
{
    unsigned int digit, length = 0;

    if (hash_flag)
    {
        _putchar('0');
        length++;
    }

    digit = n / 10;
    if (digit > 0)
    {
        length += _print_uint(digit, 0);
    }
    _putchar((n % 10) + '0');
    length++;

    return (length);
}

int _print_octal(unsigned int n, int hash_flag)
{
    unsigned int digit, length = 0;

    digit = n / 8;
    if (digit > 0)
    {
        length += _print_octal(digit, 0);
    }

    if (hash_flag && length == 0)
    {
        _putchar('0');
        length++;
    }
    _putchar((n % 8) + '0');
    length++;

    return (length);
}

int _print_hex(unsigned long int n, int upper_case, int hash_flag)
{
    unsigned long int digit;
    int length = 0;
    char symbols[] = "0123456789abcdef";
    char upper_symbols[] = "0123456789ABCDEF";

    digit = n / 16;
    if (digit > 0)
    {
        length += _print_hex(digit, upper_case, 0);
    }

    if (hash_flag && length == 0)
    {
        _putchar('0');
        _putchar(upper_case ? 'X' : 'x');
        length += 2;
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
        if (*str < 32 || *str >= 127)
        {
            _putchar('\\');
            _putchar('x');
            _print_hex((unsigned int)*str, 1, 0);
            count += 4;
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
    int plus_flag = 0, space_flag = 0, hash_flag = 0;

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%') /* this means a specifier is coming */
        {
            i++; /* skip the '%' */

            /* check for flag characters */
            while (format[i] == '+' || format[i] == ' ' || format[i] == '#')
            {
                if (format[i] == '+')
                    plus_flag = 1;
                else if (format[i] == ' ')
                    space_flag = 1;
                else if (format[i] == '#')
                    hash_flag = 1;
                i++;
            }

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
            case 'S': /* string with non-printable characters in \xHH format */
                count += _print_S(va_arg(args, char *));
                break;
            case '%': /* literal '%' */
                _putchar('%');
                count++;
                break;
            case 'd': /* decimal (base 10) */
            case 'i': /* integer (base 10) */
                count += _print_int(va_arg(args, int), plus_flag, space_flag);
                break;
            case 'u': /* unsigned int */
                count += _print_uint(va_arg(args, unsigned int), hash_flag);
                break;
            case 'o': /* octal */
                count += _print_octal(va_arg(args, unsigned int), hash_flag);
                break;
            case 'x': /* hexadecimal */
                count += _print_hex(va_arg(args, unsigned int), 0, hash_flag);
                break;
            case 'X': /* hexadecimal (upper case) */
                count += _print_hex(va_arg(args, unsigned int), 1, hash_flag);
                break;
            default:
                /* If the character isn't one we know, ignore it */
                break;
            }

            plus_flag = 0;
            space_flag = 0;
            hash_flag = 0;
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
