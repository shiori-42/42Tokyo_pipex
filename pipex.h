/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:32:59 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/17 18:35:55 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define OPEN_ERROR -1
# define SUCCESS 0
# define FAILURE 1

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern char	**environ;
int			open_tmp_file(void);
int			handle_heredoc(int tmp_fd, char *limiter);
int			open_input_file(char *argv[], int argv_index, int is_here_doc);
int			open_output_file(char *argv[], int argv_index, int is_here_doc);
int			pipe_cmd(char *argv[], int argv_index, int is_heredoc);
int			do_parent_process(int *pipe_fd);
void		do_child_process(int *pipe_fd, char *argv[], int argv_index,
				int is_heredoc);
void		perror_and_exit(char *msg);
void		free_memory(char **str);
void		my_execve(char *argv_cmd);
char		*find_cmd_path(char *cmd);
char		*cat_cmd_path(char *path, char *cmd);
char		*find_envpath_list(void);
char		*check_cmd_execute(char **path, char *cmd);
void		write_error_and_exit(char *msg);

#endif
