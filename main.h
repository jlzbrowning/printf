#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int _putchar(char c);
int _print_int(long int n, int plus_flag, int space_flag);
int _print_uint(unsigned long int n, int hash_flag);
int _print_octal(unsigned long int n, int hash_flag);
int _print_hex(unsigned long int n, int upper_case, int hash_flag);
int _print_pointer(unsigned long int n);
int _print_S(char *str);
int _printf(const char *format, ...);

int _putchar(char c)
{
    static char buffer[BUFFER_SIZE];
    static int i;

    if (c == -1 || i >= BUFFER_SIZE)
    {
        write(1, buffer, i);
        i = 0;
    }

    if (c != -1)
    {
        buffer[i] = c;
        i++;
    }

    return (1);
}

int _print_int(long int n, int plus_flag, int space_flag)
{
    unsigned long int m, digit, length = 0;
    int sign_flag = n < 0;

    if (n < 0)
        m = -n;
    else
        m = n;

    digit = m / 10;
    if (digit > 0)
        length += _print_int(digit, plus_flag, space_flag);

    if (length == 0 && plus_flag && !sign_flag)
        _putchar('+');

    if (length == 0 && space_flag && !sign_flag && !plus_flag)
        _putchar(' ');

    if (sign_flag && length == 0)
        _putchar('-');

    _putchar((m % 10) + '0');
    length++;

    return (length);
}

int _print_uint(unsigned long int n, int hash_flag)
{
    unsigned long int digit, length = 0;

    if (hash_flag && length == 0)
        _putchar('0');

    digit = n / 10;
    if (digit > 0)
        length += _print_uint(digit, hash_flag);

    _putchar((n % 10) + '0');
    length++;

    return (length);
}

int _print_octal(unsigned long int n, int hash_flag)
{
    unsigned long int digit, length = 0;

    if (hash_flag && length == 0)
        _putchar('0');

    digit = n / 8;
    if (digit > 0)
        length += _print_octal(digit, hash_flag);

    _putchar((n % 8) + '0');
    length++;

    return (length);
}

int _print_hex(unsigned long int n, int upper_case, int hash_flag)
{
    unsigned long int digit, length = 0;
    char symbols[] = "0123456789abcdef";
    char upper_symbols[] = "0123456789ABCDEF";

    if (hash_flag && length == 0)
    {
        _putchar('0');
        _putchar(upper_case ? 'X' : 'x');
    }

    digit = n / 16;
    if (digit > 0)
        length += _print_hex(digit, upper_case, hash_flag);

    if (upper_case)
        _putchar(upper_symbols[n % 16]);
    else
        _putchar(symbols[n % 16]);
    length++;

    return (length);
}

int _print_pointer(unsigned long int n)
{
    unsigned long int digit, length = 0;

    if (length == 0)
    {
        _putchar('0');
        _putchar('x');
    }

    digit = n / 16;
    if (digit > 0)
        length += _print_hex(digit, 0, 0);

    _putchar("0123456789abcdef"[n % 16]);
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
    int field_width = 0, width;

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;

            while (format[i] >= '0' && format[i] <= '9')
            {
                field_width = field_width * 10 + (format[i] - '0');
                i++;
            }

            if (format[i] == '+')
            {
                plus_flag = 1;
                i++;
            }
            else if (format[i] == ' ')
            {
                space_flag = 1;
                i++;
            }
            else if (format[i] == '#')
            {
                hash_flag = 1;
                i++;
            }

            if (format[i] == 'l')
            {
                length_l = 1;
                i++;
            }
            else if (format[i] == 'h')
            {
                length_h = 1;
                i++;
            }

            switch (format[i])
            {
            case 'c':
                width = 1;
                while (width++ < field_width)
                    _putchar(' ');
                _putchar(va_arg(args, int));
                count += field_width;
                break;
            case 's':
                str = va_arg(args, char*);
                while (*str)
                {
                    _putchar(*str++);
                    count++;
                }
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case '%':
                _putchar('%');
                count++;
                break;
            case 'd':
            case 'i':
                count += _print_int(va_arg(args, int), plus_flag, space_flag);
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case 'u':
                count += _print_uint(va_arg(args, unsigned int), hash_flag);
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case 'o':
                count += _print_octal(va_arg(args, unsigned int), hash_flag);
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case 'x':
                count += _print_hex(va_arg(args, unsigned int), 0, hash_flag);
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case 'X':
                count += _print_hex(va_arg(args, unsigned int), 1, hash_flag);
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case 'p':
                count += _print_pointer(va_arg(args, unsigned long int));
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            case 'S':
                count += _print_S(va_arg(args, char *));
                while (count < field_width)
                {
                    _putchar(' ');
                    count++;
                }
                break;
            }

            plus_flag = space_flag = hash_flag = length_l = length_h = field_width = 0;
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
