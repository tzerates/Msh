/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/18 15:05:45 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int 		wait_forks(pid_t *pid, int nb_pipe);
void		swap_env(char **content1, char **content2, char **name1, char **name2);

char		**get_env_names(char **env_list);
void		exit_free_env(t_env_l *env, int nb);
void		error_errno(t_cmd *cmd, int error_code, int exit_bool, t_env_l *env);
char		**ft_split_slash(char *s, char c);
char		**get_env_content(char **env_list);
void		execpath(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		execpath_pipe(t_cmd *cmd, int i, t_env_l *env);
void		builtin_echo(int index, t_cmd *cmd, int pipe);
void		builtin_cd(int index, t_cmd *cmd, int pipe, t_env_l *env);
void		builtin_pwd(int index, t_cmd *cmd, int pipe);
void		builtin_export(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		builtin_unset(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		builtin_env(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		builtin_exit(int index, t_cmd *cmd, int pipe, t_env_l *env);

#endif