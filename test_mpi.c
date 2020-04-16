////////////////////////////////////////////////////////////////////
// DO NOT EDIT
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// PARAMETERS THAT YOU CAN CHANGE
#define Max_Time 1000
#define Nx 100
#define Ny 100
#define output1 "out_lines"
#define output2 "out_grids"

//////////////////////////////////////////////////////////////////////////////
////////// DO NOT EDIT BELOW

double ranf();

                                /* MAIN */
main(int argc ,char *argv[])
{
  int i,j,p,no;
  int dims[1],period[1],reorder;
  int rank,size;
  int my_rank,my_size;
  double start, finish,t;
  FILE *out;
  char  string[50];
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
start=MPI_Wtime();

  if(my_rank==0)
  printf(" TEST PROGRAM \n");

/////////////////////////////////////////////////////////////////////////////////////
   sprintf( string,"%s%d",output1,my_rank);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s on %d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }
   for(j=0; j<Max_Time; j++)
   {
     fprintf(out,"%e \n",ranf() );
   }
   fclose(out);
   MPI_Barrier(new_comm);

////////////////////////////////////////////////////////////////////////////////////////
   sprintf( string,"%s%d",output2,my_rank);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s on %d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }
   for(j=0; j<Ny; j++)
   {
   for(i=0; i<Nx; i++)
     fprintf(out,"%e ",ranf() );
     fprintf(out,"\n");
   }
   fclose(out);
   MPI_Barrier(new_comm);
//////////////////////////////////////////////////////////////////////////////////////////

 finish=MPI_Wtime();
 printf(" Time for run on node %d is %lf minutes \n",my_rank,(finish-start)/60);

 MPI_Finalize();

}


double ranf()
{
const int ia=16807,ic=2147483647,iq=127773,ir=2836;
int il,ih,it;
double rc;
int t1,t2,t3,t4,t5,t6;
time_t ts,tp;
struct tm t;
int iseed;

/* Initial seed from the system time and and forced to be odd */

ts = time(&tp);
t  = *gmtime(&tp);
t1 = t.tm_sec;
t2 = t.tm_min;
t3 = t.tm_hour;
t4 = t.tm_mday;
t5 = t.tm_mon;
t6 = t.tm_year;
iseed = t6+70*(t5+12*(t4+31*(t3+23*(t2+59*t1))));
iseed=iseed*drand48();
ih = iseed/iq;
il = iseed%iq;
it = ia*il-ir*ih;
if (it > 0)
  {
  iseed = it;
  }
else
  {
iseed = ic+it;
  }
rc = ic;
return iseed/rc;
}
