/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:32 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/15 13:57:10 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void call_childs(t_data *data, char *args[])
{
    int i;
    int prev_pipe;
    pid_t last_cpid;

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

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;

	if (ac < 5)
	{
		ft_putstr_fd("Error\nAllowed format : infile cmd1 cmd-N outfile\n", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(data));
	open_files(&data, av, ac);
	get_execs_paths(&data, envp);
    data.cmds_num = ac - 3;
    call_childs(&data, av);
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	clean_and_exit(&data, data.exit_status);
	return (0);
}
