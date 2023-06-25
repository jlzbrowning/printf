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
