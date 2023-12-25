/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:19:33 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/25 15:06:28 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_envpath_list(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd)
{
	char	**path;
	char	*cmd_path_list;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path_list = find_envpath_list();
	if (!cmd_path_list)
		return (NULL);
	path = ft_split(cmd_path_list, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		cmd_path = cat_cmd_path(path[i], cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free(path);
	return (NULL);
}

void	my_execve(char *argv_arg)
{
	char	**cmd;
	char	*cmdpath;

	if (argv_arg == NULL)
		return ;
	cmd = ft_split(argv_arg, ' ');
	if (cmd == NULL || cmd[0] == NULL)
		return ;
	cmdpath = find_cmd_path(cmd[0]);
	if (cmdpath == NULL)
	{
		free_memory(cmd);
		return ;
	}
	execve(cmdpath, cmd, NULL);
	free(cmdpath);
	free_memory(cmd);
}

int	first_child_process(int infile_fd, int pipe_fd[2], char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		my_execve(argv[2]);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	second_child_process(int outfile_fd, int pipe_fd[2], char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}
	else if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		my_execve(argv[3]);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pid);
}