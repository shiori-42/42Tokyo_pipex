#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	check_io_fd(int infile_fd,int outfile_fd)
{
	if (infile_fd==-1&&outfile_fd==-1)
		return(-1);
	else if(infile_fd==-1)
	{
		close(outfile_fd);
		return(-1);
	}
	else
	{
		close(infile_fd);
		return(-1);
	}
	return(1);
}

int check_argc_argv(int argc, char **argv)
{
	(void)argv;
	if(argc!=5)
		return (-1);
	return(1);
}

// first Child processe(ls -l)
int	first_Child_process(int infile_fd,int pipe_fd[2])
{
	pid_t	pid;
	char *ls_args[]={"/usr/bin/ls","-l",NULL};

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);

		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		execve(ls_args[0],ls_args,NULL);
		perror("execve");
		exit(EXIT_FAILURE);
		
	}
	return(pid);
}

//second Child process(wc -l)
int	second_child_process(int outfile_fd,int pipe_fd[2])
{
	pid_t	pid;
	char *wc_args[]={"/usr/bin/wc","-l",NULL};

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);

		execve(wc_args[0],wc_args,NULL);
		exit(EXIT_FAILURE);
	}
	return(pid);
}

int	main(int argc, char *argv[])
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile_fd;
	int		outfile_fd;

	if (!(check_argc_argv(argc, argv))) //check commandline_args
	{
		return (-1);
	}
	infile_fd = open(argv[1], O_RDONLY); //file open both read and write
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!(check_io_fd(infile_fd,outfile_fd))) //if file open failed,close either filediscripter
	{
		return (-1);
	}
	if (pipe(pipe_fd) == -1) //make pipe
		return (-1);
	
	first_Child_process(infile_fd,pipe_fd);//call first
	second_child_process(outfile_fd,pipe_fd);//call second
	clo
	return(0);
}
