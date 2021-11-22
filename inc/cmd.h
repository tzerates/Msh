/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:58:41 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 19:47:39 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

# define PATH_MAX_SHELL	1024

typedef struct s_cmd
{
	char	*builtin;
	char	**arg;
	int		pipe;
	int		fdout;
	int		fdin;
}	t_cmd;

typedef struct s_env_l
{
	char	**list;
	char	***token;
}	t_env_l;

void		parse_cmd_array(t_cmd *cmd, t_env_l *env, int nb_cmd);
void		exec_builtin(int i, t_cmd *cmd, t_env_l *env, int pipe);
int			single_pipe(int i, t_cmd *cmd, t_env_l *env);
int			multi_pipe(int i, t_cmd *cmd, t_env_l *env, int nb_pipe);
void		free_cmd(t_cmd * cmd);


#endif