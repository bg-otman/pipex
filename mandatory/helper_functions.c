/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:06:14 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/12 13:02:32 by obouizi          ###   ########.fr       */
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

void	open_files(t_data *data, char *av[])
{
	data->fd_outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
	{
		perror("outfile");
		exit(EXIT_FAILURE);
	}
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile == -1)
	{
		perror("inputfile");
		data->fd_infile = open("/dev/null", O_RDONLY);
		data->invalid_infile = 1;
		if (data->fd_infile == -1)
		{
			close(data->fd_outfile);
			exit(EXIT_FAILURE);
		}
	}
}

void	get_execs_paths(t_data *data, char *envp[])
{
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			data->paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin(data->paths[i], "/");
		free(data->paths[i]);
		data->paths[i] = temp;
		i++;
	}
}
