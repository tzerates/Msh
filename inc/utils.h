/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:25 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 18:52:55 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H 

# include "minishell.h"

// UTILS1

int	    ft_strclen(const char *str, char c);

// UTILS2

int	    ft_str_isdigit(char *str);

// UTILS3

void	free_split_join(char **split, char *join);
void	init_token(t_env_l *env);

// ENV_UTILS1

void	free_token(t_env_l *env);
void	envdup(char **env_list, char **tmp);
void	envdup_n_change(char **tmp, char **env_list, char *change, int exist);
void	change_env_var(t_env_l *env, int len, int exist, char *change);
void	add_env_var(t_env_l *env, int len, char *add);

//ENV_UTILS2

void	envdup_plus(char **env_list, char **tmp, char *plus);
void	envdup_without(char **env_list, char **tmp, int without);
int	    check_equal(char *var_name, char **env_list);
void	display_env(t_cmd cmd, char **var_names, char **var_contents, t_env_l *env);

//ENV_UTILS3
char	*ft_getenv(char *var_name, char **env_list);
int	    count_arg(t_cmd cmd);
int	    nb_env(char **env_list);
void	free_env(int nb_env, char **env_list);

#endif