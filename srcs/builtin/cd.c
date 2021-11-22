/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:36:49 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/22 01:48:09 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*go_back(char *pwd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			count = i;
		i++;
	}
	return (ft_substr(pwd, 0, count));
}

int	check_file(char *path)
{
	struct stat	*buf;
	int			res;

	res = 0;
	buf = malloc(sizeof(struct stat) * 1);
	if (stat(path, buf) != 0)
		res = errno;
	free(buf);
	return (res);
}

void	cd_error(int error_code, t_cmd *cmd)
{
	char	*error_msg;

	error_msg = strerror(error_code);
	printf("cd: %s: %s\n", cmd->arg[1], error_msg);
}

void	builtin_cd(int i, t_cmd *cmd, int pipe, t_env_l *env)
{
	char	*pwd;
	char	*path;
	int		res;
	int		check;

	pwd = NULL;
	path = NULL;
	check = 0;
	res = check_file(cmd[i].arg[1]);
	if (cmd[i].arg[1] == NULL)
	{
		check = chdir(ft_getenv("HOME", env->list));
		if (check == -1)
			printf("cd: HOME not set\n");
		check = 0;
	}
	else if ((ft_strncmp(cmd[i].arg[1], "/", ft_strlen(cmd[i].arg[1]) + 1) == 0))
		chdir("/");
	else if (ft_strncmp(cmd[i].arg[1], "..", 2) == 0 && cmd[i].arg[1][2] == '\0')
	{
		pwd = getcwd(pwd, PATH_MAX_SHELL);
		path = go_back(pwd);
		chdir(path);
		free(path);
	}
	else if (res > 0)
		cd_error(res, cmd);
	else
		check = chdir(cmd[i].arg[1]);
	if (check == -1)
		printf("cd: %s: %s\n", cmd->arg[1], strerror(errno));
	if (pipe == 1)
		exit(1);
}
