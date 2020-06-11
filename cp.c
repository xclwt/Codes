#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE     4096
#define COPYMODE    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

void oops(char* s1, char* s2);

int main(int count, char* argv[]){
	int source_fd, target_fd, n_chars;
	char buf[BUFSIZE];

	if(count != 3){
		fprintf(stderr, "usage: %s source destination\n", argv);
		exit(1);
	}

	if(strcmp(argv[1], argv[2]) == 0){
		fprintf(stderr, "Error: source can't be the same as destination\n");
		exit(1);
	}

	if((source_fd = open(argv[1], O_RDONLY)) == -1)
		oops("Can't open ", argv[1]);
	
	if((target_fd = open(argv[2], O_WRONLY)) != -1){
		printf("This action will overwrite the destination file, Do you want to continue (y/n) ? ");
		char tmp = getchar();
		if(tmp != 'y'){
			exit(1);
		}
	}else if((target_fd = creat(argv[2], COPYMODE)) == -1){
			oops("Can't creat ", argv[2]);
	}

	while((n_chars = read(source_fd, buf, BUFSIZE)) > 0){
		if(write(target_fd, buf, n_chars) != n_chars){
			oops("Write error to ", argv[2]);
		}
	}

	if(n_chars == -1)
		oops("Read error from ", argv[1]);

	if(close(source_fd) == -1 || close(target_fd) == -1)
		oops("Error closing files", "");
}

void oops(char* s1, char* s2){
	fprintf(stderr, "Error: %s", s1);
	perror(s2);
	exit(1);
}
