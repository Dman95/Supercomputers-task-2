#include "../lib/matrix_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

//generate square matrix and vector by size
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int size;
    char vectorname[100];
    char matrixname[100];
    sprintf(vectorname, "../data/v%s", argv[1]);
    sprintf(matrixname, "../data/m%s", argv[1]);
    sscanf(argv[1], "%d", &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double start = -MPI_Wtime();

    if (!rank) {
        //generate vector
        vector *v = vector_gen(size);
        vector_save(v, vectorname);
        vector_delete(v);
    }

    //generate matrix
    mpi_matrix_gen_and_save(size, size, matrixname);
    
    if (!rank) {    
        printf("Time: %lld\n", start + MPI_Wtime());
    }

    MPI_Finalize();
    return 0;
}
