/*	function:	read from stdin and write to a file
				tee[options] args
	default:	trunc mode
	-a:			append mode*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/stat.h>

char options[256] = "a\0";

struct{
	int a;
	char* outputPath;
}teeConfig;

void getArgs(int argc, char* argv[]){
	int opt;

	teeConfig.a = 0;

	while((opt = getopt(argc, argv, options)) != -1){
		switch(opt){
			case 'a':
				printf("Append model.\n");
				teeConfig.a = 1;
				break;
			default:
				printf("Wrong args.\n");
				exit(0);
				break;
		}
	}

	if(argc < optind + 1){
		printf("Wrong args num\n");
		exit(0);
	}

	teeConfig.outputPath = argv[optind];
	printf("Output path: %s\n", teeConfig.outputPath);
}

int main(int argc, char* argv[]){
	int flag, fd;
	char buf;
	
	getArgs(argc, argv);
	
	if(teeConfig.a){
		flag = O_RDWR | O_CREAT | O_APPEND;
	}else{
		flag = O_RDWR | O_CREAT | O_TRUNC;
	}
	
	if((fd = open(teeConfig.outputPath, flag, S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
		printf("Can't open the file\n");
		exit(0);
	}
	
	while(read(STDIN_FILENO, &buf, 1) > 0){
		
		if(write(fd, &buf, 1) == -1){
			printf("Can't write to the file\n");
			exit(0);
		}
	}
	
	if(close(fd) == -1){
		printf("Can't close the file\n");
	}
}
