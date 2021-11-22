/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/18 15:10:05 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lsttotoken(t_data *data, t_list *toklst)
{
	t_token		*token;
	t_token		*tokens;
	int			i;

	if (!toklst || !(data->toklst))
		return (NULL);
	tokens = malloc(sizeof(t_token) * ++data->toklen);
	if (!tokens)
		exit_error("malloc error");
	i = -1;
	while (++i < data->toklen && toklst)
	{
		token = (t_token *)toklst->content;
		tokens[i].content = token->content;
		tokens[i].type = token->type;
		toklst = toklst->next;
	}
	data->toklen = ft_lstsize(data->toklst);
	return (tokens);
}

// /*.

static void	welding(t_data *d)
{
	int		i;
	t_list	*el;
	char	*buffer;

	i = 0;
	while (i < d->toklen)
	{
		if (d->toks[i].type >= WORD && d->toks[i].type <= SQUOTE_STR)
		{
			if (d->toks[i].type == WORD && !ft_strcmp(d->toks[i].content, "$")
				&& i + 1 <= d->toklen)
				i++;
			buffer = ft_strdup(d->toks[i++].content);
			while ((d->toks[i].type >= WORD && d->toks[i].type <= SQUOTE_STR)
				&& d->toklen)
			{
				if (d->toks[i].type == WORD && !ft_strcmp(d->toks[i].content, "$")
					&& i + 1 <= d->toklen)
					i++;
				buffer = strjoinfree(buffer, d->toks[i++].content, 1);
			}
			el = new_token(buffer, WORD);
		}
		else if (d->toks[i].type == MYSPACE && ++i)
			continue ;
		else
		{
			el = new_token(ft_strdup(d->toks[i].content), d->toks[i].type);
			i++;
		}
		ft_lstadd_back(&(d->toklst), el);
	}
}

// */

static void	checktokens(t_data *d)
{
	int	i;

	i = 0;
	if (d->toks[0].type == PIPE ||
		(d->toklen > 1 && d->toks[d->toklen - 1].type == PIPE))
		exit_error("pipes must be between valid arguments");
	while (i < d->toklen)
	{
		if (d->toks[i].type <= DLESS && d->toks[i].type >= MORE)
		{
			if (++i < d->toklen && (d->toks[i].type <= DLESS
				&& d->toks[i].type >= MORE))
				exit_error("too many redirections");
		}
		else if (d->toks[i].type == PIPE)
		{
			if (++i < d->toklen && d->toks[i].type == PIPE)
				exit_error("too many pipes");
		}
		i++;
	}
}

void	parsing(t_data *data, char *line)
{
	int	i;

	i = 0;
	tokenizer(data, line);
	wordexpansion(data);
	data->toks = lsttotoken(data, data->toklst);
	ft_lstclear(&(data->toklst), free);
	welding(data);
	data->toklen = ft_lstsize(data->toklst);
	while (i < data->toklen)
		free(data->toks[i++].content);
	free(data->toks);
	data->toks = lsttotoken(data, data->toklst);
	checktokens(data);
	lexing(data);
	// print_toklst(data->toklst, "printing : ");
}

	// print_tokens(d, d->toks);
