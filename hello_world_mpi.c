////////////////////////////////////////////////////////////////////
// DO NOT EDIT
#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
//#include<time.h>
#include<mpi.h>
///////////////////////////////////////////////////////////////////////////

                                /* MAIN */
main(int argc ,char *argv[])
{
  int i,j,p,no;
  int dims[1],period[1],reorder;
  int rank,size;
  int my_rank,my_size;
 
MPI_Comm new_comm;
MPI_Status status;

/////////////////////////////////////////////////////////////////////////////////
//           Initialising MPI
/////////////////////////////////////////////////////////////////////////////////
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
dims[0]=size;
period[0]=1;
reorder=1;
MPI_Cart_create(MPI_COMM_WORLD, 1, dims, period, reorder, &new_comm);
MPI_Comm_rank(new_comm, &my_rank);
MPI_Comm_size(new_comm, &my_size);

if( argc!=1)
{
   printf(" Incorrect usage -- try again -- \n");
   MPI_Finalize(); 
   exit(0);
}
 

 printf(" hello world from node %d\n",my_rank);
 
 //for(i=0; i<1000000000; i++)
 //{
  //j=10; j=1000; j=i-100;
 //} 

system("hostname");

 MPI_Finalize();

}

