#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){

//we will call the function uptime
unsigned int clk_ticks = uptime();

//this will print the clk_ticks from the previous function
printf("Up clock ticks: %d\n", clk_ticks);
exit(0);

}
