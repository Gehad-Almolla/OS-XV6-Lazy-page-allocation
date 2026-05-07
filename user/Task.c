# include "kernel/types.h"
# include "user/user.h"

int main() {
 for (int i=0; i<3; i++) {
 int pid = fork();
 if(pid == 0) {
 //child
 printf("%d", i);
 } else {
 //parent
 }
 }
}
