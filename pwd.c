#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 256

void print_path(ino_t cur_inode);
ino_t get_inode(char* pathname);

int main(){
	ino_t cur_inode = get_inode(".");
	
	if(get_inode("..") == cur_inode){
		printf("/");
	}else{
		print_path(get_inode("."));
	}
	printf("\n");

	return 0;
}

ino_t get_inode(char* pathname){
	struct stat stat_buf;

	if(stat(pathname, &stat_buf) == -1){
		fprintf(stderr, "Can't stat ");
		perror(pathname);
		exit(1);
	}

	return stat_buf.st_ino;
}

void inode2name(ino_t inode, char name[], int size){
	DIR* dir_ptr;
	struct dirent* direntp;

	if((dir_ptr = opendir(".")) == NULL){
		perror(".");
		exit(1);
	}

	while((direntp = readdir(dir_ptr)) != NULL){
		if(direntp->d_ino == inode){
			strncpy(name, direntp->d_name, size);
			name[size - 1] = '\0';
			closedir(dir_ptr);
			return;
		}
	}

	fprintf(stderr, "error looking for inode %d\n", inode);
	exit(1);
}

void print_path(ino_t cur_inode){
	char name[BUFSIZ];
	
	if(get_inode("..") != cur_inode){
		chdir("..");
		inode2name(cur_inode, name, BUFSIZ);
		print_path(get_inode("."));
		printf("/%s", name);
	}
}
