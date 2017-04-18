/*
*
* CS124: PA3
* Chris Arndt & Niamh Mulholland
* */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

#define MAX_ITER 100

/* 
 * Standard representation functions
 *
 *  standard_rep - generates random sequence of -1,1 
 *  neighbours - moves from solution S to a neighbour
 * 				 by moving 1 or 2 elements from set A1 
 *				 to A2 and vice versa, or swapping elements
 *				 from two sets,
 */

int* standard_rep(int n) {
	int* sol = malloc(sizeof(int)*n);
	for(int i=0; i<n; i++){
		double num = (drand48()*2 - 1);
		int numf = num/(fabs(num));
		sol[i] = numf;
	}
return sol;
}


int* neighbours(int sol[], int n) {
	int prob_swap = drand48();

	if(prob_swap < 0.5) {
		int i1 = rand()%(n-1);
		int i2 = rand()%(n-1);
		int temp = sol[i1];
		sol[i1] = sol[i2];
		sol[i2] = temp;
	}
	else {
		int prob_elt = drand48();
		//  (100/(100 choose 2))
		int prob_set = 2/99;

		if(prob_elt < prob_set){
			int i = (rand()%(n-1));
			sol[i] = sol[i]*(-1);
		}
		else {
			int i1 = rand()%(n-1);
			int i2 = rand()%(n-1);
			sol[i1] = sol[i1]*(-1);
			sol[i2] = sol[i2]*(-1);
		}
	}
return sol;
}

/* repeated random
* takes pointer to list
* repeatedly generates random solutions
* returns residue 
*/

/*TODO:
*IMPLEMENT RAND_SOL
*IMPLEMENT RESIDUE
* IMPLEMENT GEN_RAND_NEIGHBOUR
* IMPLEMENT T()
*/

/*
int* repeated_rand(int* sol) {
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = rand_sol();
		if(residue(new_sol) < residue(sol)){
			sol = new_sol;
		}
	}
return sol;
}


* hill climbing
* takes pointer to list
* improves through moves to (better) neighbours
* returns residue 
*

int* hill_climb(int* sol) {
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = gen_rand_neighbour(sol);
		if(residue(new_sol) < residue(sol)){
			sol = new_sol;
		}		
	}
return sol;
}

* simulated annealing 
* takes pointer to list
* improves through moves to (not always better) neighbours
* returns residue 
*

int* sim_anneal(int* sol) {
	int* orig_sol = sol;
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = sol;
		int prob = -(residue(new_sol)-residue(sol))/T(i);
		if(residue(new_sol) < residue(sol)){
			sol = new_sol;
	     }
	     else if(prob > num){ //need to fix this line
	     	if(residue(new_sol) < residue(orig_sol)) {
	     		orig_sol = sol;
	     	}
	     }
return orig_sol;
}*/ 

int main() { 
	time_t t;
	// initialise RNG
	srand48(time(&t));
	int* sol = standard_rep(10);
	neighbours(sol, 10);
	free(sol);


}	
