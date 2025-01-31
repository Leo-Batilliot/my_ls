/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** reverse
*/
#include "my.h"

static void swap_files(char **a, char **b)
{
    char *temp = *a;

    *a = *b;
    *b = temp;
}

char **sort_files_by_time(char **files, int len)
{
    struct stat stat_a;
    struct stat stat_b;
    int first_index;
    int second_index;

    for (int i = 0; i < len * len; i++) {
        if ((i + 1) % len == 0)
            continue;
        first_index = i % len;
        second_index = (i + 1) % len;
        if (stat(files[first_index], &stat_a) == -1)
            continue;
        if (stat(files[second_index], &stat_b) == -1)
            continue;
        if (stat_a.st_mtime < stat_b.st_mtime)
            swap_files(&files[first_index], &files[second_index]);
    }
    return files;
}

static void swap(struct dirent **a, struct dirent **b)
{
    struct dirent *temp = *a;

    *a = *b;
    *b = temp;
}

void time_sort(struct dirent **name1,
    struct dirent **name2, char *path)
{
    struct stat stat_a;
    struct stat stat_b;
    char *full_file_path_a = full_path(path, (*name1)->d_name);
    char *full_file_path_b = full_path(path, (*name2)->d_name);

    if (stat(full_file_path_a, &stat_a) == -1) {
        free(full_file_path_a);
        return;
    }
    if (stat(full_file_path_b, &stat_b) == -1) {
        free(full_file_path_b);
        return;
    }
    if (stat_a.st_mtime < stat_b.st_mtime)
        swap(name1, name2);
    free(full_file_path_a);
    free(full_file_path_b);
    return;
}

struct dirent **sort_dir_by_time(struct dirent **dir, char *path)
{
    int len = 0;
    int first_index;
    int second_index;
    struct stat stat_a;
    struct stat stat_b;
    char *full_file_path_a;
    char *full_file_path_b;

    for (; dir[len] != NULL; len++);
    for (int i = 0; i < len * len; i++) {
        if ((i + 1) % len == 0)
            continue;
        first_index = i % len;
        second_index = (i + 1) % len;
        time_sort(&dir[first_index], &dir[second_index], path);
    }
    return dir;
}

struct dirent **reverse_dir(struct dirent **dir)
{
    int len = 0;
    struct dirent *temp;

    for (; dir[len] != NULL; len++);
    for (int i = 0; i < len / 2; i++) {
        temp = dir[i];
        dir[i] = dir[len - i - 1];
        dir[len - i - 1] = temp;
    }
    return dir;
}

char **my_rev_word_array(char **args)
{
    int end = my_word_array_len(args);
    char *temp;

    for (int i = 0; i < end / 2; i++) {
        temp = args[i];
        args[i] = args[end - i - 1];
        args[end - i - 1] = temp;
    }
    return args;
}
