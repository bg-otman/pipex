/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:18:33 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/12 12:12:22 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_cmds_path(char *path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(path, cmd);
	if (*cmd != '/' && access(temp, F_OK) == 0)
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

static void	set_cmd_path(char **cmd, char *path, int *exist_flag)
{
	char	*temp;

	if (!(*exist_flag) && check_cmds_path(path, *cmd))
	{
		temp = ft_strdup(*cmd);
		free(*cmd);
		*cmd = ft_strjoin(path, temp);
		free(temp);
		*exist_flag = 1;
	}
}

static void	is_valid_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (data->paths[i])
	{
		set_cmd_path(&data->cmd1[0], data->paths[i], &data->exist_cmd1);
		set_cmd_path(&data->cmd2[0], data->paths[i], &data->exist_cmd2);
		i++;
	}
}

void	verify_cmds(t_data *data, char *cmd1, char *cmd2)
{
	data->cmd1 = ft_split(cmd1, ' ');
	data->cmd2 = ft_split(cmd2, ' ');
	if (!data->cmd1 || !data->cmd2)
	{
		perror("Allocation fail");
		clean_and_exit(data, EXIT_FAILURE);
	}
	is_valid_cmds(data);
}
