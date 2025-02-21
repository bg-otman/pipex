/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:06:14 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/20 22:46:16 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_error(char *msg, char *cmd)
{
	char	*full_msg;
	char	*temp;

	temp = ft_strjoin(msg, cmd);
	if (!temp)
		return ;
	full_msg = ft_strjoin(temp, "\n");
	free(temp);
	if (!full_msg)
		return ;
	write(2, full_msg, ft_strlen(full_msg));
	free(full_msg);
}

void	wait_for_children(t_data *data, pid_t last_cpid)
{
	int		i;
	int		status;
	pid_t	cpid;

	i = 0;
	while (i < 2)
	{
		cpid = wait(&status);
		if (cpid == -1)
		{
			perror("wait");
			clean_and_exit(data, EXIT_FAILURE);
		}
		if (cpid == last_cpid && WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
}

int	check_cmds_path(char *path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(path, cmd);
	if (access(temp, F_OK) == 0)
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

void	open_files(t_data *data, char *av[])
{
	data->fd_outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
	{
		perror("outfile");
		clean_and_exit(data, EXIT_FAILURE);
	}
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile == -1)
	{
		perror("inputfile");
		data->fd_infile = open("/dev/null", O_RDONLY);
		data->invalid_infile = 1;
		if (data->fd_infile == -1)
			clean_and_exit(data, EXIT_FAILURE);
	}
}

int	ft_count_args(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			if (cmd[i] == '\'')
				i++;
		}
		else
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\'')
				i++;
		count++;
	}
	return (count);
}
