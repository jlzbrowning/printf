#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

/**
 * _print_int - prints an integer character by character
 * @n: the integer to print
 *
 * Return: number of characters printed
 */
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

/**
 * _print_bin - prints an unsigned int in binary
 * @n: the number to print
 *
 * Return: number of characters printed
 */
int _print_bin(unsigned int n)
{
    unsigned int digit, length = 0;

    digit = n / 2;
    if (digit > 0)
    {
        length += _print_bin(digit);
    }
    _putchar((n % 2) + '0');
    length++;

    return (length);
}

/**
 * _printf - A simplified printf function
 * @format: format string (see man 3 printf)
 *
 * Return: number of characters printed
 */
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
            case '%': /* literal '%' */
                _putchar('%');
                count++;
                break;
            case 'd': /* decimal (base 10) */
            case 'i': /* integer (base 10) */
                count += _print_int(va_arg(args, int));
                break;
            case 'b': /* binary */
                count += _print_bin(va_arg(args, unsigned int));
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
