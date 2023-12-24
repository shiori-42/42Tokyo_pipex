/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:18:15 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/24 21:38:36 by syonekur         ###   ########.fr       */
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

int	check_io_fd(int infile_fd, int outfile_fd)
{
	if (infile_fd == -1 && outfile_fd == -1)
		return (-1);
	else if (infile_fd == -1)
	{
		close(outfile_fd);
		return (-1);
	}
	else
	{
		close(infile_fd);
		return (-1);
	}
	return (1);
}

int	check_argc_argv(int argc)
{
	if (argc != 5)
		return (-1);
	return (1);
}

int	main(int argc, char *argv[])
{
	int pipe_fd[2];
	int infile_fd;
	int outfile_fd;

	if (!(check_argc_argv(argc)))
		return (-1);
	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!(check_io_fd(infile_fd, outfile_fd)))
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	first_child_process(infile_fd, pipe_fd, argv);
	second_child_process(outfile_fd, pipe_fd, argv);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}