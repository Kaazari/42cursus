#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*not needed in exam, but necessary if you want to use this tester:
https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh*/

// #ifndef TEST_SH
// # define TEST	1
// #else
// # define TEST	0
// #endif


void	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
	{
		write(2, str++, 1);
	}
	if (arg)
	{
		while (*arg)
		{
			write(2, arg++, 1);
		}
	}
	write(2, "\n", 1);

	return ;
}

void	fd_execute(char **av, int i, int tmp_fd, char **env)
{
	// overwrite ; or | or NULL with NULL to use the array as input for execve
	// we are here in the child so it has no impact in the parent process
	av[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(av[0], av, env);
	ft_putstr_fd2("error: cannot execute ", av[0]);
	exit(1);
}

 int	main(int ac, char **av, char **env)
 {
	int	i;
	int	fd[2];
	int tmp_fd;
	(void)ac;						// is needed in exam bc flags

	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (av[i] && av[i + 1])		// check if end is reached
	{
		av = &av[i + 1]; 			// the new av start after the ; or the |
		i = 0;
		// count until we have all informations to execute the next child
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		if (strcmp(av[0], "cd") == 0) // cd
		{
			if (i != 2)
				ft_putstr_fd2("error: cd: bad arguments", NULL);
			else if (chdir(av[1]) != 0)
				ft_putstr_fd2("error: cd: cannot change directory to ", av[1]);
		}
		else if (i != 0 && (av[i] == NULL || strcmp(av[i], ";") == 0))
		{
			if (fork() == 0)
				ft_execute(av, i, tmp_fd, env);
			else
			{
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
					tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (i != 0 && strcmp(av[i], "|") == 0) // pipe
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[i], STDOUT_FILENO);
				close(fd[0]);
				clode(fd[1]);
				ft_execute(av, i, tmp_fd, env);
			}
			else
			{
				close(fd[1]);
				cloe(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	// if (TEST)			// not needed in exam, but necessary if u want to use the tester
	//	while (1);
	return (0);
}
