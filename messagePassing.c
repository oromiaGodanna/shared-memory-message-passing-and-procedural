/*message passing*/

#include <stdio.h>
#include <mpi.h>
#define send_data_tag 2001
#define return_data_tag 2002

int main(int argc, char **argv)
{
	int my_id, root_process, ierr, num_procs;
	MPI_Status status;
	int num = 0;

	/* Create child processes, each of which has its own variables.
	* From this point on, every process executes a separate copy
	* of this program.  Each process has a different process ID,
	* ranging from 0 to num_procs minus 1, and COPIES of all
	* variables defined in the program. No variables are shared.
	**/

	ierr = MPI_Init(&argc, &argv);

	//find out MY process ID, and how many processes were started

	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	
	int nextId;
	if( my_id == 0 ) {
		//print the process id for process 0 with the total of processes
		printf("Hello world! I'm process %i out of %i processes\n", my_id, num_procs);
		//get the id of the next process
		nextId = my_id+1;
		//send num to the next process
		if(my_id  < (num_procs -1)){
			ierr = MPI_Send( &num, 1 , MPI_INT, nextId, 0, MPI_COMM_WORLD);
		}

		
	}
	else if( my_id == 1 ) {
		//print the process id for process 1 with the total of processes
		printf("Hello world! I'm process %i out of %i processes\n", my_id, num_procs);
		
		
		//recive the num sent from the above process
		int rec_num;
		printf("On process %d I sent %d to process %d.\n", (my_id-1), num, nextId);
		ierr = MPI_Recv( &rec_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("On process %d ", my_id);
		printf("Number %i recived from process %i\n", rec_num, (my_id-1));
		
		//add one to rec_num to send it to the next process
		rec_num += 1;
		
		//get the id of the next process
		nextId = my_id+1;
		
		//send num to the next process
		if(my_id  < (num_procs -1)){
			ierr = MPI_Send( &rec_num, 1 , MPI_INT, nextId, 0, MPI_COMM_WORLD);

		}
	
		

		
	}
	else if( my_id == 2 ) {

		//print the process id for process 2 with the total of processes
		printf("Hello world! I'm process %i out of %i processes\n", my_id, num_procs);
		
		//recive the num sent from the above process
		int rec_num;
		ierr = MPI_Recv( &rec_num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("On process %d ", my_id);
		printf("Number %i recived from process %i\n", rec_num, (my_id-1));
		
		//add one to rec_num to send it to the next process
		rec_num += 1;
		
		//get the id of the next process
		nextId = my_id+1;
		
		//send num to the next process
		if(my_id  < (num_procs -1)){
			ierr = MPI_Send( &rec_num, 1 , MPI_INT, nextId, 0, MPI_COMM_WORLD);
		}
		
	} 
	else {
		if(num_procs<=3){
			return 0;
		}
		else{
			//for any remainiing processes do this
			printf("Hello world! I'm process %i out of %i processes\n",my_id, num_procs);
			
			//recive the num sent from the above process
			int prev_id = my_id - 1;
			int rec_num;
			ierr = MPI_Recv( &rec_num, 1, MPI_INT, prev_id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("On process %d ", my_id);
			printf("Number %i recived from process %i\n", rec_num, (my_id-1));
			
			//add one to rec_num to send it to the next process
			rec_num += 1;
			
			//get the id of the next process
			nextId = my_id+1;
			
			//send num to the next process
			if(my_id  < (num_procs -1)){//check if this is the last process so that it won't send anything
				ierr = MPI_Send( &rec_num, 1 , MPI_INT, nextId, 0, MPI_COMM_WORLD);
			}
		}
	}
	// Stop this process
	
	
	ierr = MPI_Finalize();
	return 0;
}
