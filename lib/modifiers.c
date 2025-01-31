/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** modifiers
*/

#include "my/my.h"

int file_or_directory(char **args, int i, modifiers_t *modifiers)
{
    struct stat path_stat;
    char *last = getlastdir(args, modifiers);

    if (stat(args[i], &path_stat) != 0)
        return 84;
    if (S_ISREG(path_stat.st_mode))
        mini_printf(1, "%s\n", args[i]);
    if (S_ISDIR(path_stat.st_mode)) {
        get_info(args[i], modifiers, my_word_array_len(args), last);
    }
    return 0;
}

static struct dirent **open_directory(char *dir_path, modifiers_t *modifiers)
{
    DIR *dir = opendir(dir_path);
    struct dirent **dircontent;

    if (!dir)
        return NULL;
    dircontent = get_dir_content(dir, dir_path, modifiers);
    closedir(dir);
    if (modifiers->t > 0)
        dircontent = sort_dir_by_time(dircontent, dir_path);
    if (modifiers->r > 0)
        dircontent = reverse_dir(dircontent);
    return dircontent;
}

static int can_open(char *path)
{
    DIR *dir = opendir(path);

    if (!dir)
        return 1;
    closedir(dir);
    return 0;
}

static int my_strcmp(char *str1)
{
    int count = 0;

    if (str1 == NULL)
        return 84;
    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] == '/')
            count = 0;
        else
            count++;
    }
    if ((count == 1 && str1[my_strlen(str1) - 1] == '.') ||
        (count == 2 && str1[my_strlen(str1) - 2] == '.' &&
        str1[my_strlen(str1) - 1] == '.'))
        return 84;
    return 0;
}

static char *get_last_subdirectory(struct dirent **dircontent, char *dir_path,
    modifiers_t *modifiers)
{
    struct stat path_stat;
    char *path = NULL;
    char *temp = NULL;
    char *name = NULL;

    for (int i = 0; dircontent[i] != NULL; i++) {
        name = dircontent[i]->d_name;
        path = full_path(dir_path, name);
        if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode) &&
            (name[0] != '.' || modifiers->a > 0) && can_open(path) == 0 &&
            my_strcmp(name) == 0) {
            free(temp);
            temp = my_strdup(path);
        }
        free(path);
    }
    return temp;
}

char *reclastdir(char *dir_path, modifiers_t *modifiers)
{
    struct dirent **dircontent = open_directory(dir_path, modifiers);
    char *last_dir;
    char *result;

    if (!dircontent)
        return my_strdup(dir_path);
    last_dir = get_last_subdirectory(dircontent, dir_path, modifiers);
    for (int i = 0; dircontent[i] != NULL; i++)
        free(dircontent[i]);
    free(dircontent);
    if (last_dir) {
        result = reclastdir(last_dir, modifiers);
        free(last_dir);
    } else {
        result = my_strdup(dir_path);
    }
    return result;
}

char *getlastdir(char **args, modifiers_t *modifiers)
{
    int len = my_word_array_len(args) - 1;
    struct stat path_stat;
    char *deepest_dir;

    if (stat(args[len], &path_stat) != 0)
        return NULL;
    if (S_ISREG(path_stat.st_mode))
        return NULL;
    if (modifiers->R == 0) {
        return args[len];
    }
    deepest_dir = reclastdir(args[len], modifiers);
    return deepest_dir;
}

int dflag(char **args, modifiers_t *modifiers)
{
    struct stat file_stat;
    infos_t info;

    for (int i = 0; args[i] != NULL; i++) {
        info.filepath = args[i];
        if (stat(info.filepath, &file_stat) == -1)
            continue;
        if (getpwuid(file_stat.st_uid)) {
            info.pwd = getpwuid(file_stat.st_uid)->pw_name;
        } else
            info.pwd = "unknown";
        if (getgrgid(file_stat.st_gid)) {
            info.grp = getgrgid(file_stat.st_gid)->gr_name;
        } else
            info.grp = "unknown";
        info.name = args[i];
        printl(&info, &file_stat, my_number_len(file_stat.st_size),
            my_number_len(file_stat.st_nlink));
    }
}

int modif(char **args, modifiers_t *modifiers)
{
    if (modifiers->t > 0)
        args = sort_files_by_time(args, my_word_array_len(args));
    if (modifiers->r > 0)
        args = my_rev_word_array(args);
    if (modifiers->d > 0 && modifiers->l > 0)
        return dflag(args, modifiers);
    if (modifiers->d > 0) {
        for (int i = 0; args[i] != NULL; i++)
            mini_printf(1, "%s  ", args[i]);
        mini_printf(1, "\n");
    } else
        return print_result(args, modifiers);
}
