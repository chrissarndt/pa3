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
long long repeated_rand(long long*, int);
long long hill_climb(long long*, int);
long long sim_anneal(long long*, int);

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
long long genbig(void);
long long* genprob(void);
long long* rand_sol(int);
long long* gen_rand_neighbor(long long*, int);
long long residue(long long*, int);
double t(int);
long long kk(heap*);

#endif
