#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"
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
int compare_name(const void*a,const void*b){
    struct dirent** e1 = (struct dirent**)a;
    struct dirent** e2 = (struct dirent**)b;
    int num = strcmp((*e1)->d_name, (*e2)->d_name);
    return flag_r ? -num : num;
}
int compare_time(const void*a,const void*b){
    struct dirent** e1 = (struct dirent**)a;
    struct dirent** e2 = (struct dirent**)b;
    char path1[PATH_MAX];
    char path2[PATH_MAX];
    if(dir1[strlen(dir1)-1]=='/'){
        snprintf(path1, PATH_MAX, "%s%s", dir1, (*e1)->d_name);
        snprintf(path2, PATH_MAX, "%s%s", dir1, (*e2)->d_name);
    }else{
        snprintf(path1, PATH_MAX, "%s/%s", dir1, (*e1)->d_name);
        snprintf(path2, PATH_MAX, "%s/%s", dir1, (*e2)->d_name);
    }
    struct stat st1;
    struct stat st2;
    if(stat(path1,&st1)==-1||stat(path2,&st2)==-1){
        return 0;
    }
    long num = st2.st_mtime - st1.st_mtime;
    return flag_r ? -num : num;
}
int filter(const struct dirent*entry){
    return flag_a ? 1 : (entry->d_name[0] != '.');
}
void print_file(char*full_path,struct dirent*entry,struct stat*st){
    if(flag_i){
        printf("%8ld ", (long)st->st_ino);
    }
    if(flag_s){
        printf("%5ld ", (long)(st->st_blocks * BLOCK_SIZE / 1024));
    }
    if(flag_l){
        if (S_ISDIR(st->st_mode)){
            printf("d");
        }
            else if(S_ISLNK(st->st_mode)){
                printf("l");
            }
                else if(S_ISCHR(st->st_mode)){
                    printf("c");
                }
                    else if(S_ISBLK(st->st_mode)){
                        printf("b");
                    }
                        else if(S_ISFIFO(st->st_mode)){
                            printf("p");
                        }
                            else if(S_ISSOCK(st->st_mode)){
                                printf("s");
                            }
                            else{
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
                            strftime(time_str, sizeof(time_str), "%m月 %d %H:%M",
                                     tm);
                            printf("%s ", time_str);
    }
    if (S_ISDIR(st->st_mode)) {
        printf(BLUE);
    } else if (st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {  
        printf(GREEN);
    } else if (S_ISCHR(st->st_mode) || S_ISBLK(st->st_mode)) { 
        printf(YELLOW);
    } else if (S_ISLNK(st->st_mode)) { 
        printf(CYAN);
    } else if (S_ISFIFO(st->st_mode) || S_ISSOCK(st->st_mode)) {  
        printf(MAGENTA);
    }
    if(flag_l&&S_ISLNK(st->st_mode)){
        char link_path[PATH_MAX];
        ssize_t len = readlink(full_path, link_path, PATH_MAX - 1);
        if(len!=-1){
            link_path[len] = '\0';
            printf("%s->%s\n", entry->d_name, link_path);
        }else{
            printf("%s\n", entry->d_name);
        }
    }else{
        if(flag_l){
            printf("%s\n", entry->d_name);
        }else{
            printf("%s  ", entry->d_name);
        }
    }
    printf(RESET);
}
void list_dir(char*dir){
    if(flag_R){
        printf("%s:\n", dir);
    }
    struct dirent** entries;
    dir1 = dir;
    int count = scandir(dir, &entries, filter, NULL);
    if(count==-1){
        perror("scandir failed");
        return;
    }
    if(flag_t){
        qsort(entries, count, sizeof(struct dirent*), compare_time);
    }else{
        qsort(entries, count, sizeof(struct dirent*), compare_name);
    }
    char** arrs = malloc(count * sizeof(char*));
    int arrs_count = 0;
    for(int i=0;i<count;i++){
        struct dirent* entry = entries[i];
        char full_path[PATH_MAX];
        if (dir[strlen(dir) - 1] == '/') {
            snprintf(full_path, PATH_MAX, "%s%s", dir, entry->d_name);
        } else {
            snprintf(full_path, PATH_MAX, "%s/%s", dir, entry->d_name);
        }
        struct stat st;
        if(stat(full_path,&st)==0){
            print_file(full_path, entry, &st);
            if(flag_R&&S_ISDIR(st.st_mode)&&strcmp(entry->d_name,".")!=0&&strcmp(entry->d_name,"..")!=0){
                arrs[arrs_count] = strdup(full_path);
                arrs_count++;
            }
        }else{
            if(flag_l){
                printf("%s\n", entry->d_name);
            }else{
                printf("%s  ", entry->d_name);
            }
        }
        free(entries[i]);
    }
    free(entries);
    if(!flag_l){
        printf("\n");
    }
    for(int i=0;i<arrs_count;i++){
        list_dir(arrs[i]);
        free(arrs[i]);
    }
    free(arrs);
}
int main(int argc,char*argv[]){
    int num;
    while((num=getopt(argc,argv,"laRtris"))!=-1){
        switch(num){
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
                                        fprintf(stderr, "ls:无法访问‘%c'", optopt);
                                        exit(1);
        }
    }
    int dir_count = 0;
    char* dirs[PATH_MAX];
    for(int i=optind;i<argc;i++){
        dirs[dir_count++] = argv[i];
    }
    if(dir_count==0){
        dirs[dir_count++] = ".";
    }
    for(int i=0;i<dir_count;i++){
        struct stat st;
        if(stat(dirs[i],&st)==-1){
            perror(dirs[i]);
            continue;
        }
        if(S_ISDIR(st.st_mode)){
            list_dir(dirs[i]);
        }else{
            struct dirent entry;
            snprintf(entry.d_name, sizeof(entry.d_name), "%s", dirs[i]);
            print_file(dirs[i], &entry, &st);
            if(!flag_l){
                printf("\n");
            }
        }
    }
    return 0;
}