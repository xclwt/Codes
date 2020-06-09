#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>

void output(struct utmp* utmp_struct);

int main(){
	struct utmp cur_record;
	int record_len = sizeof(cur_record), utmpfd;

	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd, &cur_record, record_len)){
		output(&cur_record);
	}
	close(utmpfd);
	
	return 0;
}

void output(struct utmp* utmp_struct){
	printf("%-8.8s", utmp_struct->ut_name);
	printf(" ");
	printf("%-8.8s", utmp_struct->ut_line);
	printf(" ");
	printf("%10ld", utmp_struct->ut_time);
	printf(" ");
	printf("(%s)\n", utmp_struct->ut_host);
}
