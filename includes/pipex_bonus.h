/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemmon <lemmon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:19:41 by lemmon            #+#    #+#             */
/*   Updated: 2022/03/21 12:47:42 by lemmon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
}t_data;

int		open_file(char *av, int code);
void	processing(char *av, char **envp, t_data *data);
void	ft_error(int code, char *msg);
void	execute(char *av, char **envp);
char	**get_path(char **envp);
char	*find_cmd(char **paths, char **cmd_flags);
void	free_all(char **mas);

#endif