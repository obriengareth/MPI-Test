#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>

#define WORKTAG		1
#define DIETAG		2

int myrank, mysize;


main(argc, argv)

int	argc;
char	*argv[];
{
  //int my_rank, my_size;
  
  MPI_Init(&argc, &argv);                 
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);  /// process rank, 0 thru N-1 
  MPI_Comm_size(MPI_COMM_WORLD,&mysize);
 
  printf(" Size %d from node %d\n",mysize,myrank);
  
  if( argc!=3)
  {
   printf(" Incorrect usage -- try again -- \n");
   MPI_Finalize(); exit(0);
  }
  else
  {
   printf("NODE%d %d,%s,%s\n",myrank,argc,argv[1],argv[2]);
  }
 
  if (myrank == 0) 
  {
    master();
  } 
  else 
  {
    slave();
  }

  MPI_Finalize();
}


master()
{
    int ntasks, rank, work;
    double result;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD,&ntasks); /* #processes in application */

///Seed the slaves.
    for (rank = 1; rank < ntasks; ++rank) 
    {
      work = rank/* get_next_work_request */;
      MPI_Send(&work,1,MPI_INT,rank,WORKTAG,MPI_COMM_WORLD);
    }

/// Receive a result from any slave and dispatch a new work request work requests have been exhausted.

    work = work+1/* get_next_work_request */;

    while (work<40/* valid new work request */) 
    {
     MPI_Recv(&result,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);/* received message info */

     MPI_Send(&work, 1, MPI_INT, status.MPI_SOURCE,WORKTAG, MPI_COMM_WORLD);

     work = work+1/* get_next_work_request */;
    }

/// Receive results for outstanding work requests.
    for (rank = 1; rank < ntasks; ++rank) 
    {
     MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

// Tell all the slaves to exit.
    for (rank = 1; rank < ntasks; ++rank) 
    {
      MPI_Send(0, 0, MPI_INT, rank, DIETAG, MPI_COMM_WORLD);
    }
}

slave()
{
    double result;
    int work;
    MPI_Status status;
      
    //MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    
    for (;;) 
    {
      MPI_Recv(&work, 1, MPI_INT, 0, MPI_ANY_TAG,MPI_COMM_WORLD, &status);

// Check the tag of the received message.
     if (status.MPI_TAG == DIETAG) 
     {
       return;
     }

     result = do_the_work(work);
   //  result = 1.0/* do the work */;

     MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
}


//////////////////////////////////////////////////////////////////////////
/// messing around with functions to up the work load

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
t1 = t.tm_sec+2*myrank;
t2 = t.tm_min+3*myrank;
t3 = t.tm_hour;
t4 = t.tm_mday;
t5 = t.tm_mon;
t6 = t.tm_year;
iseed = t6+70*(t5+2*myrank+12*(t4+31*(t3+23*(t2+59*t1))));
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


do_the_work(int work_id)
{
 int i,j;
 double result,mess;
 
 for (i=0; i<10000; i++)
 {
  j=i;
  mess=ranf();
 }
 printf(" hello world from node %d just finished work job %d\n",work_id,myrank);

 result=1.0;
 
 return;
}
