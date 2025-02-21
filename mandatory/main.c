/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:51:56 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/21 10:45:45 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_first_cmd(t_data *data, char *cmd)
{
	verify_cmd(data, cmd);
	if (!data->exist_cmd && !data->invalid_infile)
		put_error("Command not found : ", data->cmd[0]);
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		clean_and_exit(data, EXIT_FAILURE);
	}
	if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		clean_and_exit(data, EXIT_FAILURE);
	}
	clean_child_ressources(data);
	if (!data->invalid_infile)
	{
		if (data->exist_cmd && execve(data->cmd[0], data->cmd, data->env) == -1)
			perror("execve");
	}
	clean_and_exit(data, get_exit_code());
}

static void	process_second_cmd(t_data *data, char *cmd)
{
	verify_cmd(data, cmd);
	if (!data->exist_cmd)
		put_error("Command not found : ", data->cmd[0]);
	if (dup2(data->pipe[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		clean_and_exit(data, EXIT_FAILURE);
	}
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		clean_and_exit(data, EXIT_FAILURE);
	}
	clean_child_ressources(data);
	if (data->exist_cmd && execve(data->cmd[0], data->cmd, data->env) == -1)
		perror("execve");
	if (!data->exist_cmd)
		clean_and_exit(data, 127);
	else
		clean_and_exit(data, get_exit_code());
}

void	handle_first_child(t_data *data, char *av[])
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		clean_and_exit(data, EXIT_FAILURE);
	}
	if (cpid == 0)
		process_first_cmd(data, av[2]);
	else
		close_fd(data->pipe[1]);
}

void	handle_second_child(t_data *data, char *av[])
{
	pid_t	cpid2;

	cpid2 = fork();
	if (cpid2 == -1)
	{
		perror("fork");
		clean_and_exit(data, EXIT_FAILURE);
	}
	if (cpid2 == 0)
		process_second_cmd(data, av[3]);
	else
	{
		close_fd(data->pipe[0]);
		wait_for_children(data, cpid2);
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	if (ac != 5)
	{
		ft_putstr_fd("Error\nAllowed format : infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(data));
	data.env = env;
	get_execs_paths(&data, env);
	open_files(&data, av);
	if (pipe(data.pipe) == -1)
	{
		perror("pipe");
		clean_and_exit(&data, EXIT_FAILURE);
	}
	handle_first_child(&data, av);
	handle_second_child(&data, av);
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	clean_and_exit(&data, data.exit_status);
	return (0);
}
