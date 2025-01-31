/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** print_result
*/
#include "my/my.h"

void printcontent(char *dirpath, struct dirent **content,
    modifiers_t *modifiers)
{
    int printed = 0;
    int total_blocks = 0;
    struct stat file_stat;

    for (int i = 0; content[i] != NULL; i++)
        printed += print_name(content[i], modifiers,
            content[i + 1] != NULL, modifiers->l);
    if (printed > 0 && modifiers->l == 0)
        mini_printf(1, "\n");
    if (modifiers->l == 0)
        return;
    for (int i = 0; content[i] != NULL; i++) {
        if (stat(full_path(dirpath, content[i]->d_name), &file_stat) == 0)
            total_blocks += file_stat.st_blocks / 2;
    }
    mini_printf(1, "total %d\n", total_blocks);
    getlinfo(content, dirpath);
}

void printdir(char *dirpath, struct dirent **content, modifiers_t *modifiers,
    char *last_dir)
{
    char *fullpath;
    struct stat statbuf;

    printcontent(dirpath, content, modifiers);
    lastbackslash(dirpath, last_dir);
    for (int i = 0; content[i] != NULL; i++) {
        fullpath = full_path(dirpath, content[i]->d_name);
        if (stat(fullpath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode) &&
            modifiers->R > 0 && !((my_strlen(content[i]->d_name) == 1 &&
            content[i]->d_name[0] == '.') ||
            (my_strlen(content[i]->d_name) == 2 &&
            content[i]->d_name[0] == '.' &&
            content[i]->d_name[1] == '.')))
            get_info(fullpath, modifiers, 2,
                last_dir);
    free(fullpath);
    }
}

int print_result(char **args, modifiers_t *modifiers)
{
    int y = 0;
    struct stat path_stat;

    for (; args[y] != NULL; y++);
    for (int i = 0; args[i] != NULL; i++) {
        file_or_directory(args, i, modifiers);
        if (stat(args[i], &path_stat) != 0)
            return 84;
        if (S_ISREG(path_stat.st_mode) && i != y - 1)
            mini_printf(1, "\n");
    }
    return 0;
}

int print_name(struct dirent *entry, modifiers_t *modifiers, int spaces,
    int dont)
{
    int res = 0;

    if (entry->d_name[0] != '.' || modifiers->a > 0) {
        if (dont == 0)
            mini_printf(1, "%s", entry->d_name);
        res = 1;
    }
    if (dont == 0 && res == 1)
        if (spaces == 1)
            mini_printf(1, "  ");
    return res;
}
