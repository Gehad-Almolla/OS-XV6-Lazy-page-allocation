#include "kernel/types.h"
#include "user/user.h"

int main() {
int fds[2]; //from child to parent
char buf[100];
int n;

pipe(fds);

int pid;
pid = fork();

if(pid ==0) {
	//child
	write(fds[1], "hello parent, i'm child\n", 24);
  pause(10);
  
	n = read(fds[0], buf, sizeof(buf));
	write(1, buf, n);
	
} else {
	//parent
	n = read(fds[0], buf, sizeof(buf));
	write(1, buf, n);

	write(fds[1], "hello child, i'm parent\n", 24);
	wait(0);
	}
exit(0);
}
