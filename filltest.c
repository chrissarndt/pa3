#define XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kk.h"


long long genbig() {
	long long l;
	do {
		l = (long long) 
			(((uint64_t) rand()) & 0x000000000000FFFFull) | 
			(((uint64_t) rand() << 16) & 0x00000000FFFF0000ull) | 
			(((uint64_t) rand() << 32) & 0x0000FFFF00000000ull);
	} while (l > MAXNUM || l == 0);
	return l;
}

int main(void) {
	FILE* f = fopen("test.txt", "w");
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		fprintf(f, "%llu\n", genbig());
	}
}
