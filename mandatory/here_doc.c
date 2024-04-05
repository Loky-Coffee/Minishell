/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihaile <nmihaile@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:03:23 by nmihaile          #+#    #+#             */
/*   Updated: 2024/04/05 20:32:27 by nmihaile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_heredoc(int fd_write, char *lim)
{
	char	*line;

	ft_putstr_fd("> ", 1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			printf("LALA-1 \n");
			fflush(stdout);
			close(fd_write);
			return (1);
		}
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			printf("LULU-2\n");
			fflush(stdout);
			free(line);
			close(fd_write);
			return (0);
		}
		write(fd_write, line, ft_strlen(line));
		ft_putstr_fd("> ", 1);
		free(line);
	}
}
