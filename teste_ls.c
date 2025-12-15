#include "unistd.h"
#include "fcntl.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{
	int pipefd[2];
	pid_t pid;
	char *var[] = {"ls", NULL};
	char *str;

	pipe(pipefd);
	pid = fork();
	if (!pid)
	{
		close(pipefd[0]);
		printf("%d\n",errno);
		execve("/usr/bin/shjdiusjhd",var,envp);
		exit(1);
	}
	close(pipefd[1]);
	kill(pid, SIGINT);
	// waitpid(pid, NULL, 0);
	str = calloc(1, 100);
	read(pipefd[0],str,100);
	printf("%d\n",errno);

}
