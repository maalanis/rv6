struct pstat {
  int pid;     // Process ID
  int priority;		//adding priority for testing ############################
  enum procstate state;  // Process state
  uint64 size;     // Size of process memory (bytes)
  int ppid;        // Parent process ID
  char name[16];   // Parent command name
  uint readytime;
  uint cputime;
};

struct rusage {
  uint cputime;
};

