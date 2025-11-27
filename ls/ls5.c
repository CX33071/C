#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <limits.h>
#include <locale.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define PATH_MAX 4096
#define BLOCK_SIZE 512
char* dir1;
int flag_a = 0;
int flag_R = 0;
int flag_r = 0;
int flag_t = 0;
int flag_i = 0;
int flag_s = 0;
int flag_l = 0;
void init_locale() {
    setlocale(LC_COLLATE, "");
    setlocale(LC_CTYPE, "");
}
int type(char c,int is_chinese_char) {
    if(is_chinese_char){
        return 2;
    }else if(c>='0'&&c<='9'){
        return 3;
    }else if((c>='a'&&c<='z')||(c>='A'&&c<='Z')){
        return 0;
    }else{
        return 1;
    }
}
int youxianji(char* str) {
    char* ptr = str;
    while (*ptr == '.') {
        ptr++;
        if (*ptr == '\0') {
            return 2;
        }
    }
    unsigned char first_byte = (unsigned char)*ptr;
    if (first_byte >= 0xE0 && first_byte <= 0xEF) {
        return type(first_byte, 1);  
    } else {
        return type(first_byte, 0); 
    }
}
int is_chinese(char* str) {
    char* start = strchr(str, '.');
    int len;
    if (start == NULL) {
        len = strlen(str);
    } else {
        len = start - str;
    }
    char* ptr = str;
    int i = 0;
    while (i < len) {
        unsigned char c = (unsigned char)ptr[i];
        if (!(c >= 0xE0 && c <= 0xEF)) {
            return 0;
        }
        i += 3;
    }
    return 1;
}
int is_english(char* str) {
    if(*str=='.'){
        str++;
    }
    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (!((c >= 0x41 && c <= 0x5A) || (c >= 0x61 && c <= 0x7A)||(c=='.'))) {
            return 0;
        }
        str++;
    }
    return 1;
}

int compare_name(const void* a, const void* b) {
    struct dirent** e1 = (struct dirent**)a;
    struct dirent** e2 = (struct dirent**)b;
    if (strcmp((*e1)->d_name, ".") == 0)
        return -1;
    if (strcmp((*e2)->d_name, ".") == 0)
        return 1;
    if (strcmp((*e1)->d_name, "..") == 0)
        return -1;
    if (strcmp((*e2)->d_name, "..") == 0)
        return 1;
    int d1 = youxianji((*e1)->d_name);
    int d2 = youxianji((*e2)->d_name);
    if(d1!=d2){
        return flag_r ? (d1 - d2) : (d2 - d1);
    }
    int num = 0;
    switch(d1){
        case 3:
            num = atoi((*e1)->d_name) - atoi((*e2)->d_name);
            break;
        case 2:
            num = strcoll((*e1)->d_name, (*e2)->d_name);
            break;
        case 1:
            num = strcmp((*e1)->d_name, (*e2)->d_name);
            break;
        case 0:
            char* cmp1 = (*e1)->d_name;
            while (*cmp1 == '.')
                cmp1++;
            char* cmp2 = (*e2)->d_name;
            while (*cmp2 == '.')
                cmp2++;
            num = strcasecmp(cmp1, cmp2);
            break;
        default:
            num = strcmp((*e1)->d_name, (*e2)->d_name);
    }
    return flag_r ? -num : num;
}
int compare_time(const void* a, const void* b) {
    struct dirent** e1 = (struct dirent**)a;
    struct dirent** e2 = (struct dirent**)b;
    char path1[PATH_MAX];
    char path2[PATH_MAX];
    if (dir1[strlen(dir1) - 1] == '/') {
        snprintf(path1, PATH_MAX, "%s%s", dir1, (*e1)->d_name);
        snprintf(path2, PATH_MAX, "%s%s", dir1, (*e2)->d_name);
    } else {
        snprintf(path1, PATH_MAX, "%s/%s", dir1, (*e1)->d_name);
        snprintf(path2, PATH_MAX, "%s/%s", dir1, (*e2)->d_name);
    }
    struct stat st1;
    struct stat st2;
    if (lstat(path1, &st1) == -1 || lstat(path2, &st2) == -1) {
        return 0;
    }
    long num = st2.st_mtime - st1.st_mtime;
    return flag_r ? -num : num;
}
int filter(const struct dirent* entry) {
    return flag_a ? 1 : (entry->d_name[0] != '.');
}
void print_file(char* full_path, struct dirent* entry, struct stat* st) {
    if (flag_i) {
        printf("%8ld ", (long)st->st_ino);
    }
    if (flag_s) {
        printf("%5ld ", (long)(st->st_blocks * BLOCK_SIZE / 1024));
    }
    if (flag_l) {
        if (S_ISDIR(st->st_mode)) {
            printf("d");
        } else if (S_ISLNK(st->st_mode)) {
            printf("l");
        } else if (S_ISCHR(st->st_mode)) {
            printf("c");
        } else if (S_ISBLK(st->st_mode)) {
            printf("b");
        } else if (S_ISFIFO(st->st_mode)) {
            printf("p");
        } else if (S_ISSOCK(st->st_mode)) {
            printf("s");
        } else {
            printf("-");
        }
        printf((st->st_mode & S_IRUSR) ? "r" : "-");
        printf((st->st_mode & S_IWUSR) ? "w" : "-");
        if (st->st_mode & S_ISUID) {
            printf((st->st_mode & S_IXUSR) ? "s" : "S");
        } else {
            printf((st->st_mode & S_IXUSR) ? "x" : "-");
        }
        printf((st->st_mode & S_IRGRP) ? "r" : "-");
        printf((st->st_mode & S_IWGRP) ? "w" : "-");
        if (st->st_mode & S_ISGID) {
            printf((st->st_mode & S_IXGRP) ? "s" : "S");
        } else {
            printf((st->st_mode & S_IXGRP) ? "x" : "-");
        }
        printf((st->st_mode & S_IROTH) ? "r" : "-");
        printf((st->st_mode & S_IWOTH) ? "w" : "-");
        printf((st->st_mode & S_IXOTH) ? "x" : "-");
        printf("    %3ld    ", (long)st->st_nlink);
        struct passwd* pw = getpwuid(st->st_uid);
        printf("%-8s    ", pw->pw_name);
        struct group* gr = getgrgid(st->st_gid);
        printf("%8s ", gr->gr_name);
        printf("%8ld ", (long)st->st_size);
        struct tm* tm = localtime(&st->st_mtime);
        char time_str[32];
        strftime(time_str, sizeof(time_str), "%m月 %d %H:%M", tm);
        printf("%s ", time_str);
    }
    if (S_ISDIR(st->st_mode)) {
        printf(BLUE); 
    } else if (S_ISLNK(st->st_mode)) {
        printf(CYAN);  
    } else if (S_ISCHR(st->st_mode) || S_ISBLK(st->st_mode)) {
        printf(YELLOW); 
    } else if (S_ISFIFO(st->st_mode) || S_ISSOCK(st->st_mode)) {
        printf(MAGENTA); 
    } else {
        if ((st->st_mode & (S_ISUID | S_ISGID)) &&
            !(st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
            printf(RED);
        } else if (st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            printf(GREEN);
        }
    }
    if (flag_l && S_ISLNK(st->st_mode)) {
        char link_path[PATH_MAX];
        ssize_t len = readlink(full_path, link_path, PATH_MAX - 1);
        if (len != -1) {
            link_path[len] = '\0';
            printf("%s->%s\n", entry->d_name, link_path);
        } else {
            printf("%s\n", entry->d_name);
        }
    } else {
        printf("%s\n", entry->d_name);
    }
    printf(RESET);
}
void list_dir(char* dir) {
    if (flag_R) {
        printf("%s:\n", dir);
    }
    struct dirent** entries;
    dir1 = dir;
    int count = scandir(dir, &entries, filter, NULL);
    if (count == -1) {
        perror("scandir failed");
        return;
    }
    if (flag_t) {
        qsort(entries, count, sizeof(struct dirent*), compare_time);
    } else {
        qsort(entries, count, sizeof(struct dirent*), compare_name);
    }
    char** arrs = (char**)malloc(count * sizeof(char*));
    int arrs_count = 0;
    for (int i = 0; i < count; i++) {
        struct dirent* entry = entries[i];
        char full_path[PATH_MAX];
        if (dir[strlen(dir) - 1] == '/') {
            snprintf(full_path, PATH_MAX, "%s%s", dir, entry->d_name);
        } else {
            snprintf(full_path, PATH_MAX, "%s/%s", dir, entry->d_name);
        }
        struct stat st;
        if (lstat(full_path, &st) == 0) {
            print_file(full_path, entry, &st);
            if (flag_R && !S_ISLNK(st.st_mode) && S_ISDIR(st.st_mode) &&
                strcmp(entry->d_name, ".") != 0 &&
                strcmp(entry->d_name, "..") != 0) {
                char* path1 = strdup(full_path);
                if (path1 != NULL) {
                    arrs[arrs_count++] = path1;
                } else {
                    perror("strdup failed");
                }
            }
        } else {
            printf("%s\n", entry->d_name);
        }
        free(entries[i]);
    }
    free(entries);
    if (!flag_l) {
        printf("\n");
    }
    for (int i = 0; i < arrs_count; i++) {
        list_dir(arrs[i]);
        free(arrs[i]);
    }
    free(arrs);
}
int main(int argc, char* argv[]) {
    init_locale();
    int num;
    while ((num = getopt(argc, argv, "laRtris")) != -1) {
        switch (num) {
            case 'a':
                flag_a = 1;
                break;
            case 'l':
                flag_l = 1;
                break;
            case 'R':
                flag_R = 1;
                break;
            case 's':
                flag_s = 1;
                break;
            case 'i':
                flag_i = 1;
                break;
            case 't':
                flag_t = 1;
                break;
            case 'r':
                flag_r = 1;
                break;
            case '?':
                fprintf(stderr, "ls:参数无效：‘%c'\n", optopt);
        }
    }
    int dir_count = 0;
    char* dirs[PATH_MAX];
    for (int i = optind; i < argc; i++) {
        dirs[dir_count++] = argv[i];
    }
    if (dir_count == 0) {
        dirs[dir_count++] = ".";
    }
    for (int i = 0; i < dir_count; i++) {
        struct stat st;
        if (stat(dirs[i], &st) == -1) {
            perror(dirs[i]);
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            list_dir(dirs[i]);
        } else {
            struct dirent entry = {0};
            snprintf(entry.d_name, sizeof(entry.d_name) - 1, "%s", dirs[i]);
            entry.d_name[sizeof(entry.d_name) - 1] = '\0';
            print_file(dirs[i], &entry, &st);
            if (!flag_l) {
                printf("\n");
            }
        }
    }
    return 0;
}