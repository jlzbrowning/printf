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
        length += _print_int(digit, 0, 0);

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
        length += _print_uint(digit, 0);

    _putchar((n % 10) + '0');
    length++;

    return (length);
}

int _print_octal(unsigned int n, int hash_flag)
{
    unsigned int digit, length = 0;

    if (hash_flag)
    {
        _putchar('0');
        length++;
    }

    digit = n / 8;
    if (digit > 0)
        length += _print_octal(digit, 0);

    _putchar((n % 8) + '0');
    length++;

    return (length);
}

int _print_hex(unsigned int n, int upper_case, int hash_flag)
{
    unsigned int digit, length = 0;

    if (hash_flag)
    {
        _putchar('0');
        _putchar(upper_case ? 'X' : 'x');
        length += 2;
    }

    digit = n / 16;
    if (digit > 0)
        length += _print_hex(digit, upper_case, 0);

    _putchar(upper_case ? "0123456789ABCDEF"[n % 16] : "0123456789abcdef"[n % 16]);
    length++;

    return (length);
}

int _print_S(char *str)
{
    int length = 0;

    while (*str)
    {
        if (*str < 32 || *str >= 127)
        {
            _putchar('\\');
            _putchar('x');
            _putchar("0123456789ABCDEF"[(*str / 16) % 16]);
            _putchar("0123456789ABCDEF"[*str % 16]);
            length += 4;
        }
        else
        {
            _putchar(*str);
            length++;
        }
        str++;
    }

    return (length);
}

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int i;
    char *str;
    int plus_flag = 0, space_flag = 0, hash_flag = 0;
    int length_l = 0, length_h = 0;
    int field_width = 0, precision = -1, width;

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;

            while (format[i] == '+' || format[i] == ' ' || format[i] == '#')
            {
                plus_flag |= format[i] == '+';
                space_flag |= format[i] == ' ';
                hash_flag |= format[i] == '#';
                i++;
            }

            while (format[i] >= '0' && format[i] <= '9')
            {
                field_width = field_width * 10 + format[i] - '0';
                i++;
            }

            if (format[i] == '.')
            {
                i++;
                precision = 0;
                while (format[i] >= '0' && format[i] <= '9')
                {
                    precision = precision * 10 + format[i] - '0';
                    i++;
                }
            }

            switch (format[i])
            {
            case 'c':
                _putchar(va_arg(args, int));
                count++;
                break;
            case 's':
                str = va_arg(args, char *);
                width = 0;
                while (*str && width < precision)
                {
                    _putchar(*str++);
                    count++;
                    width++;
                }
                break;
            case '%':
                _putchar('%');
                count++;
                break;
            case 'd':
            case 'i':
                count += _print_int(va_arg(args, int), plus_flag, space_flag);
                break;
            case 'u':
                count += _print_uint(va_arg(args, unsigned int), hash_flag);
                break;
            case 'o':
                count += _print_octal(va_arg(args, unsigned int), hash_flag);
                break;
            case 'x':
                count += _print_hex(va_arg(args, unsigned int), 0, hash_flag);
                break;
            case 'X':
                count += _print_hex(va_arg(args, unsigned int), 1, hash_flag);
                break;
            case 'S':
                count += _print_S(va_arg(args, char *));
                break;
            }

            plus_flag = space_flag = hash_flag = length_l = length_h = field_width = 0;
            precision = -1;
        }
        else
        {
            _putchar(format[i]);
            count++;
        }
    }

    _putchar(-1);
    va_end(args);

    return (count);
}
#endif
