//task 2 sleep program
# include "kernel/types.h"
# include "user/user.h"

int main(int argc, char *argv[]) {

if(argc != 2){
printf("invalid use. enter exactly one value.\n");
exit(1);
}

int ticks = atoi(argv[1]);
if(ticks == 0){
printf("enter a valid number.\n");
exit(1);
}

printf("sleeping..\n");
pause(ticks);
printf("done sleeping..\n");

exit(0);
}
