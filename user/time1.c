#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//struct &rusage;

char *argv_sec[1000];

int main(int argc, char **argv){

//we will do a traverse through argv, shiftting through 
for(int i = 1; i < sizeof(argv); i++){
	argv_sec[i-1] = argv[i];
}

argv_sec[sizeof(argv)] = 0;

//put uptime in a variable
int time1 = uptime();

//put fork in variable pid
int pid = fork();

if(pid < 0){
	printf("time1: failure in fork\n");
	exit(1);
}
else if(pid == 0){
	//we will call exec() with argv1[0] and argv1
	exec(argv_sec[0], argv_sec);
	printf("elapsed time failed\n");
	exit(1);
}
else{
		int wpid = wait((int *) 0);
		if(wpid == pid){ 
			//we will subtract the intial time minus the time that is currently here
			//int elapsed_time = time1 - uptime();
			printf("elapsed time: %d ticks\n", uptime() - time1);
			
			//we will exit the shell and restart it
			exit(1);
		}
		else if(wpid < 0){
			exit(1);
		}
		else{
			//we will do nothing since it did not have a parent proccess
			
		}
	}
	exit(0);
}
