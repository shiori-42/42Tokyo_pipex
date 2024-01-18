




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

void	write_error_and_exit(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}