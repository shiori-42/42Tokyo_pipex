/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:32:59 by syonekur          #+#    #+#             */
/*   Updated: 2023/12/25 15:22:48 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern char	**environ;

char		*find_envpath_list(void);
char		*find_cmd_path(char *cmd);
void		my_execve(char *argv_arg);
int			first_child_process(int infile_fd, int pipe_fd[2], char **argv);
int			second_child_process(int outfile_fd, int pipe_fd[2], char **argv);
char		*cat_cmd_path(char *path, char *cmd);
void		free_memory(char **str);

#endif