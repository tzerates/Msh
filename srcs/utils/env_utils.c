/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:54:29 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/21 17:56:53 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_token(t_env_l *env)
{
	int	i;
	int	j;

	i = 0;
	while (env->token[i])
	{
		j = 0;
		while (env->token[i][j])
		{
			free(env->token[i][j]);
			j++;
		}
		free(env->token[i]);
		i++;
	}
	free(env->token);
}


void	envdup(char **env_list, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		env_list[i] = ft_strdup(tmp[i]);
		i++;
	}
	env_list[i] = NULL;
}

void	envdup_n_change(char **tmp, char **env_list, char *change, int exist)
{
	int	i;

	i = 0;
	while (i < exist)
	{
		tmp[i] = ft_strdup(env_list[i]);
		i++;
	}
	tmp[i] = ft_strdup(change);
	i++;
	while (env_list[i])
	{
		tmp[i] = ft_strdup(env_list[i]);
		i++;
	}
	tmp[i] = NULL;
}

void	change_env_var(t_env_l *env, int len, int exist, char *change)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (len + 1));
	envdup_n_change(tmp, env->list, change, exist);
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	env->list = malloc(sizeof(char *) * (len + 1));
	envdup(env->list, tmp);
	free_env(len, tmp);
//	free_token(env);
	init_token(env);
}

void	add_env_var(t_env_l *env, int len, char *add)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (len + 2));
	envdup_plus(tmp, env->list, add);
	while (env->list[i])
	{
		//free(env->list[i]);
		i++;
	}
	free(env->list);
	env->list = malloc(sizeof(char *) * (len + 2));
	envdup(env->list, tmp);
	free_env(len + 2, tmp);
//	free_token(env);
	init_token(env);
}
