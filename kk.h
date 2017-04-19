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

typedef struct mem {
	size_t numptrs;
	size_t sz;
	void** ptrs;
} mem;


/* * * * * * * * * * * * * *
 * * * * * * * * * * * * * *
 * * * GLOBAL VARIABLES  * *
 * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */
extern long long* prob;
extern mem ptr_data;


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
void insert(long long, heap*);
long long pull(heap*);
void insert_prob(long long*, heap*);
void printheap(heap*);

// Other functions
void* alloc_help(size_t);
void mem_clean(void);
int genrange(int);
long long genbig(void);
long long* genprob(void);
int* rand_sol(int);
int* gen_rand_neighbor(int*, int);
long long residue(int*, int);
long double t(int);
long long kk(heap*);
void printsol(int*);

#endif
