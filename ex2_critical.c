#include <stdio.h>
#include <omp.h>
#include <float.h>

int main() {

    int i, nb_steps = 10000000;
    double pi,term;
    double sum = 0.0;
    double helper_sum = 0.0;
    double step = 1.0/(double) nb_steps;

    double t_ref, t_end;
    t_ref = omp_get_wtime();

    #pragma omp parallel private(i,term,helper_sum) shared(sum)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < nb_steps; i++) {
            term = (i + 0.5) * step;
            helper_sum = 4.0 / (1.0 + term * term);
        #pragma omp critical
            sum = sum + helper_sum;
        }
    }
    pi = step * sum;

    t_end = omp_get_wtime();

    int Digs = DECIMAL_DIG;
    printf("%.*e\n",Digs,pi);
    printf("Elapsed time: %lfs\n", (t_end-t_ref));
    return 0;
}

// Atomic : 4-0.633s , 2- 0.360s, 1- 1.506s
// Critical: 4-0.680s, 2- 0.682s, 1- 0.215s