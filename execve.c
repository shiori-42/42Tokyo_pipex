






#include "pipex.h"

char	*check_cmd_execute(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		cmd_path = cat_cmd_path(path[i], cmd);
		if (cmd_path == NULL)
			exit(EXIT_FAILURE);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == -1)
			exit(EXIT_FAILURE);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
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
	if (cat_cmd_path == NULL)
		return (NULL);
	ft_strlcpy(cat_cmd_path, path, path_len + 1);
	cat_cmd_path[path_len] = '/';
	ft_strlcpy(cat_cmd_path + path_len + 1, cmd, cmd_len + 1);
	return (cat_cmd_path);
}

char	*find_cmd_path(char *cmd)
{
	char	*path_list;
	char	**splited_path;
	char	*execute_path;

	path_list = find_envpath_list();
	if (path_list == NULL)
		exit(EXIT_FAILURE);
	splited_path = ft_split(path_list, ':');
	if (splited_path == NULL || splited_path[0] == NULL)
		exit(EXIT_FAILURE);
	execute_path = check_cmd_execute(splited_path, cmd);
	free_memory(splited_path);
	return (execute_path);
}

void	my_execve(char *argv_cmd)
{
	char **cmd;
	char *cmdpath;

	cmd = ft_split(argv_cmd, ' ');
	if (cmd == NULL || cmd[0] == NULL)
		exit(EXIT_FAILURE);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (execve(cmd[0], cmd, environ) == -1)
			handle_error("execve");
	}
	else
	{
		cmdpath = find_cmd_path(cmd[0]);
		if (cmdpath == NULL)
			write_error_and_exit("command not found\n");
		if (execve(cmdpath, cmd, environ) == -1)
			handle_error("execve");
	}
}