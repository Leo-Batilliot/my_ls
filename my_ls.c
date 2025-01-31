/*
** EPITECH PROJECT, 2024
** B-PSU-100-LIL-1-1-myls-leo.batilliot
** File description:
** my_ls (a, r, R, l, d, t)
*/
#include "lib/my/my.h"
void *my_memcpy(void *dest, const void *src, int n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    for (int i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

struct dirent **get_dir_content(DIR *dir, char *dir_na, modifiers_t *modifiers)
{
    int files = my_dir_len(dir_na);
    struct dirent **dircontent = malloc(sizeof(struct dirent *) * (files + 1));
    struct dirent *entry = readdir(dir);
    int count = 0;

    dircontent[files] = NULL;
    while ((entry)) {
        if (modifiers->a == 0 && entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        dircontent[count] = malloc(sizeof(struct dirent));
        my_memcpy(dircontent[count], entry, sizeof(struct dirent));
        entry = readdir(dir);
        count++;
    }
    dircontent[count] = NULL;
    return dircontent;
}

int lastbackslash(char *now, char *last)
{
    int lnow = 0;
    int llast = 0;

    if (last != NULL)
        llast = my_strlen(last);
    if (now != NULL)
        lnow = my_strlen(now);
    if (lnow != llast) {
        mini_printf(1, "\n");
        return 0;
    }
    for (int i = 0; i < lnow -1 && i < llast - 1; i++) {
        if (now[i] != last[i]) {
            mini_printf(1, "\n");
            mini_printf(1, "%s ||| %s", now, last);
            return 0;
        }
    }
    return 1;
}

int get_info(char *dir_path, modifiers_t *modifiers, int cond, char *last_dir)
{
    DIR *dir = opendir(dir_path);
    struct dirent **dircontent;

    if (dir == NULL)
        return 84;
    if (cond > 1 || dir_path != last_dir)
        mini_printf(1, "%s:\n", dir_path);
    dircontent = get_dir_content(dir, dir_path, modifiers);
    if (modifiers->t > 0)
        dircontent = sort_dir_by_time(dircontent, dir_path);
    if (modifiers->r > 0)
        dircontent = reverse_dir(dircontent);
    printdir(dir_path, dircontent, modifiers, last_dir);
    free(dircontent);
    closedir(dir);
    return 0;
}

int main(int ac, char **av)
{
    char invalid_mod = '\0';
    modifiers_t modifiers = init_modifiers(ac, av, &invalid_mod);
    char **args;

    if (invalid_mod != '\0')
        return 84;
    args = get_files(ac, av);
    modif(args, &modifiers);
    free(args);
    return 0;
}
