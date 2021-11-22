/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:37:50 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/21 18:06:44 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_envpdup(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		exit_error("malloc failed");
	i = -1;
	while (envp[++i]){
		data->envp[i] = ft_strdup(envp[i]);
	}
	data->envp[i] = NULL;
}

t_env_l	*envptoenvl(t_data *data)
{
	int		i;
	t_env_l	*env;

	i = 0;
	env = malloc(sizeof(t_env_l));
	if (!env)
		exit_error("malloc failed");
	while (data->envp[i])
		i++;
	env->list = malloc(sizeof(char *) * (i + 1));
	if (!env->list)
		exit_error("malloc failed");
	i = 0;
	while (data->envp[i])
	{
		env->list[i] = ft_strdup(data->envp[i]);
		if (!env->list[i])
			exit_error("malloc failed");
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	env->list[i] = NULL;
	return (env);
}

char	**envltoenvp(t_env_l *env)
{
	char	**envp;
	int		i;

	i = 0;
	while (env->list[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 2));
	if (!envp)
		exit_error("malloc failed");
	i = -1;
	while (env->list[++i])
	{
		envp[i] = ft_strdup(env->list[i]);
		if (!envp[i])
			exit_error("malloc failed");
		free(env->list[i]);
	}
	free(env->list);
	envp[i] = NULL;
	return (envp);
}

char	**getenvp2(char *env)
{
	char	**strs;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	strs = malloc(sizeof(char *) * (2));
	if (!strs)
		exit_error("malloc failed");
	while (env[i] && env[i] != '=')
		i++;
	strs[0] = ft_substr(env, 0, i);
	strs[1] = ft_substr(&env[i + 1], 0, ft_strlen(&env[i + 1]));
	return (strs);
}

void	getenvp(t_data *data, char **envp)
{
	int		i;
	char	**env;
	t_list	*el;

	i = 0;
	while (envp && envp[i])
	{
		env = getenvp2(envp[i]);
		el = ft_lstnew(env);
		if (!el)
			exit_error("get_envp");
		ft_lstadd_back(&(data->envlst), el);
		i++;
	}
	data->envlen = ft_lstsize(data->envlst);
}
