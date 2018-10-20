all: yuuutsu shousitsu

yuuutsu: yuuutsu.c
	gcc yuuutsu.c -o yuuutsu

shousitsu: shousitsu.c
	gcc shousitsu.c -o shousitsu

clean: shousitsu yuuutsu
	rm -f shousitsu yuuutsu