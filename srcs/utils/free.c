/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:19:46 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 19:40:37 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free(t_data *data)
{
	int		i;
	t_token	*token;

	i = -1;
	while (++i < data->toklen)
	{
		token = (t_token *)data->toklst->content;
		free(token->content);
		data->toklst = data->toklst->next;
		i++;
	}
	ft_lstclear(&(data->toklst), free);
	ft_lstclear(&(data->proglst), free);
	// free(data->toks);
}

void	env_free(t_list *envlst)
{
	char	**strs;

	while (envlst->next)
	{
		strs = (char **)envlst->content;
		free(strs[0]);
		free(strs[1]);
		envlst = envlst->next;
	}
	strs = (char **)envlst->content;
	free(strs[0]);
	free(strs[1]);
	ft_lstclear(&(envlst), free);
	printf("exit\n");
	exit(0);
}
