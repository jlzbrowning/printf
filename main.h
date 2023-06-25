#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024

typedef struct buffer
{
    char buff[BUFF_SIZE];
    int len;
} buffer_t;

void flush_buff(buffer_t *b)
{
    write(1, b->buff, b->len);
    b->len = 0;
}

void add_to_buff(buffer_t *b, char c)
{
    if (b->len == BUFF_SIZE)
        flush_buff(b);
    b->buff[b->len++] = c;
}

void _print_int(buffer_t *b, int n)
{
    unsigned int m, digit;

    if (n < 0)
    {
        add_to_buff(b, '-');
        m = -n;
    }
    else
    {
        m = n;
    }

    digit = m / 10;
    if (digit > 0)
    {
        _print_int(b, digit);
    }
    add_to_buff(b, (m % 10) + '0');
}

void _print_uint(buffer_t *b, unsigned int n)
{
    unsigned int digit;

    digit = n / 10;
    if (digit > 0)
    {
        _print_uint(b, digit);
    }
    add_to_buff(b, (n % 10) + '0');
}

void _print_octal(buffer_t *b, unsigned int n)
{
    unsigned int digit;

    digit = n / 8;
    if (digit > 0)
    {
        _print_octal(b, digit);
    }
    add_to_buff(b, (n % 8) + '0');
}

void _print_hex(buffer_t *b, unsigned int n, int upper_case)
{
    unsigned int digit;
    char symbols[] = "0123456789abcdef";
    char upper_symbols[] = "0123456789ABCDEF";

    digit = n / 16;
    if (digit > 0)
    {
        _print_hex(b, digit, upper_case);
    }

    if (upper_case)
        add_to_buff(b, upper_symbols[n % 16]);
    else
        add_to_buff(b, symbols[n % 16]);
}

void _printf(const char *format, ...)
{
    va_list args;
    buffer_t b = {{0}, 0};
    int i;

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
                add_to_buff(&b, va_arg(args, int));
                break;
            case 's': /* string */
                char *str = va_arg(args, char*);
                while (*str)
                    add_to_buff(&b, *str++);
                break;
            case '%': /* literal '%' */
                add_to_buff(&b, '%');
                break;
            case 'd': /* decimal (base 10) */
            case 'i': /* integer (base 10) */
                _print_int(&b, va_arg(args, int));
                break;
            case 'u': /* unsigned int */
                _print_uint(&b, va_arg(args, unsigned int));
                break;
            case 'o': /* octal */
                _print_octal(&b, va_arg(args, unsigned int));
                break;
            case 'x': /* hexadecimal (lower case) */
                _print_hex(&b, va_arg(args, unsigned int), 0);
                break;
            case 'X': /* hexadecimal (upper case) */
                _print_hex(&b, va_arg(args, unsigned int), 1);
                break;
            default:
                /* If the character isn't one we know, ignore it */
                break;
            }
        }
        else /* if it's not a '%', just print the character */
            add_to_buff(&b, format[i]);
    }

    flush_buff(&b);
    va_end(args);
}
#endif
