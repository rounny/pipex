/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemmon <lemmon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:18:05 by lemmon            #+#    #+#             */
/*   Updated: 2022/03/21 12:52:05 by lemmon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
}t_data;

void	pipex(t_data *data, char **av, char **envp);
void	ft_error(int code, char *msg);
void	execute(char *av, char **envp);
char	**get_path(char **envp);
char	*find_cmd(char **paths, char **cmd_flags);
void	free_all(char **mas);
void	child_one(t_data *data, char **av, char **envp);
void	child_two(t_data *data, char **av, char **envp);

#endif