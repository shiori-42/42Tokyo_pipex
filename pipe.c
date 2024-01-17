/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:43:25 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/17 21:15:51 by syonekur         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

void	do_child_process(int *pipe_fd, char *argv[], int argv_index,
		int is_here_doc)
{
	int	fd_in;
	int	fd_out;

	fd_in = open_input_file(argv[argv_index], is_here_doc);
	if ((is_here_doc == 0 && argv_index == 2) || (is_here_doc == 1
			&& argv_index == 3))
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	fd_out = open_output_file(argv[argc - 1], is_here_doc);
	if (argv_index < argc - 2)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else
	{
		dup2(iofd.outfile_fd, STDOUT_FILENO);
		close(iofd.outfile_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	my_execve(argv[argv_index]);
}

int	pipe_cmd(char *argv[], int argv_index, int is_here_doc)
{
	int	i;
	int	pipe_fd[2];
	int	pid;
	int	prev_fd;

	i = 0;
	prev_fd = -1;
	while (argv[argv_index + 1] != NULL)
	{
		if (pipe(pipe_fd) == -1)
			handle_error("pipe");
		pid = fork();
		if (pid == -1)
			handle_error("fork");
		if (pid == 0)
			do_child_process(pipe[fd], argv, argv_index, is_here_doc);
		else
			do_parent_process(pipe[fd], argv, argv_index, is_here_doc);
		argv_index++;
	}
	return (0);
}
