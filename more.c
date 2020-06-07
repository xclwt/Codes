/*仍需完善的地方：
  1.百分比显示，受限于c库，为了效率着想，需要自己实现一个读取字符串并返回读取长度的函数，文件总大小函数filesize()已实现。
  2.键盘输入即触发相应动作，非必须，未考虑。

  注意：编译时需加上参数“-lncurses”
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <term.h>
#include <curses.h>

#define LINELEN 512

int row_num;

void do_more(FILE* fp);

int see_more(FILE* tty);

void update_col();

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

	update_col();
    
	while(fgets(line, LINELEN, fp)){
		if(lines_num == row_num){
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
        update_col();
	}
}

int see_more(FILE* tty){
	int ch;
	
    /*如果直接使用system("stty -icanon")以使得命令直接处理，
     会导致两个后果：1.在使用管道重定向到stdin时失效
     2.在使用空格翻页使丢失部分字符
     如需修改，请理清代码逻辑*/
	printf("\033[7m more? \033[0m");
	while((ch = getc(tty)) != EOF){
		if(ch == 'q')
			return 0;
		if(ch == ' ')
			return row_num;
		if(ch == '\n')
			return 1;
	}

	return 0;
}

void update_col(){
    setupterm(NULL, fileno(stdout), (int *)0);
    row_num = tigetnum("lines") - 1;
}

int file_size(char* filename){
	struct stat statbuf;

	stat(filename, &statbuf);
	
	return statbuf.st_size;
}
