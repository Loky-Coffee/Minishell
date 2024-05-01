/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihaile <nmihaile@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:33:21 by nmihaile          #+#    #+#             */
/*   Updated: 2024/05/01 22:00:33 by nmihaile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmd_is_echo_ninjashell(t_token *token)
{
	if (RENDER_NS_HEADER == 1
		&& token
		&& ft_strncmp_ignorecase(token->str, "echo", 5) == 0
		&& token->next
		&& ft_strncmp_ignorecase(token->next->str, "$0", 3) == 0)
		return (1);
	return (0);
}

int	run_builtin(int fd_in, int fd_out, t_builtin builtin, t_cmd *cmd, t_ms *ms)
{
	int		exit_code;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	exit_code = 1;
	if (builtin == BI_ECHO)
		exit_code = ft_echo(cmd);
	else if (builtin == BI_CD)
		exit_code = ft_cd(cmd, ms);
	else if (builtin == BI_PWD)
		exit_code = ft_pwd();
	else if (builtin == BI_EXPORT)
		exit_code = ft_export(0, ms->nodes, ms);
	else if (builtin == BI_UNSET)
		exit_code = ft_unset(ms);
	else if (builtin == BI_ENV)
		exit_code = ft_env(ms);
	else if (builtin == BI_EXIT)
		exit_code = ft_exit(cmd, ms);
	else if (builtin == BI_ECHO_NINJASHELL)
		render_ninjashell();
	ft_close_fd(fd_in, fd_out);
	return (exit_code);
}

pid_t	fork_run_builtin(int fd_in, int fd_out, t_builtin builtin, t_cmd *cmd, t_ms *ms)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{	
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		exit_code = 1;
		if (builtin == BI_ECHO)
			exit_code = ft_echo(cmd);
		else if (builtin == BI_CD)
			exit_code = ft_cd(cmd, ms);
		else if (builtin == BI_PWD)
			exit_code = ft_pwd();
		else if (builtin == BI_EXPORT)
			exit_code = ft_export(0, ms->nodes, ms);
		else if (builtin == BI_UNSET)
			exit_code = ft_unset(ms);
		else if (builtin == BI_ENV)
			exit_code = ft_env(ms);
		else if (builtin == BI_EXIT)
			exit_code = ft_exit(cmd, ms);
		else if (builtin == BI_ECHO_NINJASHELL) // sollen wir das lassen ???
			render_ninjashell();
		if (exit_code != 0)
			ms->exit_code = exit_code;
		ft_close_fd(fd_in, fd_out);
		terminate(ms, cmd, exit_code);
	}
	ft_close_fd(fd_in, fd_out);
	return (pid);
}
