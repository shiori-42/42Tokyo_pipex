/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mondatory_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:50:24 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/29 19:57:44 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int infile_fd, int pipe_fd[2], int new_pipe_fd, char **argv)
{
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(new_pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(new_pipe_fd[0]);
	close(new_pipe_fd[1]);
	my_execve(argv[argv_index]);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	last_child(int outfile_fd, int pipe_fd[2], int new_pipe_fd, char **argv)
{
	dup2(new_pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(new_pipe_fd[0]);
	close(new_pipe_fd[1]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	my_execve(argv[argv_index]);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fork_cmd(int iofile_fd, int pipe_fd[2], char **argv, int fork_status)
{
	pid_t	pid;
	int		new_pipe_fd[2];

	if (pipe(new_pipe_fd) == -1)
		handle_error("pipe");
	pid = fork();
	if (pid < 0)
		handle_error("fork");
	else if (pid == 0)
	{
		if (fork_status == 1)
			first_child(iofile_fd, pipe_fd, new_pipe_fd, argv[argv_index]);
		else if (fork_status == 3)
			last_child(iofile_fd, pipe_fd, new_pipe_fd, argv[argv_index]);
		else
			middle_child(pipe_fd,new_pipe_fd, pipe_fd, argv[argv_index]);
		perror("execve");
		exit(1);
	}
	close(new_pipe_fd[0]);
	close(new_pipe_fd[1]);
}
