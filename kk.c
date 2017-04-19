#define XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "kk.h"

// maximum number of iterations for heuristics
#define MAX_ITER 100
// number of elements in a single problem
#define PROBSIZE 100
// total number of problems
#define NUMPROBS 100
// maximum element in a single problem
#define MAXNUM 1000000000000

long long* prob;

/*
 *
 * CS124: PA3
 * Chris Arndt & Niamh Mulholland
 * Heuristic Approaches to NP-Complete Problems
 *
 * Usage: 
 *   ./kk [inputfile]
 *
 * If given an inputfile of the specified format, 
 *   the file will be parsed and the karmarkar karp
 *   algorithm will be run on the resulting sequence
 *   of numbers.  The residue will be printed to 
 *   STDOUT
 *
 * If not given an inputfile, 100 random sequences 
 *   of 100 numbers will be generated, and the specified
 *   algorithms will be run on each one.  The residues of
 *   these algorithms will be printed to the file 
 *   results.tsv
 * 
 */


int main(int argc, char* argv[]) {
	// error checking and rand() seed
	if (argc > 2) {
		printf("\n\n    Usage: ./kk [inputfile]\n");
	}
	srand(time(NULL));
	srand48(time(NULL));
	
	// if given inputfile, parse and run KK
	if (argc == 2) {
		// read file into string
		FILE* f = fopen(argv[1], "r");	
		fseek(f, 0, SEEK_END);
		int fsz = ftell(f);
		char* fstr = malloc(fsz);
		fseek(f, 0, SEEK_SET);
		fread(fstr, fsz, 1, f);

		// declare heap
		heap* hp = heap_init();

		// parse data
		char* buf = strtok(fstr, "\n");
		for (int i = 0; i < PROBSIZE; i++) {
			insert(atoll(buf), hp);
			buf = strtok(NULL, "\n");
		}

		// print result and exit
		long long res = kk(hp);
		heap_kill(hp);
		printf("%llu\n", res);
	}
	else {
		// open results file and declare variables
		FILE* w = fopen("results.tsv", "w");
		fprintf(w, "kk\trs\trp\ths\thp\tss\tsp\n");
		long long karmkarp, randstd, randpp, 
			 	hillstd, hillpp, simstd, simpp;



		// iterate through NUMPROBS problems and find solutions
		for (int i = 0; i < NUMPROBS; i++) {
			prob = genprob();
			heap* hp = heap_init();
			insert_prob(prob, hp);

			// run algorithms on problem
			karmkarp = kk(hp);
			printf("1\n");
			randstd = repeated_rand(rand_sol(1), 1);
			printf("2\n");
			randpp = repeated_rand(rand_sol(0), 0);
			printf("3\n");
			hillstd = hill_climb(rand_sol(1), 1);
			printf("4\n");
			hillpp = hill_climb(rand_sol(0), 0);
			printf("5\n");
			simstd = sim_anneal(rand_sol(1), 1);
			printf("6\n");
			simpp = sim_anneal(rand_sol(0), 0);
			printf("7\n");

			// clean up for next loop and print
			heap_kill(hp);
			free(prob);
			fprintf(w, "%llu\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu\n", 
				karmkarp, randstd, randpp, hillstd, hillpp, 
				simstd, simpp);
		}
	}
	return(0);
}





/* * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * *
 * * * * HEURISTICS  * * * * *
 * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * */

/*
 * repeated_rand(sol, mode) 
 *
 * continually generates random solutions 
 * and selects best, returns residue
 *
 */
long long repeated_rand(int* sol, int mode) {
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = rand_sol(mode);
		if(residue(new_sol, mode) < residue(sol, mode)){
			int* temp = sol;
			sol = new_sol;
			free(temp);
		}
		else {
			free(new_sol);
		}
	}
	return residue(sol, mode);
}


/* 
 * hill_climb(sol, mode)
 *
 * takes pointer to list
 * improves through moves to (better) neighbors
 * returns residue 
 *
 */

long long hill_climb(int* sol, int mode) {
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = gen_rand_neighbor(sol, mode);
		if(residue(new_sol, mode) < residue(sol, mode)){
			int* temp = sol;
			sol = new_sol;
			free(temp);
		}
		else {
			free(new_sol);
		}
	}
	return residue(sol, mode);
}

/* 
 * sim_anneal(sol, mode)
 *
 * takes pointer to list
 * improves through moves to (not always better) neighbors
 * returns residue 
 *
 */

long long sim_anneal(int* sol, int mode) {
	int* orig_sol = sol;
	for(int i = 0; i < MAX_ITER; i++){
		printf("fuck\n");
		int* new_sol = gen_rand_neighbor(sol, mode);
		printf("this\n");
		long double prob = exp(-(residue(new_sol, mode)-residue(sol, mode))/((long double) t(i)));
		printf("fucking\n");
		if(residue(new_sol, mode) < residue(sol, mode) || drand48() < prob){
			int* temp = sol;
			sol = new_sol;
			free(temp);
	    }
		else {
			free(new_sol);
		}
		printf("shit\n");
	    if(residue(sol, mode) < residue(orig_sol, mode)) {
	    	orig_sol = sol;
	    }
		printf("FUCK\n");
	}
	return residue(orig_sol, mode);
}





/* * * * * * * * * * * * * *
 * * * * * * * * * * * * * *
 * * * HEAP FUNCTIONS  * * * 
 * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

/* 
 * Iterator functions
 *
 * par(child) - returns index of child's parent
 * left(par) - returns index of parent's left child
 * right(par) - returns index of parent's right child
 *
 */

int par(int child) {
	if (child == 0) {
		return -1;
	}
	else if (child % 2 == 0) {
		return (child - 1) / 2;
	}
	else {
		return child / 2;
	}
}

int left(int par) {
	return 2*par + 1;
}

int right(int par) {
	return left(par) + 1;
}


/*
 * Heap manipulation functions
 *
 * heap_init() - initializes a heap 
 * heap_kill() - frees a heap
 * insert(elt, hp) - inserts element elt into heap hp
 * pull(hp) - pulls the minimum element of heap hp
 * insert_prob(prob, hp) - inserts entire problem prob into heap hp
 * printheap(hp) - prints heap (for testing purposes)
 * 
 */

heap* heap_init() {
	heap* hp = (heap*) calloc(1, sizeof(heap));
	hp->h = (long long*) calloc(100, sizeof(long long));
	hp->sz = 0;
	return hp;
}

/*
 * heap_kill(hp)
 *
 * frees allocated memory for heap hp
 *
 */
void heap_kill(heap* hp) {
	free(hp->h);
	free(hp);
}

/*
 * insert(elt, hp) 
 *
 * inserts element at bottom of heap 
 * and bubbles up through parents until 
 * max-heap condition is met
 *
 */
void insert(long long elt, heap* hp) {
	hp->sz++;
	hp->h[hp->sz - 1] = elt;
	int cur = hp->sz - 1;
	int next = par(cur);
	while (next >= 0 && hp->h[next] < elt) {
		hp->h[cur] = hp->h[next];
		cur = next;
		next = par(cur);
	}
	hp->h[cur] = elt;
}

/*
 * pull(hp)
 *
 * takes element on top of heap, 
 * replaces it with last element, and 
 * bubbles down until the max-heap 
 * condition is met
 *
 */
long long pull(heap* hp) {
	int maxelt = hp->h[0];
	int last = hp->h[hp->sz - 1];
	hp->h[hp->sz] = 0;
	hp->sz--;
	int swap, cur;
	for (cur = 0; left(cur) <= hp->sz; cur = swap) {
		// find larger child
		swap = left(cur);
		if (swap != hp->sz && hp->h[swap] < hp->h[right(cur)]) {
			swap = right(cur);
		}

		// perform requisite swaps
		if (last < hp->h[swap]) {
			hp->h[cur] = hp->h[swap];
		}
		else {
			break;
		}
	}
	hp->h[cur] = last;
	return maxelt;
}

/*
 * insert_prob(prob, hp)
 *
 * inserts each element in prob into a heap
 *
 */
void insert_prob(long long* prob, heap* hp) {
	for (int i = 0; i < PROBSIZE; i++) {
		insert(prob[i], hp);
	}
}

/*
 * printheap(hp)
 * 
 * prints heap hp
 *
 */
void printheap(heap* hp) {
	printf("[");
	int i;
	for (i = 0; i < hp->sz; i++) {
		printf("%llu,  ", hp->h[i]);
	}
	printf("]\n");
}





/* * * * * * * * * * * * *
 * * * * * * * * * * * * *
 * * * * * OTHER * * * * *
 * * * * * * * * * * * * *
 * * * * * * * * * * * * */

/*
 * genrange(n)
 *
 * generates a random integer in range [0, n(
 *
 */
int genrange(int n) {
	double ret;
	do {
		ret = drand48() * n;
	} while (ret == n);
	return (int) ret;
}


/* 
 * genbig()
 *
 * generates a random number in the 
 * range [1, 10^12]
 *
 */
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

/*
 * genprob()
 *
 * generates a number partition problem 
 * of PROBSIZE elements
 *
 */
long long* genprob() {
	long long* ret = (long long*) calloc(PROBSIZE, sizeof(long long));
	for (int i = 0; i < PROBSIZE; i++) {
		ret[i] = genbig();
	}
	return ret;
}


/*
 * rand_sol(mode)
 *
 * generates a random solution of 
 * standard form if mode is non-zero 
 * and pre-partitioned form otherwise
 *
 */
int* rand_sol(int mode) {
	int* sol = (int*) calloc(PROBSIZE, sizeof(int));
	for(int i = 0; i < PROBSIZE; i++) {
		// standard solution format
		if (mode) {
			sol[i] = (drand48() < .5) ? -1 : 1;
		}
		// prepartitioned solution format
		else {
			sol[i] = genrange(PROBSIZE);
		}
	}
	return sol;
}


/*
 * gen_random_neighbor(sol, mode)
 *
 * generates a random neighbor solution to solution sol
 * if mode is non-zero, uses standard format; else, uses 
 * pre-partitioned format
 *
 */
int* gen_rand_neighbor(int* sol, int mode) {
	// copy old solution
	int* newsol = (int*) calloc(PROBSIZE, sizeof(int));
	memcpy(newsol, sol, PROBSIZE * sizeof(int));

	// change copy to random neighbor using standard format
	if (mode) {
		if (drand48() < .5) {
			newsol[genrange(PROBSIZE)] *= -1;
		}
		else {
			int c1 = genrange(PROBSIZE);
			int c2;
			do {
				c2 = genrange(PROBSIZE);
			} while (c1 == c2);
			newsol[c1] *= -1;
			newsol[c2] *= -1;
		}
	}
	// change copy to random neighbor using pre-partitioned format
	else {
		int ind = genrange(PROBSIZE);
		int to;
		do {
			to = genrange(PROBSIZE);
		} while (newsol[ind] == to);
		newsol[ind] = to;
	}

	return newsol;
}

/*
 * residue(sol, mode)
 *
 * finds the residue of problem prob (global) with solution sol
 * interprets sol as standard solution form if mode is non-zero 
 * and pre-partitioned form otherwise
 *
 */
long long residue(int* sol, int mode) {
	// find residue of prob with standard solution
	if (mode) {
		long long ret = 0;
		for (int i = 0; i < PROBSIZE; i++) {
			ret += sol[i] * prob[i];
		}
		return llabs(ret);
	}
	// find residue of prob with pre-partitioned solution
	else {
		// find A'
		long long* aprime = (long long*) calloc(PROBSIZE, sizeof(long long));
		for (int i = 0; i < PROBSIZE; i++) {
			aprime[sol[i]] += prob[i];
		}

		// find residue
		heap* hp = heap_init();
		insert_prob(aprime, hp);
		long long ret = kk(hp);
		heap_kill(hp);
		return ret;
	}
}

/*
 * t(i)
 *
 * annealing function
 *
 */
long double t(int i) {
	return 10000000000 * pow(.8, floor(i / (double)300));
}

/*
 * kk(hp)
 *
 * runs karmarkar karp algorithm on heap hp and returns residue
 *
 */
long long kk(heap* hp) {
	long long a;
	long long b;
	do { 
		a = pull(hp);
		b = pull(hp);
		insert(0, hp);
		insert(llabs(a - b), hp);
	} while (b > 0);
	return a;
}

