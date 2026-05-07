#include "kernel/types.h"
#include "user/user.h"

int main() {
int fds[2]; //from child to parent
char buf[100];
int n;
char *argv[]= {"child", "process", "is", "now", "replaced.", 0 };

pipe(fds);

int pid;
pid = fork();

if(pid ==0) {
        //child
  
        n = read(fds[0], buf, sizeof(buf));
	write(1, buf, n);
	exec("echo", argv);
} else {
        //parent
        write(fds[1], "hello child, now write.\n", 24);
        wait(0);
        }
exit(0);
}


