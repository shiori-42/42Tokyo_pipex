/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:32:59 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/04 13:43:29 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern char	**environ;

typedef struct s_fd
{
	int		infile_fd;
	int		outfile_fd;
	int		prev_fd;
}			t_fd;

typedef struct s_cmd_info
{
	int		argv_index;
	int		argc;
	int		here_doc;
}			t_cmd_info;

void		do_child_process(int *pipe_fd, t_fd iofd, char **argv,
				t_cmd_info cmd_info);
int			pipe_cmd(t_fd iofd, t_cmd_info cmd_info, char *argv[]);
char		*find_envpath_list(void);
char		*cat_cmd_path(char *path, char *cmd);
char		*find_cmd_path(char *cmd);
void		my_execve(char *argv_arg);
void		free_memory(char **str);
void		handle_error(char *msg);
int			check_io_fd(int infile_fd, int outfile_fd);

#endif
