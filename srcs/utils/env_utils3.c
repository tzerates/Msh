/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:54:53 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 18:54:56 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(char *var_name, char **env_list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env_list[i] != NULL)
	{
		if (env_list[i] && ft_strncmp(env_list[i], var_name, len) == 0
			&& env_list[i][len] == '=')
			return (ft_substr(env_list[i], len + 1, ft_strlen(env_list[i])));
		i++;
	}
	return (NULL);
}

int	count_arg(t_cmd cmd)
{
	int	i;

	i = 0;
	while (cmd.arg[i])
		i++;
	return (i);
}

int	nb_env(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i])
		i++;
	return (i);
}

void	free_env(int nb_env, char **env_list)
{
	int	i;

	i = 0;
	while (i < nb_env)
	{
		if (env_list[i])
		{
			free(env_list[i]);
			env_list[i] = NULL;
		}
		i++;
	}
	free(env_list);
}
