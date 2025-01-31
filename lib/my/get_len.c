/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** get_len
*/

#include "my.h"

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    for (; str[i] != '\0'; i++);
    return i;
}

int my_number_len(long int nb)
{
    int i = 0;

    for (; nb > 0; i++)
        nb /= 10;
    return i;
}

int my_word_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

int my_dir_len(char *dir_name)
{
    DIR *dir = opendir(dir_name);
    int count = 0;
    struct dirent *entry = readdir(dir);

    while (entry != NULL) {
        count++;
        entry = readdir(dir);
    }
    closedir(dir);
    return count;
}
