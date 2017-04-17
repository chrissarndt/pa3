/*
*
* CS124: PA3
* Chris Arndt & Niamh Mulholland
* */

#define MAX_ITER 100

int num[10] = {2,8,7,6,0,2,8,7,6,0};
int* sol;

sol = num;

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

int* repeated_rand(int* sol) {
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = rand_sol();
		if(residue(new_sol) < residue(sol)){
			sol = new_sol;
		}
	}
return sol;
}


/* hill climbing
* takes pointer to list
* improves through moves to (better) neighbours
* returns residue 
*/

int* hill_climb(int* sol) {
	for(int i = 0; i < MAX_ITER; i++){
		int* new_sol = gen_rand_neighbour(sol);
		if(residue(new_sol) < residue(sol)){
			sol = new_sol;
		}		
	}
return sol;
}

/* simulated annealing 
* takes pointer to list
* improves through moves to (not always better) neighbours
* returns residue 
*/

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
}

