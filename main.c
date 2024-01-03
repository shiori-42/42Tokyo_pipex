/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:54:29 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/03 18:51:15 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_tmp_file(void)
{
	int	tmp_fd;

	tmp_fd = open("/tmp/here_doc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		handle_error("error creating temp file for here_doc");
	return (tmp_fd);
}

void	handle_here_doc(int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, "LIMITER\n", 8) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open("/tmp/here_doc_tmp", O_RDONLY);
	if (tmp_fd < 0)
		handle_error("error reopening temp file for here_doc");
}

t_fd	init_fd(char *infile, char *outfile, int here_doc)
{
	t_fd	iofd;
	int		tmp_fd;

	if (here_doc)
	{
		tmp_fd = open_tmp_file();
		if (tmp_fd != -1)
			handle_here_doc(tmp_fd);
		iofd.infile_fd = tmp_fd;
	}
	else
		iofd.infile_fd = open(infile, O_RDONLY);
	iofd.outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (check_io_fd(iofd.infile_fd, iofd.outfile_fd) == -1)
		handle_error("error open");
	return (iofd);
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
	t_fd		iofd;
	t_cmd_info	cmd_info;
	int			argv_index;
	int			here_doc;

	if (argc < 5)
		handle_error("error args count");
	here_doc = (ft_strncmp(argv[1], "here_doc", 8) == 0);
	argv_index = 2 + here_doc;
	iofd = init_fd(argv[argv_index - 1], argv[argc - 1], here_doc);
	cmd_info.argc = argc;
	cmd_info.argv_index = argv_index;
	cmd_info.here_doc = here_doc;
	if (pipe_cmd(iofd, cmd_info, argv) != 0)
		return (-1);
	return (0);
}
