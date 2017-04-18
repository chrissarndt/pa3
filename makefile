all: kk

kk: kk.c
	gcc -std=c99 -o kk kk.c -lm -I.

clean:
	rm -rf kk
