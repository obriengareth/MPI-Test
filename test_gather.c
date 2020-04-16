////////////////////////////////////////////////////////////////////
//  2D ELM - Gareth O'Brien 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>

int my_rank, my_size;
MPI_Comm new_comm;
MPI_Status status;
const  int  TAG_SEND   = 50;
const  int  ndims      = 1;
MPI_Datatype fcol;             // new datatype for the slice
MPI_Datatype scol;             // new datatype for the slice
#define MAX_NB_OF_COMM 512
MPI_Request array_of_requests[MAX_NB_OF_COMM];
MPI_Status  array_of_statuses[MAX_NB_OF_COMM];



////////////////////////////////////////////////////////////////////
// MAIN 
main(int argc ,char *argv[])
{
 int i,j,k;
 int dims[1],period[1],reorder;
 int rank,size;
 double start, finish,t;

//////////////////////////////////////////////////////////////////
//           Initialising MPI
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
   MPI_Finalize(); exit(0);
 }
/*
 #define No 100
 int test_array[No];
 for(i=0; i<No; i++)
 {
   test_array[i]=my_rank;
 }

 if(my_rank==2)
 {
 for(i=0; i<No; i++)
 printf("%d %d\n",my_rank,test_array[i]);
 }
 int root=0;
 MPI_Gather( test_array, 10, MPI_INT, test_array, 10, MPI_INT, root, new_comm); 
 MPI_Barrier(new_comm);
 MPI_Bcast(test_array,No,MPI_INT,root,new_comm);

 if(my_rank==0)
 {
 for(i=0; i<No; i++)
 printf("%d %d\n",my_rank,test_array[i]);
 }
 MPI_Barrier(new_comm);
 if(my_rank==2)
 {
 for(i=0; i<No; i++)
 printf("%d %d\n",my_rank,test_array[i]);
 }*/


 #define No 50
 #define Nn 3
 int test_array[No][Nn];
 for(i=0; i<No; i++)
 {
 for(j=0; j<Nn; j++)
 {
   test_array[i][j]=my_rank+j;
 }
 }

 if(my_rank==2)
 {
 for(i=0; i<No; i++)
 printf("%d: %d %d %d\n",my_rank,test_array[i][0],test_array[i][1],test_array[i][2]);
 }
 int root=0;
 MPI_Gather( test_array, 15, MPI_INT, test_array, 15, MPI_INT, root, new_comm); 
 MPI_Barrier(new_comm);
 MPI_Bcast(test_array,No*Nn,MPI_INT,root,new_comm);

 if(my_rank==0)
 {
 for(i=0; i<No; i++)
 printf("%d: %d %d %d\n",my_rank,test_array[i][0],test_array[i][1],test_array[i][2]);
 }
 MPI_Barrier(new_comm);
 if(my_rank==2)
 {
 for(i=0; i<No; i++)
 printf("%d: %d %d %d\n",my_rank,test_array[i][0],test_array[i][1],test_array[i][2]);
 }


 MPI_Finalize();
  
}
