/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemmon <lemmon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:07:46 by lemmon            #+#    #+#             */
/*   Updated: 2022/03/21 13:08:02 by lemmon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	if (execve(cmd, cmd_name, envp) < 0)
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
	if (code == 3)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "USAGE: ./pipex file1 cmd1 cmd2 ... file2\n", 41);
		exit(1);
	}
	perror(msg);
	exit(1);
}

int	open_file(char *av, int code)
{
	int	file;

	file = 0;
	if (code == 1)
		file = open(av, O_RDONLY);
		if (file < 0)
			ft_error(1, "Infile");
	else if (code == 2)
		file = open (av, O_TRUNC | O_CREAT | O_WRONLY, 0777);
			if (file < 0)
				ft_error(1, "Outfile");
	return (file);
}

void	processing(char *av, char **envp, t_data *data)
{
	pid_t	pid;
	
	if (pipe(data->pipefd) < 0)
		ft_error(1, "Pipefd");
	pid = fork();
	if (pid < 0)
		ft_error(1, "Fork");
	if (pid == 0)
	{
		close(data->pipefd[0]);
		if (dup2(data->pipefd[1], 1) < 0)
			ft_error(1, "Dup2");
		close(data->pipefd[1]);
		execute(av, envp);
	}
	else
	{	
		close(data->pipefd[1]);
		if (dup2(data->pipefd[0], 0) < 0)
			ft_error(1, "Dup2");
		close(data->pipefd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;
	
	i = 2;
	if (ac < 5)
		ft_error(3, "Not enough params!\n");
	data.infile = open_file(av[1], 1);
	if (dup2(data.infile, 0) < 0)
		ft_error(1, "Dup2");
	data.outfile = open_file(av[ac - 1], 2);
	if (dup2(data.outfile, 1) < 0)
		ft_error(1, "Dup2");
	while (i < ac - 2)
	{
		processing(av[i], envp, &data);
		i++;
	}
	execute(av[ac - 2], envp);
	return (0);
}
