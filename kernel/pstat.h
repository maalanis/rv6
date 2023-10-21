struct pstat {
	int pid; 
	enum procstate state; 
	uint64 size; 
	int ppid; 
	char name[16];
	uint readytime;
	uint cputime;
};

struct rusage {
   uint cputime;
};	
