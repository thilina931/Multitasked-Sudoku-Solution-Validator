/*
SLIIT_ID:IT15005786
CURTIN_ID:19222233
NAME:Thilina Loku Bogahawatta*/


#include<stdlib.h>		
#include<stdio.h>		/* exit(), malloc(), free() */
#include<sys/types.h>	/* key_t, sem_t, pid_t */
#include<sys/shm.h>		/* shmat(), IPC_RMID*/
#include<semaphore.h>	/* sem_open(), sem_destroy(), sem_wait()*/
#include<fcntl.h>		/* O_CREAT, O_EXEC */


typedef struct structure{
int pid;

}subt;

int M,N;
int *Buffer1; 
int segid1,y=1,number1; 
int i,j,l;
FILE *file1;
int c,d,forvalue;
sem_t *sem;
unsigned int semValue;
int *temp;
int results[9]={0};
int results2[9]={0};


int main(int argc,char *argv[]){

subt *sub;

/*Getting command line arguments*/

M=atoi(argv[2]);
N=atoi(argv[3]);

/*Creating and attaching Buffer1, shared memory */

if((segid1=shmget(800000,sizeof(int)*M*N,IPC_CREAT|0666))<0)
{
perror("shmget1");
exit(1);
}

if((Buffer1=(int *)shmat(segid1,NULL,0))<0){
perror("shmat");
exit(1);

}


semValue=1;
/*Semphore value, if this value is changed to 0 
 * it dosen't  access to crirical section*/
/* initialize semaphores for shared processes */
sem=sem_open("PSEM",O_CREAT|O_EXCL,0644,semValue); 
/* name of semaphore is "pSem", semaphore is reached using this name */
sem_unlink("PSEM");/* unlink prevents the semaphore existing forever 
/* if a crash occurs during the execution
  


/*Opening files */
file1=fopen(argv[1],"r");

if(file1==NULL ){

	printf("File open Failed!!");
	exit(1);

}

for(i=0;i<M;i++){
	for(j=0;j<N;j++){
	 if(fscanf(file1,"%d",&number1)!=EOF){
		Buffer1[i*N+j]=number1;
	 }
	}
}



printf("     TABLE  \n");

for(i=0;i<M;i++){
	for(j=0;j<N;j++){

   	 printf("  %d",Buffer1[i*N+j]);
 
	}
printf("\n");
}



  for(i=0;i<=M;i++){    

	
	sub->pid=fork();

	if(i==9){

		if(sub->pid==0){
		printf("Validation_Result_from_Processs (%d):%d\n",i+1,getpid());
		printf("Columns %d of %d Valid  \n",i,i);
		
		// columns cheak 
		for(j=0;j<N;j++){
		

			int tmp;
				
			int array_value= Buffer1[i*N+j];

			if(results2[0]==0){
				
				results2[0]=array_value;
				
				
				
						
			
			}else
			{

			int n=sizeof(results2);
		
			for(l=1;l<=8;l++){
			
			
			

			if(results2[l]==array_value){
				
				printf("Invalid Columns: %d",results2[j]);

			}else{
				
				results2[l]=array_value;


			}
			
			}
			
			

			}

	}

		}
	

		}
	else{
	
	//int sum2=0;
	if(sub->pid<0){
	
	printf("Error");
	}

	else if(sub->pid==0)
		{
		sem_wait(sem);

printf("Validation_Result_from_Process (%d):%d\n",i+1,getpid());

		
		//row cheaking 
 		for(j=0;j<N;j++){
		

			int tmp;
				
			int array_value= Buffer1[i*N+j];

			if(results[0]==0){
				
				results[0]=array_value;
				
				
				
						
			}else
			{



			
			int n=sizeof(results);
		
			for(l=1;l<=8;l++){
			
			
			

			if(results[l]==array_value){
				
				printf("Invalid Row: %d",results[j]);

			}else{
				
				results[l]=array_value;


			}
			
			}
					

			}

	}
printf("Row %d is Valid \n",i+1);
			
		
				
		printf("\n");
		sem_post(sem);	
		exit(0);

		}

	else
	{
	wait(NULL);
	}
}

}
sem_destroy(sem);
}

