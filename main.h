#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>

int _putchar(char c)
{
    return (write(1, &c, 1));
}

int _print_int(long int n, int plus_flag, int space_flag)
{
    unsigned long int m, digit, length = 0;

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

int _print_uint(unsigned long int n, int hash_flag)
{
    unsigned long int digit, length = 0;

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

int _print_octal(unsigned long int n, int hash_flag)
{
    unsigned long int digit, length = 0;

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
    int length_l = 0, length_h = 0;

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;

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

            while (format[i] == 'l' || format[i] == 'h')
            {
                if (format[i] == 'l')
                    length_l = 1;
                else if (format[i] == 'h')
                    length_h = 1;
                i++;
            }

            switch (format[i])
            {
            case 'c':
                _putchar(va_arg(args, int));
                count++;
                break;
            case 's':
                str = va_arg(args, char*);
                while (*str)
                {
                    _putchar(*str++);
                    count++;
                }
                break;
            case 'S':
                count += _print_S(va_arg(args, char *));
                break;
            case '%':
                _putchar('%');
                count++;
                break;
            case 'd':
            case 'i':
                if (length_l)
                    count += _print_int(va_arg(args, long int), plus_flag, space_flag);
                else if (length_h)
                    count += _print_int(va_arg(args, int), plus_flag, space_flag);
                else
                    count += _print_int(va_arg(args, int), plus_flag, space_flag);
                break;
            case 'u':
                if (length_l)
                    count += _print_uint(va_arg(args, unsigned long int), hash_flag);
                else if (length_h)
                    count += _print_uint(va_arg(args, unsigned int), hash_flag);
                else
                    count += _print_uint(va_arg(args, unsigned int), hash_flag);
                break;
            case 'o':
                if (length_l)
                    count += _print_octal(va_arg(args, unsigned long int), hash_flag);
                else if (length_h)
                    count += _print_octal(va_arg(args, unsigned int), hash_flag);
                else
                    count += _print_octal(va_arg(args, unsigned int), hash_flag);
                break;
            case 'x':
                if (length_l)
                    count += _print_hex(va_arg(args, unsigned long int), 0, hash_flag);
                else if (length_h)
                    count += _print_hex(va_arg(args, unsigned int), 0, hash_flag);
                else
                    count += _print_hex(va_arg(args, unsigned int), 0, hash_flag);
                break;
            case 'X':
                if (length_l)
                    count += _print_hex(va_arg(args, unsigned long int), 1, hash_flag);
                else if (length_h)
                    count += _print_hex(va_arg(args, unsigned int), 1, hash_flag);
                else
                    count += _print_hex(va_arg(args, unsigned int), 1, hash_flag);
                break;
            default:
                break;
            }

            plus_flag = 0;
            space_flag = 0;
            hash_flag = 0;
            length_l = 0;
            length_h = 0;
        }
        else
        {
            _putchar(format[i]);
            count++;
        }
    }

    va_end(args);

    return (count);
}
#endif
