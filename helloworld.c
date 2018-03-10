#include <mpi.h>
#include <stdio.h>

int main(int argc, char * argv[]){
    int ierr, procid, numprocs;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    printf("Hello world! I am process %d out of %d!\n", procid, numprocs);
    ierr = MPI_Finalize();

}
