/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** handle_argv
*/
#include "my/my.h"

int are_valid_mods(modifiers_t *mods, char *str, char *invalid_mod)
{
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] != 'a' && str[i] != 'l' && str[i] != 'R'
            && str[i] != 'r' && str[i] != 'd' && str[i] != 't') {
            *invalid_mod = str[i];
            return 84;
            }
        if (str[i] == 'a')
            mods->a++;
        if (str[i] == 'l')
            mods->l++;
        if (str[i] == 'R')
            mods->R++;
        if (str[i] == 'r')
            mods->r++;
        if (str[i] == 'd')
            mods->d++;
        if (str[i] == 't')
            mods->t++;
    }
}

void get_mods(modifiers_t *mods, int ac, char **av, char *invalid_mod)
{
    int res = 0;

    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-' && my_strlen(av[i]) > 1)
            res = are_valid_mods(mods, av[i], invalid_mod);
        if (res == 84)
            return;
    }
}

modifiers_t init_modifiers(int ac, char **av, char *invalid_mod)
{
    modifiers_t mods;

    mods.a = 0;
    mods.l = 0;
    mods.R = 0;
    mods.r = 0;
    mods.d = 0;
    mods.t = 0;
    get_mods(&mods, ac, av, invalid_mod);
    return mods;
}

char **get_correct_files_names(char *avi, char **res, int *count, int *err)
{
    struct stat path_stat;

    if (avi[0] != '-' || my_strlen(avi) == 1) {
        if (stat(avi, &path_stat) != 0) {
            *err = 8;
            return res;
        }
        res[*count] = my_strdup(avi);
        (*count)++;
    }
    return res;
}

char **get_files(int ac, char **av)
{
    char **res;
    int count = 0;
    int err = 0;

    res = malloc((ac + 1) * sizeof(char *));
    if (res == NULL)
    return NULL;
    for (int i = 0; i < ac + 1; i++)
        res[i] = NULL;
    for (int i = 1; i < ac; i++) {
        res = get_correct_files_names(av[i], res, &count, &err);
        if (err != 0)
            break;
    }
    if ((res == NULL || res[0] == NULL) && err != 8) {
        res[0] = ".";
        count++;
    }
    res[count] = NULL;
    return res;
}
