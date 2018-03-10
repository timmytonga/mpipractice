#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int ierr, procid, numprocs;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (numprocs % 2!= 0 ){
        fprintf(stderr, "ERROR: Number of processes is not even!\n");
        return MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (procid % 2 == 0){
        // procid 0 will send 3.14 to procid1
        double pi = 3.14+procid;
        MPI_Send(&pi, 1, MPI_DOUBLE, procid + 1, 0, MPI_COMM_WORLD);
        printf("ProcID %d sent value %lf to ProcID %d.\n", procid, pi, procid + 1);
    }
    else{
        // procid 1 will wait to receive a double from procid 0....
        double value;
        MPI_Status status;
        ierr = MPI_Recv(&value, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if (ierr == MPI_SUCCESS)
            printf("ProcID %d received value %lf.\n", procid, value);
        else 
            printf("ProcID %d did not sucessfully receive a value!\n",procid);
    }
    
    ierr =  MPI_Finalize();
}
