/****************************************************************************
* fileout-bin.c
* DESCRIPTION:  Create an output file that can be read by filein-bin.c
*               Uses fwrite
*
*  Does not always works correctly because of the concurrency!!
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

    /* initialize array */
    for (i=0; i < array_size; i++)
      myarray[i] = 10*myrank*array_size+i;

    /* print out array for fun */
    for (i=0; i < array_size; i++) 
      printf("%4d%c", myarray[i], i%10==9 ? '\n' : ' ');

    /* open file */
    fh = fopen( filename, "w");

    /* seek to write location */
    fseek( fh, array_size*myrank*sizeof(int), SEEK_SET );
    if ( fwrite( (void *) myarray, sizeof(int), array_size, fh) > 0 )
      printf("process %d portion successfully written\n", myrank);

    /* close file */
    fclose( fh );

    /* finalize MPI */
    MPI_Finalize();
}
