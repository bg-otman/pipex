/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:51:56 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/12 13:39:22 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_cmd1(t_data *data)
{
	if (!data->exist_cmd1)
		ft_printf("Command not found : %s\n", data->cmd1[0]);
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
		if (data->exist_cmd1 && execve(data->cmd1[0], data->cmd1, NULL) == -1)
			perror("execve");
	}
	clean_and_exit(data, get_exit_code());
}

void	process_cmd2(t_data *data)
{
	if (!data->exist_cmd2)
		ft_printf("Command not found : %s\n", data->cmd2[0]);
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
	if (data->exist_cmd2)
	{
		if (execve(data->cmd2[0], data->cmd2, NULL) == -1)
			perror("execve");
	}
	clean_and_exit(data, get_exit_code());
}

void	handle_first_child(t_data *data)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		clean_and_exit(data, EXIT_FAILURE);
	}
	if (cpid == 0)
		process_cmd1(data);
	else
	{
		if (waitpid(cpid, NULL, 0) == -1)
		{
			perror("waitpid failed");
			clean_and_exit(data, EXIT_FAILURE);
		}
		close_fd(data->pipe[1]);
	}
}

void	handle_second_child(t_data *data)
{
	pid_t	cpid2;

	cpid2 = fork();
	if (cpid2 == -1)
	{
		perror("fork");
		clean_and_exit(data, EXIT_FAILURE);
	}
	if (cpid2 == 0)
		process_cmd2(data);
	else
	{
		close_fd(data->pipe[0]);
		if (waitpid(cpid2, &data->exit_status, 0) == -1)
		{
			perror("waitpid failed");
			clean_and_exit(data, EXIT_FAILURE);
		}
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;

	if (ac != 5)
	{
		ft_putstr_fd("Error\nAllowed format : infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(data));
	open_files(&data, av);
	get_execs_paths(&data, envp);
	if (pipe(data.pipe) == -1)
		clean_and_exit(&data, EXIT_FAILURE);
	verify_cmds(&data, av[2], av[3]);
	handle_first_child(&data);
	handle_second_child(&data);
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	clean_and_exit(&data, data.exit_status);
	return (0);
}
