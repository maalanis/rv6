#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/pstat.h"

int *argv_sec;
struct rusage argv_sec2;
char *args[1000];

int main(int argc, char **argv) {
	//we will do a traverse through argv, shiftting through 
	for(int i = 1; i < argc; i++){
		args[i-1] = argv[i];
	}
	
	args[argc - 1] = 0;
	
	//Start measuring the CPU time
	int start_ticks = uptime();
	int pid = fork();
	
	if(pid < 0) {
		printf("Fork failed\n");
		exit(1);
	}
	
	if(pid == 0){
		//child processor: execute the given command
		exec(args[0], args);
		
		//if the exec fails, we will exit
		printf("Failed to execute");
		exit(1);
	}
	else{
		//parent process: wait for the child to finish
		if(wait2(0, &argv_sec2) < 0){
			printf("init: wait2 failed\n");
		}
		
		//we will stop measuring the CPU time
		int end_ticks = uptime();
		
		//calculate and print elapsed time and %CPU
		int elapsed_time = end_ticks - start_ticks;
		int cpu_time = argv_sec2.cputime;
		int cpu_percentage = (cpu_time * 100) / elapsed_time;
		
		printf("Elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n", elapsed_time, cpu_time, cpu_percentage);
		
	}
	exit(0);
}
