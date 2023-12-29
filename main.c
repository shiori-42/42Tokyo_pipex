/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:54:29 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/29 19:53:56 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_fd	init_fd(char *infile, char *outfile, int here_doc)
{
	t_fd	iofd;

	if (here_doc)
		iofd.infile_fd = STDIN_FILENO;
	else
		iofd.infile_fd = open(infile, O_RDONLY);
	iofd.outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (check_io_fd(iofd.infile_fd, iofd.infile_fd) == -1)
		handle_error(NULL);
	return (iofd);
}

void	handle_erorr(char *msg)
{
	perror(msg);
	exit(1);
}

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
	else if (outfile_fd == -1)
	{
		close(infile_fd);
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		pipe_fd[2];
	t_fd	iofd;
	int		argv_index;
	int		here_doc;

	if (argc < 5)
		handle_error("NULL");
	here_doc = (ft_strncpm(argv[1], "here_doc", 8) == 0);
	iofd = init_fd(argv[1], argv[argc - 1], here_doc);
	argv_index = 2 + here_doc;
	if (pipe(pipe_fd) < 0)
		handle_error("pipe");
	while (argv_index < argc - 1)
	{
		if (argv_index == 2 + here_doc)
			fork_cmd(iofd.infile_fd, pipe_fd, argv, 1);
		else if (argv_index == argc - 2)
			fork_cmd(iofd.outfile_fd, pipe_fd, argv, 3);
		else
			middle_child(NULL, pipe_fd, argv, 2);
		argv_index++;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (0);
}
