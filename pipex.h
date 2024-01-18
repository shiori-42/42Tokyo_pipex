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

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern char	**environ;
void		my_execve(char *argv_cmd);
char		*find_cmd_path(char *cmd);
char		*cat_cmd_path(char *path, char *cmd);
char		*find_envpath_list(void);
char		*check_cmd_execute(char **path, char *cmd);
int			do_parent_process(int *pipe_fd);
void		do_child_process(int *pipe_fd, char *argv[], int argv_index,
				int is_heredoc);
void		handle_error(char *msg);
void		free_memory(char **str);
int			open_output_file(char *argv[], int argv_index, int is_heredoc);
int			open_input_file(char *argv[], int argv_index, int is_heredoc);
int			handle_here_doc(int tmp_fd);
int			open_tmp_file(void);
int			pipe_cmd(char *argv[], int argv_index, int is_heredoc);

#endif
