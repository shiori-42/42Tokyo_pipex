/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:52:51 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/29 19:56:11 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_child(int *prev_pipe_fd, int *next_pipe_fd, char *cmd)
{
	pid_t pid;

	if (pipe(next_pipe_fd) < 0)
	{
		handle_error("pipe error in middle_child");
	}
	pid = fork();
	if (pid == 0)
	{
		close(next_pipe_fd[0]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
		dup2(next_pipe_fd[1], STDOUT_FILENO);
		close(next_pipe_fd[1]);
		my_execve(cmd);
		perror("execve error in middle_child");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(next_pipe_fd[1]);
		close(prev_pipe_fd[0]);
	}
}