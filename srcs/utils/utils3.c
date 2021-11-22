/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:53:04 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 18:56:14 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_split_join(char **split, char *join)
{	
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	free(join);
}

void	init_token(t_env_l *env)
{
	char	**var_contents;
	int		i;

	env->token = malloc(sizeof(char **) * (nb_env(env->list) + 1));
	var_contents = get_env_content(env->list);
	i = 0;
	while (var_contents[i])
	{
		env->token[i] = ft_split(var_contents[i], ' ');
		i++;
	}
	env->token[i] = NULL;
	i = 0;
	while (var_contents[i])
	{
		free(var_contents[i]);
		i++;
	}
	free(var_contents);
}
