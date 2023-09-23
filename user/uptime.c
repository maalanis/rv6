#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
int clockTicks = uptime();
 printf( "up %d clock ticks", clockTicks);
 exit(0);
}


