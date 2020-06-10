#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>

#define NRECS   16
#define NULLUT  (struct utmp*)NULL
#define UTSIZE  sizeof(struct utmp)

static char utmpbuf[NRECS * UTSIZE];
static int num_rcvs;
static int cur_rcv;
static int utmpfd = -1;

void output(struct utmp* utmp_struct);
int utmp_open(char* filename);
struct utmp* utmp_next();
int utmp_reload();
int utmp_close();

int main(){
	struct utmp* cur_record;

	if((utmpfd = utmp_open(UTMP_FILE)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while((cur_record = utmp_next()) != NULLUT){
		output(cur_record);
	}
	utmp_close();
	
	return 0;
}
 
void output(struct utmp* utmp_struct){
	if(utmp_struct->ut_type != USER_PROCESS){
		return;
	}
	
	long time = (long)utmp_struct->ut_time;

	printf("%-8.8s", utmp_struct->ut_name);
	printf(" ");
	printf("%-8.8s", utmp_struct->ut_line);
	printf(" ");
	printf("%12.12s  ", (ctime(&time) + 4));
	printf(" ");
	printf("(%s)\n", utmp_struct->ut_host);
}

int utmp_open(char* filename){
    utmpfd = open(filename, O_RDONLY);
    num_rcvs = cur_rcv = 0;
    
    return utmpfd;
}

struct utmp* utmp_next(){
    if(utmpfd == -1){
        return NULLUT;
    }
    
    if(num_rcvs == cur_rcv){
        if(utmp_reload() == 0){
            return NULLUT;
        }
    }
    
    return (struct utmp*)&utmpbuf[(cur_rcv++) * UTSIZE];
}

int utmp_reload(){
    int num_read = read(utmpfd, utmpbuf, NRECS * UTSIZE);
    
    num_rcvs = num_read / UTSIZE;
    cur_rcv = 0;
    
    return num_rcvs;
}

int utmp_close(){
    if(utmpfd != -1){
        return close(utmpfd);
    }
}
