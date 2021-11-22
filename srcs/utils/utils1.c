/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:51:01 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/22 02:40:49 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strclen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

int    wait_forks(pid_t *pid, int nb_pipe)
{
    int    i;

    i = 0;
    while (i < nb_pipe - 1)
	{
        waitpid(pid[i], NULL, 0);
		i++;
	}
    free(pid);
    return (i);
}
