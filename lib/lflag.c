/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** lflag
*/
#include "my/my.h"

static void user_perms(struct stat *file_stat)
{
    if ((*file_stat).st_mode & S_IRUSR)
        mini_printf(1, "r");
    else
        mini_printf(1, "-");
    if ((*file_stat).st_mode & S_IWUSR)
        mini_printf(1, "w");
    else
        mini_printf(1, "-");
    if ((*file_stat).st_mode & S_IXUSR)
        mini_printf(1, "x");
    else
        mini_printf(1, "-");
}

static void group_perms(struct stat *file_stat)
{
    if ((*file_stat).st_mode & S_IRGRP)
        mini_printf(1, "r");
    else
        mini_printf(1, "-");
    if ((*file_stat).st_mode & S_IWGRP)
        mini_printf(1, "w");
    else
        mini_printf(1, "-");
    if ((*file_stat).st_mode & S_IXGRP)
        mini_printf(1, "x");
    else
        mini_printf(1, "-");
}

static void other_perms(struct stat *file_stat)
{
    if ((*file_stat).st_mode & S_IROTH)
        mini_printf(1, "r");
    else
        mini_printf(1, "-");
    if ((*file_stat).st_mode & S_IWOTH)
        mini_printf(1, "w");
    else
        mini_printf(1, "-");
    if ((*file_stat).st_mode & S_IXOTH)
        mini_printf(1, "x");
    else
        mini_printf(1, "-");
}

void final_printl(infos_t *info, char mod_time[16], int highest, int largest)
{
    mod_time[16] = '\0';
    for (int i = 0; i < largest - my_number_len(info->nlink); i++)
        mini_printf(1, " ");
    mini_printf(1, " %l %s %s", info->nlink, info->pwd, info->grp);
    for (int i = 0; i < highest - my_number_len(info->size); i++)
        mini_printf(1, " ");
    mini_printf(1, " %l %s %s\n", info->size, mod_time + 4, info->name);
}

void printl(infos_t *info, struct stat *file_stat, int highest, int largest)
{
    if (getgrgid((*file_stat).st_gid)) {
            info->grp = getgrgid((*file_stat).st_gid)->gr_name;
        } else
            info->grp = "unknown";
    if (S_ISDIR((*file_stat).st_mode))
        mini_printf(1, "d");
    else if (S_ISLNK((*file_stat).st_mode))
        mini_printf(1, "l");
    else
        mini_printf(1, "-");
    user_perms(file_stat);
    group_perms(file_stat);
    other_perms(file_stat);
    info->size = (*file_stat).st_size;
    info->nlink = (*file_stat).st_nlink;
    final_printl(info, ctime(&file_stat->st_mtime), highest, largest);
}

static int how_long(struct dirent **dircontent, char *dirpath, int version)
{
    int max = 0;
    int now;
    struct stat file_stat;
    char *path;

    for (int i = 0; dircontent[i] != NULL; i++) {
        path = full_path(dirpath, dircontent[i]->d_name);
        if (stat(path, &file_stat) == -1)
            continue;
        if (version == 1)
            now = my_number_len(file_stat.st_size);
        if (version == 2)
            now = my_number_len(file_stat.st_nlink);
        if (now > max)
            max = now;
        free(path);
    }
    return max;
}

void getlinfo(struct dirent **content, char *dirpath)
{
    struct stat file_stat;
    infos_t info;
    int highest = how_long(content, dirpath, 1);
    int largest = how_long(content, dirpath, 2);

    for (int i = 0; content[i] != NULL; i++) {
        info.filepath = full_path(dirpath, content[i]->d_name);
        if (stat(info.filepath, &file_stat) == -1)
            return;
        if (getpwuid(file_stat.st_uid)) {
            info.pwd = getpwuid(file_stat.st_uid)->pw_name;
        } else
            info.pwd = "unknown";
        info.name = content[i]->d_name;
        printl(&info, &file_stat, highest, largest);
    }
}
