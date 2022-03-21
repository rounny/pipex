/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemmon <lemmon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:17:57 by lemmon            #+#    #+#             */
/*   Updated: 2022/03/19 14:45:00 by lemmon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute(char *av, char **envp)
{
	char	**path;
	char	**cmd_name;
	char	*cmd;

	path = get_path(envp);
	if (!path)
		ft_error(1, "PATH");
	cmd_name = ft_split(av, ' ');
	if (!cmd_name)
	{
		free_all(path);
		ft_error(1, "Malloc");
	}
	cmd = find_cmd(path, cmd_name);
	if (!cmd)
		ft_error(-1, cmd_name[0]);
	if (execve(cmd, cmd_name, NULL) < 0)
		ft_error(-1, cmd_name[0]);
	free_all(path);
	free_all(cmd_name);
}

void	ft_error(int code, char *msg)
{
	if (code == -1)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": command not found\n", 20);
		exit(1);
	}
	perror(msg);
	exit(1);
}

void	warning(int code, char *mess)
{
	if (code == -1)
	{
		write(2, mess, ft_strlen(mess));
		write(2, ": command not found\n", 20);
		exit(1);
	}
	perror(mess);
	exit(code);
}

void	pipex(t_data *data, char **av, char **envp)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		ft_error(1, "Fork");
	if (data->pid1 == 0)
		child_one(data, av, envp);
	data->pid2 = fork();
	if (data->pid2 < 0)
		ft_error(1, "Fork");
	if (data->pid2 == 0)
		child_two(data, av, envp);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
	{
		write(1, "USAGE: ./pipex file1 cmd1 cmd2 file2\n", 37);
		exit(1);
	}
	data.infile = open(av[1], O_RDONLY);
	if (data.infile < 0)
		ft_error(1, "Infile");
	data.outfile = open(av[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (data.outfile < 0)
		ft_error(1, "Outfile");
	if (pipe(data.pipefd) < 0)
		ft_error(1, "Error pipefd\n");
	pipex(&data, av, envp);
	return (0);
}
