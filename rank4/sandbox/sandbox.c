#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	kill_process(int signum);
int	check_status(int wstatus, unsigned int timeout, bool verbose);

pid_t	g_child_pid = 0;
bool	g_kill_success = false;
bool	g_kill_fail = false;

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int	wstatus = 0;
	struct sigaction *act;

	g_child_pid = fork();
	if (g_child_pid == -1)
		return (-1);
	else if (g_child_pid == 0)
	{ // child process
		f();
		exit(0);
	}
	//catch alarm and kill child process on signal
	act->sa_handler = kill_process;
	act->sa_flags = SA_RESTART;
	sigaction(SIGALRM, act, NULL);
	alarm(timeout);
	if (waitpid(g_child_pid, &wstatus, 0) == -1)
		return (-1);
	if (g_kill_fail)
		return (-1);
	return (check_status(wstatus, timeout, verbose));
}

void	kill_process(int signum)
{
	(void) signum;
	if (kill(g_child_pid, SIGKILL) == -1)
		g_kill_fail = true;
	g_kill_success = true;
}

int	check_status(int wstatus, unsigned int timeout, bool verbose)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGKILL && g_kill_success)
		{
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
		}
		else
			if (verbose)
				printf("Bad function: %s\n", strsignal(WTERMSIG(wstatus)));
		return (0);
	}
	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus))
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", WEXITSTATUS(wstatus));
			return (0);
		}
		else
			printf("Nice function\n");
		return (1);
	}
	return (-1);
}
