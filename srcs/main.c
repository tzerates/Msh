/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:56 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/19 19:22:11 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	data_init(t_data *data, char **envp)
{
	data->toklst = NULL;
	data->envlst = NULL;
	data->proglst = NULL;
	data->proglen = 0;
	ft_envpdup(data, envp);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*tmp;
	t_data	*data;

	if (ac != 1 || av[1])
		exit_error("Error : minishell takes no arguments");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_error("malloc error");
	data_init(data, envp);
	getenvp(data, envp);
	while (1)
	{
		tmp = readline("petit_shellito> ");
		if (!tmp)
			env_free(data->envlst);
		add_history(tmp);
		line = ft_strtrim(tmp, " ");
		free(tmp);
		if (!ft_strcmp(line, ""))
			continue ;
		parsing(data, line);
		transfer_to_cmd(data, envptoenvl(data));
		ft_free(data);
	}
	ft_free(data);
	free(line);
	return (0);
}
