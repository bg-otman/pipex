/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:52:42 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/21 10:44:55 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	**paths;
	char	**cmd;
	char	**env;
	int		pipe[2];
	int		fd_infile;
	int		fd_outfile;
	int		invalid_infile;
	int		exist_cmd;
	int		exit_status;
}			t_data;

void		wait_for_children(t_data *data, pid_t last_cpid);
void		get_execs_paths(t_data *data, char *env[]);
void		clean_and_exit(t_data *data, int status);
void		clean_child_ressources(t_data *data);
void		open_files(t_data *data, char *av[]);
void		verify_cmd(t_data *data, char *cmd);
void		put_error(char *msg, char *cmd);
void		free_arr(char **arr);
void		close_fd(int fd);
int			check_cmds_path(char *path, char *cmd);
int			get_exit_code(void);
int			ft_count_args(char *cmd);

#endif