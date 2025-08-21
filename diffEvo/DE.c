#include "../alea.c"
#include "DE.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double eval_fit(Individual ind, FitnessFunction fit_fn){
  return fit_fn(ind);
}

double run(DE_config cfg, FitnessFunction fit_fn, InitFunction init_fn, Individual best_ind){
  Individual* pop = (Individual*)malloc(cfg.pop_size * sizeof(Individual));
  Individual* new_pop = (Individual*)malloc(cfg.pop_size * sizeof(Individual));

  double* fitness = (double*)malloc(cfp.pop_size, * sizeof(double));
  double* new_fitness = (double*)malloc(cfp.pop_size, * sizeof(double));

  //INITIALISING SOLUTIONS
  //============================================================================================

  printf("Creating Solutions ...\n");

  for(int i = 0 ; i < cfg.pop_size; i++){
    pop[i] = (Individual)malloc(sizeof(Individual)):
    new_pop[i] = (Individual)malloc(sizeof(Individual)):
  }

  printf("Initialising Solutions ...\n");

  for(int i = 0; i < cfg.pop_size; i++){
    init_fn(pop[i]);
    fitness[i] = eval_fit(pop[i], fit_fn);
  }

  printf("Initialisation done.\n");

  double best_global_fit = DBL_MAX;

  //MAIN LOOP
  //============================================================================================

  print("Starting main loop ...\n");

  for(int gen = 0; gen < cfg.max_gen; gen++){

    print("\tGeneration %d : \n", gen);

    for(int i = 0 ; i < cfg.pop_size; i++){

      //MUTATATION
      //============================================================================================

      print("\t\tPerforming mutation ... \n");
      int a, b, c;
      do{a = alea_integer(0, cfg.pop_size - 1)}while(a == i);
      do{b = alea_integer(0, cfg.pop_size - 1)}while(b == i || b == a);
      do{c = alea_integer(0, cfg.pop_size - 1)}while(c == i || c == b || c == a);

      print("\t\t\tConcerned solns: %d = mutate(%d %d %d)", i, a, b, c);

      Individual mutant = new_pop[i];

      for(int j = 0; j < cfg.n_dim; j++)
        mutant[j] = pop[a][j] + cfg.f * (pop[b][j] - pop[c][j]);

      //CROSSOVER
      //============================================================================================
      
      print("\t\tPerforming crossover ...\n");

      Individual trial = new_pop[i];
      int pakka_idx = alea_integer(0, cfg.n_dim - 1);

      for(int j = 0; j < cfg.n_dim; j++){
        if(alea(0, 1) > cfg.cr && j == pakka_idx)
          trial[j] = pop[i][j];
        else
          print("\t\t\tCrossover at %d\n", j);
      }

      print("\t\tSelecting ...\n");

      //SELECTION
      //============================================================================================

      new_fitness[i] = eval_fit(new_pop[i], fit_fn);

      if(new_fitness[i] > fitness[i]){
        fitness[i] = new_fitness[i];
      }
      else{
        for(int j = 0; j < cfg.n_dim; j++){
          new_pop[i][j] = pop[i][j];
        }
      }

    }
    
    //REPLACE POPULATION
    //============================================================================================
    for(int i = 0 ; i < cfg.max_pop; i++){
      for(int  j = 0 ; j < cfg.n_dim; j++)
        pop[i][j] = new_pop[i][j];
      fitness[i] = new_fitness[i];
    }

    int best_idx = 0;
    for(int i = 1; i < cfg.max_pop; i++)
      best_idx = (fitness[i] < fitness[best_idx])?i:best_idx;
    
    if (fitness[best_idx] < best_global_fit) {
      best_global_fit = fitness[best_idx];
      for (int j = 0; j < cfg.n_dim ; j++)
        best_ind[j] = pop[best_idx][j];
    }

    if (gen % 10 == 0) 
      printf("Generation %d: Best Fitness = %lf\n", gen, best_global_fitness);
    
    for(int i = 0 ; i < cfg.max_pop; i++){
      free(pop[i]);
      free(new_pop[i]);
    }
    free(pop);
    free(new_pop);
    free(fitness);
    free(new_fitness);

    return best_global_fit;

  }

}
