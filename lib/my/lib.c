/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** lib
*/
#include "my.h"

static char *full_path2(char *path, char *dir, int lpath, int ldir)
{
    char *res = malloc(sizeof(char) * (lpath + ldir + 2));
    int count = 0;

    for (int i = 0; i < lpath; i++) {
        res[i] = path[i];
        count++;
    }
    if (res[lpath - 1] != '/') {
        res[lpath] = '/';
        count++;
    }
    for (int i = 0; i < ldir; i++) {
        res[count] = dir[i];
        count++;
    }
    res[count] = '\0';
    return res;
}

char *full_path(char *path, char *dir)
{
    int lpath = 0;
    int ldir = 0;
    char *res;

    if (path != NULL)
        lpath = my_strlen(path);
    if (dir != NULL)
        ldir = my_strlen(dir);
    res = full_path2(path, dir, lpath, ldir);
    return res;
}
