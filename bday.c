#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int sort(char *fname);
int get_birthdate(char *fname, char *date[3]);
int create_path(char *path, char *date[3]);

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
        sort(argv[i]);
}

int sort(char *fname)
{
    char *old_name = malloc(512 * sizeof(char));
    char *new_name = malloc(512 * sizeof(char));
    char *root_path = malloc(256 * sizeof(char));
    char *date[3];
    for (int i = 0; i < 3; ++i)
        date[i] = malloc(4 * sizeof(char));

    getcwd(root_path, 255);
    strcat(root_path, "/");
    strncpy(old_name, root_path, 256);
    strncpy(new_name, root_path, 256);
    strncat(old_name, fname, 256);

    get_birthdate(old_name, date);
    create_path(new_name, date);

    strncat(new_name, fname, 256);

    printf("%s -> %s", old_name, new_name);

    int err = renamex_np(old_name, new_name, RENAME_EXCL);

    printf(err ? " [X]\n" : "\n");

    free(old_name);
    free(new_name);
    free(root_path);
    for (int i = 0; i < 3; ++i)
        free(date[i]);
    return 0;
}

int create_path(char *root_path, char *date[3])
{
    int ret[3];

    for (int i = 0; i < 3; ++i) {
        strncat(root_path, date[i], 4);
        strcat(root_path, "/");
        ret[i] = mkdir(root_path, 0777);
    }

    return ret[0] && ret[1] && ret[2];
}

int get_birthdate(char *fname, char *date[3])
{
    struct stat info;
    if (lstat(fname, &info) < 0) { return -1; }

    struct tm *cdate = gmtime(&info.st_birthtime);

    strftime(date[0], 4, "%Y", cdate);
    strftime(date[1], 2, "%m", cdate);
    strftime(date[2], 2, "%d", cdate);

    return 0;
}
