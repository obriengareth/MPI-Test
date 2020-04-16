/****************************************************************************
* mpifilein.c
* DESCRIPTION:  Input using MPI IO functions
******************************************************************************/

#include "mpi.h"
#define array_size 100

static char filename[] = "output.dat";

main( int argc, char **argv )
{
    int myrank, commsize;
    MPI_File infile;
    MPI_Offset offset;
    MPI_Status status;
    int nbytes, myarray[array_size], mode, i;

    /* initialize MPI */
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &commsize );

    /* open file */
    mode = MPI_MODE_RDONLY;

    MPI_File_open( MPI_COMM_WORLD, filename, mode, MPI_INFO_NULL, &infile );

    /* set file view */
    offset = 0;
    MPI_File_set_view( infile, myrank*array_size, MPI_INT, MPI_INT, "native", MPI_INFO_NULL );

    /*  write buffer to file */
    MPI_File_read( infile, &myarray[0], array_size, MPI_INT, &status );

    /* print out number of bytes written */
    MPI_Get_elements( &status, MPI_CHAR, &nbytes );
    printf( "TASK %d ====== number of bytes read = %d ======\n", myrank, nbytes );

    /* close file */
    MPI_File_close( &infile );

    /* print out results */
    for (i=0; i < array_size; i++) 
      printf("%4d%c", myarray[i], i%10==9 ? '\n' : ' ');

    /* finalize MPI */
    MPI_Finalize();
}
