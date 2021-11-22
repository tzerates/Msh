/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:54 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/22 02:37:37 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pipe_stdout(int i, t_cmd *cmd, int *fds, t_env_l *env)
{
	close (fds[0]);
	dup2(fds[1], 1);
	close (fds[1]);
	exec_builtin(i, cmd, env, 1);
}

static void	pipe_stdin(int i, t_cmd *cmd, int *fds, t_env_l *env)
{
	close (fds[1]);
	dup2(fds[0], 0);
	close (fds[0]);
	exec_builtin(i + 1, cmd, env, 1);
}

int	single_pipe(int i, t_cmd *cmd, t_env_l *env)
{
	int			fds[2];
	pid_t		pid[2];

	if (pipe(fds) == -1)
		error_errno(cmd, errno, 1, env);
	pid[0] = fork();
	if (pid[0] == -1)
		error_errno(cmd, errno, 1, env);
	if (pid[0] == 0)
		pipe_stdin(i, cmd, fds, env);
	pid[1] = fork();
	if (pid[1] == -1)
		error_errno(cmd, errno, 1, env);
	if (pid[1] == 0)
		pipe_stdout(i, cmd, fds, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (i + 2);
}

static void	set_pipe(int i, t_cmd *cmd, t_env_l *env, int fds[3])
{
	dup2(fds[2], 0);
	if (cmd[i + 1].builtin != NULL)
	{
		dup2(fds[1], 1);
		close(fds[1]);
	}
	else
		close(fds[1]);
	close(fds[0]);
	exec_builtin(i, cmd, env, 1);
}

int	multi_pipe(int i, t_cmd *cmd, t_env_l *env, int nb_pipe)
{
	int		fds[3];
	pid_t	*pid;

	nb_pipe++;
	pid = malloc(sizeof(pid_t) * nb_pipe);
	fds[2] = 0;
	while (i < nb_pipe)
	{
		if (pipe(fds) == -1)
			error_errno(cmd, errno, 1, env);
		pid[i] = fork();
		if (pid[i] == -1)
			error_errno(cmd, errno, 1, env);
		if (pid[i] == 0)
			set_pipe(i, cmd, env, fds);
		if (fds[2] != 0)
			close(fds[2]);
		fds[2] = fds[0];
		close(fds[1]);
		i++;
	}
	wait_forks(pid, nb_pipe);
	return (nb_pipe);
}
