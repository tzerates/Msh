/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:54:12 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/19 18:58:08 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "parsing.h"
# include "cmd.h"
# include "builtin.h"
# include "utils.h"

extern int  g_err;

typedef struct s_token
{
	char			*content;
	int				type;
}	t_token;

typedef struct s_prog
{
	char			**av;
	int				fdin;
	int				fdout;
}	t_prog;

typedef struct s_data
{
	t_list			*toklst;
	t_token			*toks;
	int				toklen;
	t_list			*envlst;
	int				envlen;
	t_list			*proglst;
	t_prog			*progs;
	int				proglen;
	char			**envp;
}	t_data;

//==========================UTILS==========================//

void				exit_error(char *error);
int					is_esymbol(char c);
int					is_number(char *str, int n);
t_list				*new_token(char *content, int type);
int					remove_element(t_list **list, void *todelete);
char				**get_env(t_list *envlst, char *str, int len);
char				*strjoinfree(char *s1, char *s2, int x);

void				ft_free(t_data *data);
void				env_free(t_list *envlst);

void				print_lst(t_list *lst, char *str);
void				print_toklst(t_list *toklst, char *str);
void				print_tokens(t_data *data, t_token *tokens);
void				print_proglst(t_list *lst, char *str);

//=========================PARSING=========================//

void				parsing(t_data *data, char *line);
void				tokenizer(t_data *data, char *line);
void				wordexpansion(t_data *data);
void				lexing(t_data *data);

void				transfer_to_cmd(t_data *data, t_env_l *env);
t_env_l				*envptoenvl(t_data *data);
char				**envltoenvp(t_env_l *env);
void				ft_envpdup(t_data *data, char **envp);
void				getenvp(t_data *data, char **envp);
char				**getenvp2(char *env);


#endif
