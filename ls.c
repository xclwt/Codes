#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>

void show_info(char* dir_name);
void show_status(char* dir_name, struct stat* statbuf);
void getstat(char* fullpath, char* filename);
void mode2letters(int mode, char str[]);
char* gid2name(gid_t gid);
char* uid2name(uid_t uid);

int main(int argc, char* argv[]){
	if(argc == 1){
		show_info(".");
	}else{
		while(--argc){
			printf("%s\n", *++argv);
			show_info(*argv);
		}
	}
}

void show_info(char* dir_name){
	printf("x");
	DIR* dir_ptr;
	struct dirent* direntp;
	char *fullpath = (char*)malloc(strlen(dir_name) + 1 + MAXNAMLEN + 1);
	if((dir_ptr = opendir(dir_name)) == NULL){
		fprintf(stderr, "ls:cannot open %s\n", dir_name);
	}else{
		while((direntp = readdir(dir_ptr)) != NULL){
			sprintf(fullpath, "%s/%s", dir_name, direntp->d_name);
			getstat(fullpath, direntp->d_name);
		}
		closedir(dir_ptr);
	}
}

void show_status(char* dir_name, struct stat* statbuf){
	char str[11];

	mode2letters(statbuf->st_mode, str);

	printf("%s", str);
	printf("%4d", statbuf->st_nlink);
	printf(" %s", uid2name(statbuf->st_uid));
	printf(" %s", gid2name(statbuf->st_gid));
	printf("%8ld", statbuf->st_size);
	printf(" %.12s", ctime(&statbuf->st_mtime) + 4);
	printf(" %s\n", dir_name);
}

void getstat(char* fullpath, char* filename){
	struct stat statbuf;
	
	if(stat(fullpath, &statbuf) == -1){
		perror(fullpath);
	}
	else{
		show_status(filename, &statbuf);
	}
}

void mode2letters(int mode, char str[]){
	strcpy(str, "----------");

	if(S_ISDIR(mode))	
		str[0] = 'd';
	else if(S_ISCHR(mode))
		str[0] = 'c';
	else if(S_ISBLK(mode))
		str[0] = 'b';
	
	if(mode & S_IRUSR)
		str[1] = 'r';
	if(mode & S_IWUSR)
		str[2] = 'w';
	if(mode & S_IXUSR)
		str[3] = 'x';
	if(mode & S_IRGRP)
		str[4] = 'r';
	if(mode & S_IWGRP)
		str[5] = 'w';
	if(mode & S_IXGRP)
		str[6] = 'x';
	if(mode & S_IROTH)
		str[7] = 'r';
	if(mode & S_IWOTH)
		str[8] = 'w';
	if(mode & S_IXOTH)
		str[9] = 'x';

}

char* uid2name(uid_t uid){
	struct passwd* pwd_ptr;
	char name[10];

	if((pwd_ptr = getpwuid(uid)) != NULL){
		return pwd_ptr->pw_name;
	}else{
		sprintf(name, "%d", uid);
		return name;
	}
}

char* gid2name(gid_t gid){
	struct group* grp_ptr;
	char name[10];

	if((grp_ptr = getgrgid(gid)) != NULL){
		return grp_ptr->gr_name;
	}else{
		sprintf(name, "%d", gid);
		return name;
	}
}
