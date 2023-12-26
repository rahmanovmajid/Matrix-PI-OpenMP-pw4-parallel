#include <stdio.h>
#include <omp.h>
#include <float.h>

int main() {

    int i, nb_steps = 10000000;
    double pi,term;
    double sum = 0.0;
    double step = 1.0/(double) nb_steps;

    double t_ref, t_end;
    t_ref = omp_get_wtime();

    #pragma omp parallel private(i,term)
    {
        #pragma omp for reduction(+:sum) schedule(guided)
        for (i = 0; i < nb_steps; i++) {
            term = (i + 0.5) * step;
            sum += 4.0 / (1.0 + term * term);
        }
    }
    pi = step * sum;

    t_end = omp_get_wtime();

    int Digs = DECIMAL_DIG;
    printf("%.*e\n",Digs,pi);
    printf("Elapsed time: %lfs\n", (t_end-t_ref));
    return 0;
}

// Dynamic : 4- 0.29s , 2- 0.35s, 1- 0.31s
// Guided: 4- 0.06s, 2- 0.05s, 1- 0.09s