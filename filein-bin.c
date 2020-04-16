/****************************************************************************
* filein-bin.c
* DESCRIPTION:  Read what fileout-bin wrote, uses fread
******************************************************************************/

#include "mpi.h"
#include <stdio.h>
#define array_size 100

static char filename[] = "output1.dat";

main( int argc, char **argv )
{
    int myrank, commsize;
    FILE *fh;
    int nbytes, mode, i;
    int myarray[array_size];

    /* initialize MPI */
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &commsize );

    /* open file */
    fh = fopen( filename, "r");

    /* seek to write location */
    fseek( fh, array_size*myrank*sizeof(int), SEEK_SET );
    if ( fread( (void *) myarray, sizeof(int), array_size, fh) > 0 )
      printf("process %d portion successfully read\n", myrank);

    /* close file */
    fclose( fh );

    /* print out results */
    for (i=0; i < array_size; i++) 
      printf("%4d%c", myarray[i], i%10==9 ? '\n' : ' ');

    /* finalize MPI */
    MPI_Finalize();
}
