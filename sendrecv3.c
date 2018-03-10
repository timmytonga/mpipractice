#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[]){
    int ierr, procid, numprocs;
    printf(">>argc is %d\n",argc);
    for (int i = 0; i < argc; i++)
        printf(">>argv[%d]: %s\n", i, argv[i]);
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // All procids send the value -procid to process 0...
    double val = -1.0* procid;
    MPI_Send(&val, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    printf("ProcID %d sent value %lf to ProcID 0.\n", procid, val);

    if (procid == 0){
        int i; double val; double sum = 0; MPI_Status status;

        for ( i = 0; i != numprocs; ++i){
            ierr = MPI_Recv(&val, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (ierr == MPI_SUCCESS){
                printf("ProcID %d received value %lf.\n", procid, val);
                sum += val;
            }
            else MPI_Abort(MPI_COMM_WORLD, 1);
        }
        printf("The total is %lf.\n", sum);
    }
    ierr = MPI_Finalize();

}
