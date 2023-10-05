

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char *argv1[1000];
int main(int argc, char **argv)
{	

for( int i = 1; i < sizeof(argv); i++)
{
	argv1[i-1] = argv[i];
}

	int startTime = uptime();
	int endTime = 0;
	int c_pid = fork();
	if(c_pid<0)
	{
		printf("Fork failed, no child was made");
		
		exit(1);
	}
	else if(c_pid == 0)
	{
		printf("Hello I am child (pid:%d)\n", (int) getpid());
		exec(argv1[0], argv1);
		
		//this code should not work
		printf("Looks like execv failed:(\n");
		exit(1);
	} 
 	else
 	{
 		int c_wait = wait((int *) 0);
 		if(c_wait == c_pid)
 		{
 			printf("back to parent process\n");
 			endTime = uptime();
 			printf("total running time: %d\n", endTime-startTime);
 			exit(0);
 		} else if (c_wait <0)
 		{
 			printf("error going back to parent\n");
 			exit(1);
 			
 		}
 		else {
 		
 			exit(1);
 		}
 		
 		exit(0);
 		
 		
 		
 		
 	}
}

