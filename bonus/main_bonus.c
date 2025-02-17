/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:32 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/17 17:36:09 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	call_childs(t_data *data, char *args[])
{
	int		i;
	int		prev_pipe;
	pid_t	last_cpid;

	prev_pipe = -1;
	i = 0;
	while (i < data->cmds_num)
	{
		if (i < data->cmds_num - 1)
		{
			if (pipe(data->pipe) == -1)
			{
				perror("pipe");
				clean_and_exit(data, EXIT_FAILURE);
			}
		}
		last_cpid = process_cmds(data, args, &prev_pipe, i);
		i++;
	}
	close_fd(prev_pipe);
	if (waitpid(last_cpid, &data->exit_status, 0) == -1)
	{
		perror("waitpid");
		clean_and_exit(data, EXIT_FAILURE);
	}
}

static void	handle_here_doc(t_data *data)
{
	char	*temp;
	int		fd;

	fd = open("/tmp/.tmp_here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("here_doc tmp file");
		clean_and_exit(data, EXIT_FAILURE);
	}
	temp = get_next_line(0);
	while (ft_strcmp(data->limiter, temp))
	{
		write(fd, temp, ft_strlen(temp));
		free(temp);
		temp = get_next_line(0);
	}
	free(temp);
	get_next_line(-1);
	close(fd);
}

static void	validate_args(t_data *data, int ac, char *av[])
{
	if (!ft_strcmp(av[1], "here_doc"))
	{
		data->here_doc = 1;
		data->limiter = ft_strjoin(av[2], "\n");
		if (!data->limiter)
		{
			perror("Alocation fail");
			exit(1);
		}
		if (ac < 6)
		{
			ft_putstr_fd("here_doc need at least 5 arguments\n", 2);
			free(data->limiter);
			exit(2);
		}
	}
	if (!data->here_doc && ac < 5)
	{
		ft_putstr_fd("Error\nAllowed format : infile cmd1 cmd-N outfile\n", 2);
		exit(3);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	validate_args(&data, ac, av);
	if (data.here_doc)
	{
		data.cmds_num = ac - 4;
		handle_here_doc(&data);
	}
	else
		data.cmds_num = ac - 3;
	open_files(&data, av, ac);
	get_execs_paths(&data, envp);
	if (data.here_doc)
		call_childs(&data, av + 3);
	else
		call_childs(&data, av + 2);
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	clean_and_exit(&data, data.exit_status);
	return (0);
}
