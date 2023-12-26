#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 590

int main() {

    double t_ref, t_end;
    t_ref = omp_get_wtime();

    double C[N][N], A[N][N], B[N][N];
    size_t i, j, k;

    #pragma omp parallel shared(C,B,A) private(i,j,k)
    {
        #pragma omp for schedule(dynamic)
        for (i = 0; i < N; i++ ) {
            for ( j = 0; j < N; j++ ) {
                C[i][j] = 0.;
                for ( k = 0; k < N; k++ ) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
    t_end = omp_get_wtime();
    printf("Elapsed time: %lf seconds.\n", (t_end-t_ref));
    return 0;
}

// 4 threads: normal - 1.076s, static - 0.731s,  dynamic - 0.766s;
// 3 threads: normal - 1.076s, static - 0.800s,  dynamic - 0.754s;
// 2 threads: normal - 1.076s, static - 0.899s,  dynamic - 0.884s;
// 1 thread:  normal - 1.076s, static - 1.427s,  dynamic - 1.457s;