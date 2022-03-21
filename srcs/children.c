/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemmon <lemmon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:37:11 by lemmon            #+#    #+#             */
/*   Updated: 2022/03/19 12:21:31 by lemmon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_two(t_data *data, char **av, char **envp)
{
	if (dup2(data->pipefd[0], 0) < 0)
		ft_error(1, "Dup1");
	if (dup2(data->outfile, 1) < 0)
		ft_error(1, "Dup2");
	close (data->outfile);
	close (data->pipefd[0]);
	close (data->pipefd[1]);
	execute(av[3], envp);
}

void	child_one(t_data *data, char **av, char **envp)
{
	if (dup2(data->infile, 0) < 0)
		ft_error(1, "Dup3");
	if (dup2(data->pipefd[1], 1) < 0)
		ft_error(1, "Dup4");
	close (data->infile);
	close (data->pipefd[0]);
	close (data->pipefd[1]);
	execute(av[2], envp);
}
