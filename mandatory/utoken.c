/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihaile <nmihaile@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:51:40 by nmihaile          #+#    #+#             */
/*   Updated: 2024/03/11 19:43:34 by nmihaile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_tokentype	ft_get_stokentype(char c)
{
	if (c == '\'')
		return (TOKEN_SQUOTE);
	else if (c == '"')
		return (TOKEN_DQUOTE);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '<')
		return (TOKEN_LESS);
	else if (c == '>')
		return (TOKEN_GRAETER);
	else if (c == '\n')
		return (TOKEN_NEWLINE);
	else if (c == '&')
		return (TOKEN_AND);
	else if (c == '~')
		return (TOKEN_TILDE);
	else if (c == '$')
		return (TOKEN_DOLLAR);
	else if (c == '.')
		return (TOKEN_DOT);
	else if (c == '-')
		return (TOKEN_MINUS);
	return (TOKEN_ERROR);
}

static t_tokentype	ft_get_dtokentype(char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0)
		return (TOKEN_DLESS);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (TOKEN_DGREATER);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (TOKEN_DAND);
	if (ft_strncmp(s, "||", 2) == 0)
		return (TOKEN_OR);
	return (TOKEN_ERROR);
}

t_tokentype	is_single_token(char c)
{
	char	*tokens;

	// ;&|><~*?$!\'\"^.=\\:
	tokens = "\'\"|<>\n&~$.-";
	while (*tokens)
		if (c == *tokens++)
			return (ft_get_stokentype(c));
	return (0);
}

t_tokentype	is_double_token(char *s)
{
	int		i;
	char	*tokens[5];

	tokens[0] = "<<";
	tokens[1] = ">>";
	tokens[2] = "&&";
	tokens[3] = "||";
	tokens[4] = NULL;
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], s, 2) == 0)
			return (ft_get_dtokentype(s));
		i++;
	}
	return (0);
}
	
t_tokentype	is_tripple_token(char *s)
{
	if (ft_strlen(s) >= 3)
		if (s[0] == '<' && s[1] == '<' && s[2] == '<')
			return (1);
	return (0);
}
