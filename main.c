/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:18:15 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/29 15:53:22 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cat_cmd_path(char *path, char *cmd)
{
	size_t	path_len;
	size_t	cmd_len;
	char	*cat_cmd_path;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	cat_cmd_path = malloc(path_len + cmd_len + 2);
	if (!cat_cmd_path)
		return (NULL);
	ft_strlcpy(cat_cmd_path, path, path_len + 1);
	cat_cmd_path[path_len] = '/';
	ft_strlcpy(cat_cmd_path + path_len + 1, cmd, cmd_len + 1);
	printf("%s\n", cat_cmd_path);
	return (cat_cmd_path);
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
	int	pipe_fd[2];
	int	infile_fd;
	int	outfile_fd;
	// add int first
	int first;
	int		status;

	if (argc < 5)
		return (-1);
	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (check_io_fd(infile_fd, outfile_fd) == -1)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	// first_child_process(infile_fd, pipe_fd, argv);
	// second_child_process(outfile_fd, pipe_fd, argv);
	//add fork_cmd
	first=1;
	fork_cmd(infile_fd, pipe_fd, argv,first);
	first=0;
	fork_cmd(outfile_fd, pipe_fd, argv,first);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
  while (1)
  {
    if (waitpid(-1, &status, 0) == -1)
      break ;
  }
  (void)status;
	return (0);
}
