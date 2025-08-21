#ifndef DE
#define DE

typedef struct{
  int n_dim;
  int pop_size;
  int max_gen;
  double f; // mutation rate
  double cr; // crossover rate
} DE_config;

typedef double* Solution;

typedef double (*FitnessFunction)(Individual);

typedef double (*InitFunction)(Individual);

double run(DE_config cfg, FitnessFunction fit_fn, InitFunction init_fn, Individual best_ind);

#endif
