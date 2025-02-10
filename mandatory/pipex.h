/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:52:42 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/10 12:56:03 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_data
{
    int			pipe[2];
    int         fd_infile;
    int         fd_outfile;
    char		**paths;
    char		**cmd1;
    char		**cmd2;
} t_data;

void    clean_and_exit(t_data *data, int status);
void    free_arr(char **arr);
void    verify_cmds(t_data *data, char *cmd1, char *cmd2);

#endif