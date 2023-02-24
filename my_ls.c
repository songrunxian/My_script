#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <time.h>
#include <stdint.h>
#include <grp.h>
#define MAX_N 1005 

void do_ls();
void do_ls1();

int main(int argc, char *argv[]) {
	if (argc == 1) {
		do_ls();
		return 0;
	} else if (argc == 2) {
		do_ls1();
		return 0;
	} else {
		char path[MAX_N];
		//dir[MAX_N] = *argv[2];
		//这样是不对的;这行代码试图将 argv[2] 的第一个字符存储到 dir 数组的最后一个位置上，这可能导致数组越界错误
		strcpy(path, argv[2]);
		DIR *dir = opendir(path);
		struct stat sb;
		char option[MAX_N];
		strcpy(option, argv[1]);
		if( !strcmp(option,"-a") ) {
			if(dir != NULL) {
				struct dirent *file;
				while( (file = readdir(dir)) != NULL ) {
					printf("%s	", file->d_name);
				}
				printf("\n");
			}
		}
		if( !strcmp(option,"-l") ) {
			if (dir!=NULL) {
				struct dirent *file ;
				while((file = readdir(dir)) != NULL){
					stat(file->d_name, &sb);
					if (S_ISREG(sb.st_mode)){
						printf("-");
					} else if (S_ISDIR(sb.st_mode)){
						printf("d");
					} else if (S_ISBLK(sb.st_mode)){
						printf("b");
					} else if (S_ISCHR(sb.st_mode)){
						printf("c");
					} else if (S_ISSOCK(sb.st_mode)){
						printf("s");
					} else {
						printf("l");
					}
					printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    					printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    					printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    					printf((sb.st_mode & S_IRGRP) ? "r" : "-");
	    				printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    					printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    					printf((sb.st_mode & S_IROTH) ? "r" : "-");
    					printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    					printf((sb.st_mode & S_IXOTH) ? "x" : "-");
					int uid, gid;
					uid = sb.st_uid;
					gid = sb.st_gid;
					struct passwd *pd = getpwuid(uid);
					struct group *g = getgrgid(gid);
					printf("\t%s\t%s", pd->pw_name, g->gr_name);
					int size = sb.st_size;
					printf("\t%d", size);
					time_t T = sb.st_atim.tv_sec;
					struct tm *t = localtime(&T);
					if(t->tm_mon+1 == 1) {
						printf("\tJan");
					} else if(t->tm_mon+1 == 2) {
						printf("\tFeb");
					} else if(t->tm_mon+1 == 3) {
						printf("\tMar");
					} else if(t->tm_mon+1 == 4) {
						printf("\tApr");
					} else if(t->tm_mon+1 == 5) {
						printf("\tMay");
					} else if(t->tm_mon+1 == 6) {
						printf("\tJun");
					} else if(t->tm_mon+1 == 7) {
						printf("\tJul");
					} else if(t->tm_mon+1 == 8) {
						printf("\tAug");
					} else if(t->tm_mon+1 == 9) {
						printf("\tSep");
					} else if(t->tm_mon+1 == 10) {
						printf("\tOct");
					} else if(t->tm_mon+1 == 11) {
						printf("\tNov");
					} else {
						printf("\tDec");
					}
					printf(" %02d %02d:%02d", t->tm_mday, t->tm_hour, t->tm_min);
					printf("\t%s\n", file->d_name);
				}
			}
		}
		closedir(dir);
	}
	return 0;
}

void do_ls() {
	printf("you don't put in parameters, please write such as ls -a ; ls -al\n");
}
void do_ls1() {
	printf("you don't have put in path\n");
}
