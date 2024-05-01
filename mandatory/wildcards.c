/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihaile <nmihaile@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:32:04 by nmihaile          #+#    #+#             */
/*   Updated: 2024/05/01 23:19:27 by nmihaile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	print_mat(char *mat, const char *str, const char *pattern)
// {
// 	// Delete This function
// 	// it's for DEBUGGING only
// 	// Print mat
// 	size_t	i;
// 	size_t	j;

// 	fprintf(stderr, "\n");
// 	i = 0;
// 	while (i < ft_strlen(str) - 1 + 3)
// 	{
// 		j = 0;
// 		while  (j < ft_strlen(pattern) - 1 + 3)
// 		{
// 			if (mat[i * 2048 + j] == '\0')
// 				fprintf(stderr, "0");
// 			else if (mat[i * 2048 + j] == 1)
// 				fprintf(stderr, "1");
// 			else
// 				fprintf(stderr, "%c", mat[i * 2048 + j]);
// 			j++;
// 		}
// 		fprintf(stderr, "\n");
// 		i++;
// 	}
// }

static void	compress_wildcard_pattern(char *pattern)
{
	char	*cur;
	char	*res;

	if (pattern == NULL || *pattern == '\0')
		return ;
	cur = pattern;
	res = pattern;
	*res++ = *cur++;
	while (*cur)
	{
		if (*cur != '*' || *(res - 1) != '*')
			*res++ = *cur;
		cur++;
	}
	*res = '\0';
}

static int	init_mat(char *mat, const char *str, const char *pattern)
{
	size_t	i;
	size_t	j;

	if ((str == NULL && pattern == NULL) || ft_strncmp(pattern, "*", 2) == 0)
		return (1);
	mat[0] = 0;
	mat[1] = 0;
	mat[1 * 2048 + 0] = 0;
	ft_strlcpy(&mat[2], pattern, 2048 - 2);
	i = 2;
	j = 0;
	while (str[j])
		mat[(i++) * 2048 + 0] = str[j++];
	mat[1 * 2048 + 1] = 1;
	i = 0;
	while (i < ft_strlen(pattern))
		mat[1 * 2048 + i++ + 2] = 0;
	i = 0;
	while (i < ft_strlen(str))
		mat[(i++ + 2) * 2048 + 1] = 0;
	return (0);
}

static int	is_matching(size_t i, size_t j, char *str, char *pattern)
{
	char	mat[2048 * 2048];

	if (init_mat(mat, str, pattern))
		return (1);
	while (i < ft_strlen(str) + 2)
	{
		j = 2;
		while (j < ft_strlen(pattern) + 2)
		{
			if (mat[i * 2048] == mat[j] || mat[j] == '?')
				mat[i * 2048 + j] = mat[(i - 1) * 2048 + (j - 1)];
			else if (mat[j] == '*')
			{
				if (mat[i * 2048 + (j - 1)] == 1)
					mat[i * 2048 + j] = 1;
				else
					mat[i * 2048 + j] = mat[(i - 1) * 2048 + j];
			}
			else
				mat[i * 2048 + j] = 0;
			j++;
		}
		i++;
	}
	return (mat[--i * 2048 + --j]);
}

static int	expand_pattern(char *pattern, char *expstr)
{
	t_epv	epv;

	if (has_wildcards(pattern))
		return (1);
	epv.dir = opendir(".");
	if (epv.dir == NULL)
		return (ft_strlcat(expstr, pattern, FT_PATH_MAX), 1);
	ft_strlcpy(epv.pattern, pattern, FT_PATH_MAX);
	compress_wildcard_pattern(epv.pattern);
	epv.count = 0;
	epv.entry = readdir(epv.dir);
	while (epv.entry)
	{
		if (epv.entry->d_name[0] != '.' && is_matching(2, 2, epv.entry->d_name, epv.pattern))
		{
			if (epv.count)
				ft_strlcat(expstr, " ", FT_PATH_MAX);
			ft_strlcat(expstr, epv.entry->d_name, FT_PATH_MAX);
			epv.count++;
		}
		epv.entry = readdir(epv.dir);
	}
	if (!epv.count)
		return (closedir(epv.dir), 1);
	return (closedir(epv.dir), 0);
}

void	expand_wildcard(t_token *token)
{
	int		i;
	int		j;
	char	expstr[FT_PATH_MAX];
	char	pattern[FT_PATH_MAX];

	if (token == NULL || token->str == NULL || token->str[0] == '\0')
		return ;
	i = 0;
	ft_memset(expstr, 0, FT_PATH_MAX);
	while (token->str[i])
	{
		j = 0;
		ft_memset(pattern, 0, FT_PATH_MAX);
		while (token->str[i] && ft_isspace(token->str[i]))
			ft_strlchr(expstr, token->str[i++], FT_PATH_MAX);
		while (token->str[i] && !ft_isspace(token->str[i]))
			pattern[j++] = token->str[i++];
		if (expand_pattern(pattern, expstr))
			ft_strlcat(expstr, pattern, FT_PATH_MAX);
	}
	free(token->str);
	token->str = ft_strdup(expstr);
}
