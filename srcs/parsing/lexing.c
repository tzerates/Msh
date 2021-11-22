/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:50:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/20 16:42:14 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_prog	*init_prog(t_data *d, int index)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (index + i < d->toklen && d->toks[index + i].type != PIPE)
	{
		if (d->toks[index + i].type >= MORE && d->toks[index + i].type <= DLESS)
			index += 2;
		i++;
	}
	prog = malloc(sizeof(t_prog));
	prog->av = ft_calloc(sizeof(char *), (i + 1));
	prog->fdin = STDIN_FILENO;
	prog->fdout = STDOUT_FILENO;
	return (prog);
}

static int	handleredirections(t_data *d, t_prog *p, int i)
{

	if (d->toks[i + 1].type != WORD)
		exit_error("redirection needs a valid argument");
	if (d->toks[i++].type == MORE)
		p->fdout = open(d->toks[i].content,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (d->toks[i++].type == LESS)
		p->fdin = open(d->toks[i].content, O_RDONLY);
	else if (d->toks[i++].type == DMORE)
		p->fdout = open(d->toks[i].content,
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	// TODO else if (d->toks[i].type == DLESS)
	if (p->fdin < 0 || p->fdout < 0)
		exit_error("redirection error");
	return (2);
}

static void	tokentoprog(t_data *d)
{
	int		i;
	int		j;
	t_prog	*prog;
	t_list	*el;

	i = 0;
	prog = NULL;
	while (i < d->toklen)
	{
		j = 0;
		if (!prog)
			prog = init_prog(d, i);
		while (d->toks[i].type != PIPE && i < d->toklen)
		{
			if (d->toks[i].type >= MORE && d->toks[i].type <= DLESS)
				i += handleredirections(d, prog, i);
			else if (d->toks[i].type == WORD)
				prog->av[j++] = ft_strdup(d->toks[i++].content);
		}
		if (i == d->toklen || d->toks[i++].type == PIPE)
		{
			el = ft_lstnew((void *)prog);
			ft_lstadd_back(&(d->proglst), el);
			prog = NULL;
		}
	}
}

	// print_proglst(d->proglst, "imprimiendo");

static t_prog	*lsttoprog(t_data *data, t_list *proglst)
{
	t_prog	*prog;
	t_prog	*progs;
	int		i;

	if (!proglst || !(data->proglst))
		return (NULL);
	i = -1;
	progs = malloc(sizeof(t_prog) * data->proglen);
	if (!progs)
		exit_error("maloc error");
	while (++i < data->proglen)
	{
		prog = (t_prog *)proglst->content;
		progs[i].av = prog->av;
		progs[i].fdin = prog->fdin;
		progs[i].fdout = prog->fdout;
		proglst = proglst->next;
	}
	return (progs);
}

void	lexing(t_data *d)
{
	// int	i;

	// i = 0;
	tokentoprog(d);
	d->proglen = ft_lstsize(d->proglst);
	d->progs = lsttoprog(d, d->proglst);
	// progtocmd(d);
	// handlepipes(d);
}
