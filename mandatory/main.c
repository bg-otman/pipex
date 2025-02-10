/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:51:56 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/10 13:26:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    get_execs_paths(t_data *data, char *envp[])
{
    char *temp;
    int i;
    
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

void    open_files(t_data *data, char *av[])
{
    if (access(av[4], F_OK) == 0)
    {
        if (unlink(av[4]) == -1)
        {
            perror("unlink");
            clean_and_exit(data, EXIT_FAILURE);
        }
    }
    data->fd_outfile = open(av[4], O_CREAT | O_WRONLY, 0644);
    if (data->fd_outfile == -1)
    {
        perror("outfile");
        exit(EXIT_FAILURE);
    }
    data->fd_infile = open(av[1], O_RDONLY);
    if (data->fd_infile == -1)
    {
        perror("inputfile");
        close(data->fd_outfile);
        exit(EXIT_FAILURE);
    }
}

void       process_cmd1(t_data *data)
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
        close(data->pipe[0]);
        execve(data->cmd1[0], data->cmd1, NULL);
    }
    // else
    //     wait(NULL);
}

void       process_cmd2(t_data *data)
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
        close(data->pipe[1]);
        execve(data->cmd2[0], data->cmd2, NULL);
    }
    // else
    //     wait(NULL);
}

int main(int ac, char *av[], char *envp[])
{
    t_data data;
    
    if (ac != 5)
    {
        printf("Error\nNeeded format : <infile> cmd1 cmd2 <outfile>\n");
        return (1);
    }
    ft_bzero(&data, sizeof(data));
    open_files(&data, av);
    get_execs_paths(&data, envp);
    if (pipe(data.pipe) == -1)
        clean_and_exit(&data, EXIT_FAILURE);
    verify_cmds(&data, av[2], av[3]);
    process_cmd1(&data);
    process_cmd2(&data);
    clean_and_exit(&data,EXIT_SUCCESS);
    return (0);
}
