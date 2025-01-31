/*
** EPITECH PROJECT, 2024
** myh
** File description:
** task 02
*/
#ifndef TEST_H
    #define TEST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <pwd.h>
    #include <grp.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <time.h>

typedef struct modifiers {
    int a;
    int l;
    int R;
    int r;
    int d;
    int t;
} modifiers_t;
typedef struct info {
    char *pwd;
    char *grp;
    char *filepath;
    char time_buf[80];
    char *name;
    unsigned long nlink;
    unsigned long size;
} infos_t;
int mini_printf(int output, char *format, ...);
modifiers_t init_modifiers(int, char **, char *);
char **get_files(int ac, char **av);
char **my_rev_word_array(char **args);
int my_word_array_len(char **array);
struct dirent **reverse_dir(struct dirent **dir);
int modif(char **args, modifiers_t *modifiers);
int my_dir_len(char *dir_name);
int print_result(char **args, modifiers_t *modifiers);
int print_name(struct dirent *entry, modifiers_t *modifiers,
    int spaces, int dont);
int are_valid_mods(modifiers_t *mods, char *str, char *invalid_mod);
void get_mods(modifiers_t *mods, int ac, char **av, char *invalid_mod);
int get_info(char *dir, modifiers_t *modifiers, int, char *);
struct dirent **sort_dir_by_time(struct dirent **dir, char *);
struct dirent **get_dir_content(DIR *dir, char *dir_name, modifiers_t *);
int my_strlen(char *str);
char *full_path(char *path, char *dir);
void printdir(char *dirpath, struct dirent **, modifiers_t *, char *);
int lastbackslash(char *now, char *last);
char *getlastdir(char **args, modifiers_t *modifiers);
int file_or_directory(char **args, int i, modifiers_t *modifiers);
char *my_strdup(char *to_dup);
char **sort_files_by_time(char **files, int len);
void getlinfo(struct dirent **content, char *dirpath);
int my_number_len(long int nb);
void printl(infos_t *info, struct stat *file_stat, int highest, int);

#endif /* TEST_H */
