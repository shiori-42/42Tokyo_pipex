




#include "pipex.h"

void	do_child_process(int *pipe_fd, char *argv[], int argv_index,
		int is_heredoc)
{
	int	fd_in;
	int	fd_out;
	int	prev_fd;

	prev_fd = pipe_fd[2];
	if (argv_index == is_heredoc + 2)
	{
		fd_in = open_input_file(argv, argv_index, is_heredoc);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (argv[argv_index + 2] != NULL)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else
	{
		fd_out = open_output_file(argv, argv_index, is_heredoc);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	my_execve(argv[argv_index]);
}

int	do_parent_process(int *pipe_fd)
{
	if (pipe_fd[2] != -1)
		close(pipe_fd[2]);
	pipe_fd[2] = pipe_fd[0];
	close(pipe_fd[1]);
	return (0);
}

int	pipe_cmd(char *argv[], int argv_index, int is_heredoc)
{
	int pipe_fd[3];
	int pid;

	pipe_fd[2] = -1;
	while (argv[argv_index + 1] != NULL)
	{
		if (pipe(pipe_fd) == -1)
			handle_error("pipe");
		pid = fork();
		if (pid == -1)
			handle_error("fork");
		if (pid == 0)
			do_child_process(pipe_fd, argv, argv_index, is_heredoc);
		else
			do_parent_process(pipe_fd);
		argv_index++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (0);
}