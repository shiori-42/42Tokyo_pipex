/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:32:15 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/18 19:36:32 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_stdin(int *pipe_fd, char *argv[], int argv_index, int is_heredoc)
{
	int	fd_in;
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
}

void	set_stdout(int *pipe_fd, char *argv[], int argv_index, int is_heredoc)
{
	int	fd_out;

	if (argv[argv_index + 2] == NULL)
	{
		fd_out = open_output_file(argv, argv_index, is_heredoc);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
}

void	do_child_process(int *pipe_fd, char *argv[], int argv_index,
		int is_heredoc)
{
	set_stdin(pipe_fd, argv, argv_index, is_heredoc);
	set_stdout(pipe_fd, argv, argv_index, is_heredoc);
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
	int	pipe_fd[3];
	int	pid;

	pipe_fd[2] = -1;
	while (argv[argv_index + 1] != NULL)
	{
		if (pipe(pipe_fd) == -1)
			perror_and_exit("pipe");
		pid = fork();
		if (pid == -1)
			perror_and_exit("fork");
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
