/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:19:33 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/29 15:53:23 by syonekur         ###   ########.fr       */
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
	if (execve(cmdpath, cmd, environ) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	free(cmdpath);
	free_memory(cmd);
}

void	do_child_first(int infile_fd, int pipe_fd[2], char **argv)
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

void	do_child(int outfile_fd, int pipe_fd[2], char **argv)
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

int	fork_cmd(int iofile_fd, int pipe_fd[2], char **argv, int first)
{
	pid_t	pid;
//	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror(NULL);
		exit(1);
	}
	else if (pid == 0)
	{
		if (first == 1)
			do_child_first(iofile_fd, pipe_fd, argv);
		else if (first == 0)
			do_child(iofile_fd, pipe_fd, argv);
		perror(NULL);
		exit(1);
	}
//	else if (pid > 0)
//		waitpid(pid, &status, 0);
	return (-1);
}
