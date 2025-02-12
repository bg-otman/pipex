/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:52:42 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/12 13:34:00 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	int		pipe[2];
	int		fd_infile;
	int		fd_outfile;
	int		invalid_infile;
	int		exist_cmd1;
	int		exist_cmd2;
	int		exit_status;
}			t_data;

void		verify_cmds(t_data *data, char *cmd1, char *cmd2);
void		get_execs_paths(t_data *data, char *envp[]);
void		clean_and_exit(t_data *data, int status);
void		clean_child_ressources(t_data *data);
void		open_files(t_data *data, char *av[]);
void		free_arr(char **arr);
void		close_fd(int fd);
int			get_exit_code(void);

#endif