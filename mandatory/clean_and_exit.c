/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:09:28 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/13 13:00:37 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
	arr = NULL;
}

int	get_exit_code(void)
{
	if (errno == ENOENT)
		return (127);
	else if (errno == EACCES)
		return (126);
	else
		return (1);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	clean_child_ressources(t_data *data)
{
	close_fd(data->fd_infile);
	close_fd(data->fd_outfile);
	close_fd(data->pipe[0]);
	close_fd(data->pipe[1]);
}

void	clean_and_exit(t_data *data, int status)
{
	if (data->cmd1)
		free_arr(data->cmd1);
	if (data->cmd2)
		free_arr(data->cmd2);
	if (data->paths)
		free_arr(data->paths);
	close_fd(data->fd_infile);
	close_fd(data->fd_outfile);
	close_fd(data->pipe[0]);
	close_fd(data->pipe[1]);
	exit(status);
}
