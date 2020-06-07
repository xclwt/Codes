/*仍需完善的地方：
  1.百分比显示，受限于c库，为了效率着想，需要自己实现一个读取字符串并返回读取长度的函数，文件总大小函数filesize()已实现。
  2.终端适配，暂无思路。
  3.键盘输入即触发相应动作，非必须，未考虑。
*/

#include <stdio.h>
#include <sys/stat.h>

#define LINELEN 512
#define PAGELEN 24

void do_more(FILE* fp);

int see_more(FILE* tty);

int main(int count, char* argv[]){
	FILE* fp;
	int filesize;

	if(count == 1){
		do_more(stdin);
	}else{
		while(count--){
			if((fp = fopen(*(++argv), "r")) != NULL){	
				do_more(fp);
				if(fclose(fp) == EOF){
					exit(1);
				}
			}else{
				exit(1);
			}
		}
	}

	return 0;
}

void do_more(FILE* fp){
	char line[LINELEN];
	int lines_num = 0, reply;
	FILE* tty = fopen("/dev/tty", "r");

	if(!tty){
		exit(1);
	}

	while(fgets(line, LINELEN, fp)){
		if(lines_num == PAGELEN){
			reply = see_more(tty);
			printf("\033[1A           \033[0m\r");	//消除反显提示“more？”
			if(reply == 0)
				break;
			lines_num -= reply;
		}
		if(fputs(line, stdout) == EOF){
			exit(1);
		}
		++lines_num;
	}
}

int see_more(FILE* tty){
	int ch;
	
	printf("\033[7m more? \033[0m");
	while((ch = getc(tty)) != EOF){
		if(ch == 'q')
			return 0;
		if(ch == ' ')
			return PAGELEN;
		if(ch == '\n')
			return 1;
	}

	return 0;
}

int file_size(char* filename){
	struct stat statbuf;

	stat(filename, &statbuf);
	
	return statbuf.st_size;
}
