#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

#define PROMPT "YUKI.N>"
#define INDENT "       "
#define ESC 0x1B
//const char* ESC="\033";

struct _message{
	char* serif;
	char* prompt;			/* セリフ前のプロンプト部分の文字 */
	char writer;					/* Y:長門有希 K:キョン*/
	unsigned int wait;			/* 待機時間(s) */
} messages[] = {
	{"これをあなたが読んでいる時、", PROMPT, 'Y', 80000},
	{"わたしはわたしではないだろう。\n", INDENT, 'Y',1000000},

	{"このメッセージが表示されたということは、",PROMPT,'Y',80000},
	{"そこにはあなた、わたし、涼宮ハルヒ、朝比奈みくる、",INDENT, 'Y',80000},
	{"小泉一樹が存在しているはずである。\n", INDENT, 'Y',150000},

	{"それが鍵。", PROMPT, 'Y',1000000},
	{"あなたは解答を見つけ出した。\n", INDENT, 'Y', 1000000},

	{"これは緊急脱出プログラムである。\n", PROMPT, 'Y', 1000000},
	{"起動させる場合はエンターキーを、", INDENT, 'Y',80000},
	{"そうでない場合はそれ以外のキーを選択せよ。\n", INDENT, 'Y',1000000},
	{"起動させた場合、", INDENT, 'Y', 80000},
	{"あなたは時空修正の機会を得る。", INDENT, 'Y', 100000},
	{"ただし成功は保証できない。", INDENT, 'Y', 100000},
	{"また帰還の保証もできない。\n", INDENT, 'Y', 100000},

	{"このプログラムが起動するのは一度きりである。", PROMPT, 'Y', 100000},
	{"実行ののち、消去される。\n", INDENT, 'Y', 100000},
	{"非実行が選択された場合は起動せずに消去される。\n", INDENT, 'Y', 3000000},
	{"Ｒｅａｄｙ？", "", 'K', 1000000},
	{"", "", 'K', 1}
};

void init(void);
void print_message(struct _message);

int main(void){
	int i=0;

	init();
	sleep(2);
	while(messages[i].serif[0]!='\0'){
		print_message(messages[i]);
		i++;
	}

	if(getchar()=='\n'){
		return system("poweroff");
	}
	return(0);
}

void init(){
	setlocale(LC_CTYPE, "ja_JP.UTF-8");

	printf("%c[2J",ESC);			/* CLS */
	printf("%c[0;0H",ESC);
	fflush(stdout);
}

void print_message(struct _message msg){
	int i = 0;
	unsigned int typespeed = (msg.writer=='Y')? 80000 : 300000;

	while(msg.prompt[i]!='\0'){
		int len = mblen(&msg.prompt[i], MB_CUR_MAX);
		char mchar[MB_CUR_MAX+1];
		memset(mchar, '\0', MB_CUR_MAX);
		strncpy(mchar, &msg.prompt[i], len);
		i+=len;
		printf("%s", mchar);
		fflush(stdout);
		usleep((strcmp(msg.prompt,PROMPT)==0)? 80000 : 1);
	}
	usleep(300000);
	i=0;
	while(msg.serif[i]!='\0'){
		int len = mblen(&msg.serif[i], MB_CUR_MAX);
		char mchar[MB_CUR_MAX+1];
		memset(mchar, '\0', MB_CUR_MAX);
		strncpy(mchar, &msg.serif[i], len);
		i+=len;
		printf("%s", mchar);
		fflush(stdout);
		usleep(typespeed);
	}
	usleep(msg.wait);
	puts("");
}
