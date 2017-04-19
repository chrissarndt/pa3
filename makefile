all: kk filltest

kk: kk.c
	gcc -std=c99 -o kk kk.c -lm -I.

filltest: filltest.c
	gcc -std=c99 -o filltest filltest.c -lm

clean:
	rm -rf kk filltest *.txt
