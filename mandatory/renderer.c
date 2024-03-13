/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihaile <nmihaile@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:50:40 by nmihaile          #+#    #+#             */
/*   Updated: 2024/03/13 14:30:52 by nmihaile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	render_tokens(t_ms *ms)
{
	t_list	*lst;
	t_token	*token;
	char	*str;

	lst = ms->tokens;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->len == 1)
		{
			if (token->type == TOKEN_NEWLINE)
				ft_printf("type: %2i [\\n]\n", token->type);
			else
				ft_printf("type: %2i [%c]\n", token->type, token->str[token->start]);
		}
		else
		{
			str = ft_substr(ms->line, token->start, token->len);
			ft_printf("type: %2i [%s]\n", token->type, str);
			free(str);
		}
		lst = lst->next;
	}
}

void	render_nodes(int depth, t_node *n)
{
	int		i;
	char	*str;

	if (n == NULL)
		return;
	i = 0;
	str = NULL;
	while (i++ < depth)
		printf("  ");
	if (n && n->tokens&& n->tokens[0])
		str = ft_substr(n->tokens[0]->str, n->tokens[0]->start, n->tokens[0]->len);
	printf("%s\n", str);
	fflush(stdout);
	if (str)
		free(str);
	if (n->lft)
		render_nodes(depth + 1, n->lft);
	if (n->rgt)
		render_nodes(depth + 1, n->rgt);
}
