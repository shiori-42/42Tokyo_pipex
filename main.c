
#include "pipex.h"

int	open_tmp_file(void)
{
	int	tmp_fd;

	tmp_fd = open("/tmp/heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == OPEN_ERROR)
		exit(EXIT_FAILURE);
	return (tmp_fd);
}

int	handle_heredoc(int tmp_fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (tmp_fd == -1)
		exit(EXIT_FAILURE);
	return (tmp_fd);
}

int	open_input_file(char *argv[], int argv_index, int is_here_doc)
{
	int	in_fd;
	int	tmp_fd;

	if (is_here_doc)
	{
		tmp_fd = open_tmp_file();
		in_fd = handle_heredoc(tmp_fd, argv[2]);
	}
	else
	{
		in_fd = open(argv[argv_index - 1], O_RDONLY);
		if (in_fd == OPEN_ERROR)
			handle_error(argv[argv_index - 1]);
	}
	return (in_fd);
}

int	open_output_file(char *argv[], int argv_index, int is_here_doc)
{
	int	out_fd;

	if (is_here_doc)
		out_fd = open(argv[argv_index + 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else
		out_fd = open(argv[argv_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		handle_error(argv[argv_index + 1]);
	return (out_fd);
}

int	main(int argc, char *argv[])
{
	int	is_heredoc;
	int	argv_index;

	if (argc < 5)
		write_error_and_exit("Usage: ./pipex infile cmd1 cmd2 ... outfile\n");
	is_heredoc = (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0);
	argv_index = 2 + is_heredoc;
	if (pipe_cmd(argv, argv_index, is_heredoc) != 0)
		return (FAILURE);
	return (SUCCESS);
}
