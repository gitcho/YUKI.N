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
	{"みえてる？", PROMPT, 'Y', 2000000},
	{"ああ", "", 'K',1000000},
	{"そっちの時空間とは",PROMPT,'Y',100000},
	{"まだ完全には連結を絶たれていない。",INDENT, 'Y',100000},
	{"でも時間の問題。", INDENT, 'Y',150000},
	{"そうなれば最後。", INDENT, 'Y',3000000},
	{"どうすりゃいい？", "", 'K', 1000000},
	{"どうにもならない。", PROMPT, 'Y', 1000000},
	{"情報統合思念体は失望している。", INDENT, 'Y',1000000},
	{"これで進化の可能性は失われた。", INDENT, 'Y',1000000},
	{"涼宮ハルヒは", PROMPT, 'Y', 100000},
	{"何もない所から", INDENT, 'Y', 100000},
	{"情報を生み出す力を", INDENT, 'Y', 100000},
	{"持っていた。", INDENT, 'Y', 100000},
	{"それは情報統合思念体にも", INDENT, 'Y', 100000},
	{"ない力。", INDENT, 'Y', 150000},
	{"この情報創造能力を解析すれば", INDENT, 'Y', 100000},
	{"自律進化への糸口が", INDENT, 'Y', 100000},
	{"つかめるかもしれないと考えた。", INDENT, 'Y', 3000000},
	{"あなたに賭ける。", PROMPT, 'Y', 1000000},
	{"何をだよ", "", 'K', 1000000},
	{"もう一度こちらへ回帰することを", PROMPT, 'Y', 100000},
	{"我々は望んでいる。", INDENT, 'Y', 150000},
	{"涼宮ハルヒは重要な観察対象。", INDENT, 'Y', 1000000},
	{"わたしという個体も", INDENT, 'Y', 100000},
	{"あなたには戻ってきて欲しいと感じている。", INDENT, 'Y', 1000000},
	{"", "", 'K', 1},
	{"また図書館に", PROMPT, 'Y', 1000000},
	{"sleeping beauty", PROMPT, 'Y', 1},
	{"", "", 'K', 1}
};

void init(void);
void print_message(struct _message, int);

int main(void){
	int i=0;

	init();
	sleep(3);
	while(messages[i].serif[0]!='\0'){
		print_message(messages[i], 0);
		i++;
	}
	init();
	print_message(messages[i+1], 1);
	init();
	sleep(1);
	print_message(messages[i+2], 0);
	sleep(3);
	init();
	return system("poweroff");
}

void init(){
	setlocale(LC_CTYPE, "ja_JP.UTF-8");

	printf("%c[2J",ESC);			/* CLS */
	printf("%c[0;0H",ESC);
	fflush(stdout);
}

void print_message(struct _message msg, int slowFlag){
	int i = 0;
	unsigned int typespeed = (msg.writer=='Y' && !slowFlag)? 80000 : 300000;

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
