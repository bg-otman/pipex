/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:56:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/15 13:58:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void process_first_cmd(t_data *data, char *cmd)
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
    clean_child_ressources(data, -1);
    if (!data->invalid_infile)
    {
        if (data->exist_cmd && execve(data->cmd[0], data->cmd, NULL) == -1)
            perror("execve");
    }
    clean_and_exit(data, get_exit_code());
}

static void process_middle_cmd(t_data *data, char *cmd, int prev_pipe)
{
    verify_cmd(data, cmd);
    if (!data->exist_cmd)
        put_error("Command not found : ", data->cmd[0]);
    if (dup2(prev_pipe, STDIN_FILENO) == -1)
    {
        perror("dup2");
        clean_and_exit(data, EXIT_FAILURE);
    }
    if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        clean_and_exit(data, EXIT_FAILURE);
    }
    clean_child_ressources(data, prev_pipe);
    if (execve(data->cmd[0], data->cmd, NULL) == -1 && data->exist_cmd)
        perror("execve");
    clean_and_exit(data, get_exit_code());
}

static void process_last_cmd(t_data *data, char *cmd, int prev_pipe)
{
    verify_cmd(data, cmd);
    if (!data->exist_cmd)
        put_error("Command not found : ", data->cmd[0]);
    if (dup2(prev_pipe, STDIN_FILENO) == -1)
    {
        perror("dup2");
        clean_and_exit(data, EXIT_FAILURE);
    }
    if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        clean_and_exit(data, EXIT_FAILURE);
    }
    clean_child_ressources(data, prev_pipe);
    if (execve(data->cmd[0], data->cmd, NULL) == -1 && data->exist_cmd)
        perror("execve");
    clean_and_exit(data, get_exit_code());
}

pid_t   process_cmds(t_data *data, char *args[], int *prev_pipe, int i)
{
    pid_t cpid;
    
    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        clean_and_exit(data, EXIT_FAILURE);
    }
    if (cpid == 0)
    {
        if (i == 0)
            process_first_cmd(data, args[i + 2]);
        else if (i == data->cmds_num - 1)
            process_last_cmd(data, args[i + 2], *prev_pipe);
        else
            process_middle_cmd(data, args[i + 2], *prev_pipe);
    }
    else
    {
        close_fd(*prev_pipe);
        *prev_pipe = data->pipe[0];
        if (i < data->cmds_num - 1)
            close_fd(data->pipe[1]);
    }
    return (cpid);
}
