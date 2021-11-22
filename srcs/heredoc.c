/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:09:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 17:10:25 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     add_char(char **str, char c)
{
    char    *tmp;
    int     i;

    if (!*str)
        i = 0;
    else
        i = ft_strlen(*str);
    tmp = malloc(sizeof(char) * (i + 2));
    if (!tmp)
    {
        ft_putstr_fd(sterror(errno), 2);
        ft_putchar_fd('\n', 2);
        return (0);
    }
    if (*str)
    {
        ft_strlcpy(tmp, *str, i + 1 );
        free(*str);
    }
    tmp[i] = c;
    tmp[i + 1] = '\0';
    *str = tmp;
    free(tmp);
    return(1);
}

char    *get_arg(char *arg)
{
    int     print;
    char    c;
    char    *tmp;

    print = 0;
    c = 0;
    tmp = NULL;
    while(*arg)
    {
        if(*arg == '\\' && print == 0)
            print = 1;
        else if ((*arg == '\'' || *arg == '\"') && print == 0)
            {
                c = *arg;
                print = 1;
            }
        else if (print == 1 && *arg == c)
            print = 0;
        else if(*arg == '$' && c != '\'')
            tmp = get_value(&arg, tmp); // get $
        else
            add_char(&tmp, *arg);
        arg++;
    }
    return (tmp);

}

void	heredoc(const char *eof, t_cmd *cmd)
{
	int			fd[2];
	char		*newline;
	char		*tmp;

	pipe(fd);
	newline = NULL;
	while (1)
	{
		if (newline)
		{
			free(newline);
			newline = NULL;
		}
        if(!eof)
            break ;
		newline = readline("> "); // soit ça soit "heredoc> "
		tmp = get_arg(newline); // Gérer les $$
		if (ft_strncmp(newline, eof, ft_strlen(eof)) == 0)
			break ;
		write(fd[1], newline, ft_strlen(newline));
		write(fd[1], "\n", 1);
	}
    close(fd[1]);
	free(newline);
	cmd->fdin = fd[0];
	free(tmp);
}
