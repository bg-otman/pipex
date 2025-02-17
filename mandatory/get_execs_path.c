/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:55:10 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/17 22:22:02 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_slash(t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin(data->paths[i], "/");
		if (!temp)
			(perror("allocation fail"), clean_and_exit(data, EXIT_FAILURE));
		free(data->paths[i]);
		data->paths[i] = temp;
		i++;
	}
}

void	get_execs_paths(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			data->paths = ft_split(envp[i] + 5, ':');
			if (!data->paths)
				(perror("allocation fail"), clean_and_exit(data, EXIT_FAILURE));
			break ;
		}
		i++;
	}
	if (!data->paths)
		(ft_putstr_fd("PATH NOT FOUND\n", 2), clean_and_exit(data,
				EXIT_FAILURE));
	set_slash(data);
}
