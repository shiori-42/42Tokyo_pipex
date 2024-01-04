/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:19:33 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/29 16:50:00 by syonekur         ###   ########.fr       */
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
	return (cat_cmd_path);
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
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == -1)
			handle_error(NULL);
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
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, environ) == -1)
			handle_error("execve");
	}
	cmdpath = find_cmd_path(cmd[0]);
	if (execve(cmdpath, cmd, environ) == -1)
		handle_error("execve");
	free(cmdpath);
	free_memory(cmd);
}
