#define XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) {
	FILE* f = fopen("test.txt", "w");
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		fprintf(f, "%d\n", rand());
	}
}
