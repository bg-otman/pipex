/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:09:28 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/10 12:56:33 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    clean_and_exit(t_data *data, int status)
{
    if (data->cmd1)
        free_arr(data->cmd1);
    if (data->cmd2)
        free_arr(data->cmd2);
    if (data->paths)
        free_arr(data->paths);
    close(data->fd_infile);
    close(data->fd_outfile);
    close(data->pipe[0]);
    close(data->pipe[1]);
    exit(status);
}
