/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:43:25 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/05 17:14:08 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_memory(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	handle_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	do_child_process(int *pipe_fd, t_fd iofd, t_cmd_info cmd_info,
		char **argv)
{
	if ((cmd_info.here_doc == 0 && cmd_info.argv_index == 2)
		|| (cmd_info.here_doc == 1 && cmd_info.argv_index == 3))
	{
		dup2(iofd.infile_fd, STDIN_FILENO);
		close(iofd.infile_fd);
	}
	else
	{
		dup2(iofd.prev_fd, STDIN_FILENO);
		close(iofd.prev_fd);
	}
	if (cmd_info.argv_index < cmd_info.argc - 2)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(iofd.outfile_fd, STDOUT_FILENO);
		close(iofd.outfile_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	my_execve(argv[cmd_info.argv_index]);
}

int	pipe_cmd(t_fd iofd, t_cmd_info cmd_info, char *argv[])
{
	int	pipe_fd[2];
	int	pid;

	iofd.prev_fd = -1;
	while (cmd_info.argv_index < cmd_info.argc - 1)
	{
		if (pipe(pipe_fd) == -1)
			handle_error("pipe");
		pid = fork();
		if (pid == -1)
			handle_error("fork");
		if (pid == 0)
			do_child_process(pipe_fd, iofd, cmd_info, argv);
		else
		{
			if (iofd.prev_fd != -1)
				close(iofd.prev_fd);
			iofd.prev_fd = pipe_fd[0];
			close(pipe_fd[1]);
		}
		cmd_info.argv_index++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (0);
}
