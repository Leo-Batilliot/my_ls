/*
** EPITECH PROJECT, 2024
** mini printf
** File description:
** mini print f
*/
#include "my/my.h"

char *my_strdup(char *to_dup)
{
    int length = 0;
    char *res;

    while (to_dup[length] != '\0')
        length++;
    res = malloc(sizeof(char) * (length + 1));
    if (!res)
        return NULL;
    for (int i = 0; i < length; i++) {
        res[i] = to_dup[i];
    }
    res[length] = '\0';
    return res;
}

int my_putchar(int output, char c)
{
    if (output == 1)
        write(1, &c, 1);
    if (output == 2)
        write(2, &c, 1);
}

int my_putstr(int output, char *str)
{
    int i;

    if (str == NULL)
        return 84;
    for (i = 0; str[i] != '\0'; i = i + 1);
    if (output == 1)
        write(1, str, i);
    if (output == 2)
        write(2, str, i);
    return 0;
}

int my_put_nbr(int output, long nb)
{
    char res[1];

    if (nb < 0) {
        my_putstr(output, "-");
        nb = - nb;
    }
    if (nb >= 10) {
        my_put_nbr(output, nb / 10);
    }
    res[0] = nb % 10 + '0';
    my_putstr(output, res);
}

static void process_format(int output, char specifier, va_list ap)
{
    switch (specifier) {
        case 's':
            my_putstr(output, va_arg(ap, char *));
            break;
        case 'd':
            my_put_nbr(output, va_arg(ap, int));
            break;
        case 'i':
            my_put_nbr(output, va_arg(ap, int));
            break;
        case 'c':
            my_putchar(output, (char) va_arg(ap, int));
            break;
        case '%':
            my_putstr(output, "%");
        case 'l':
            my_put_nbr(output, va_arg(ap, long int));
            break;
    }
}

int mini_printf(int output, char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    while (*format) {
        if (*format == '%') {
            format++;
            process_format(output, *format, ap);
            format++;
        } else {
            my_putchar(output, *format);
            format++;
                }
    }
    va_end(ap);
    return 0;
}
