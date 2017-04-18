#ifndef KK_H
#define KK_H



/* * * * * * * * * * * * * *
 * * * * * * * * * * * * * *
 * * * TYPE DEFINITIONS  * *
 * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

typedef struct heap {
	int sz;
	long long* h;
} heap;


/* * * * * * * * * * * * * *
 * * * * * * * * * * * * * *
 * * * * PROTOTYPES  * * * * 
 * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

// Heuristics
long long repeated_rand(int*, int);
long long hill_climb(int*, int);
long long sim_anneal(int*, int);

// Heap function prototypes
int par(int);
int left(int);
int right(int);
heap* heap_init(void);
void heap_kill(heap*);
void insert(long long, heap*);
long long pull(heap*);
void insert_prob(long long*, heap*);
void printheap(heap*);

// Other functions
int genrange(int);
long long genbig(void);
long long* genprob(void);
int* rand_sol(int);
int* gen_rand_neighbor(int*, int);
long long residue(int*, int);
long double t(int);
long long kk(heap*);

#endif
