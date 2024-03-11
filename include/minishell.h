/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihaile <nmihaile@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:46:39 by nmihaile          #+#    #+#             */
/*   Updated: 2024/03/11 18:49:24 by nmihaile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define FALSE 0
# define TRUE 1

# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define LIGHTRED		"\033[0;91m"
# define LIGHTGREEN		"\033[0;92m"
# define LIGHTYELLOW	"\033[0;93m"
# define LIGHTBLUE		"\033[0;94m"
# define LIGHTMAGENTA	"\033[0;95m"
# define LIGHTCYAN		"\033[0;96m"
# define RESET			"\033[0m"

typedef enum e_tokentype
{
	TOKEN_ERROR,
	TOKEN_WORD,
	TOKEN_VARIABLE,	// ? do we need this??

	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_GRAETER,
	TOKEN_AND,		// do we need this??
	TOKEN_DOT,
	TOKEN_TILDE,
	TOKEN_DOLLAR,
	TOKEN_MINUS,
	TOKEN_NEWLINE,	// do we need this??

	TOKEN_DLESS,
	TOKEN_DGREATER,
	TOKEN_DAND,		// do we need this??
	TOKEN_OR,

	TOKEN_TLESS,

}	t_tokentype;

typedef struct s_token
{
	int			start;
	int			len;
	t_tokentype	type;
	char		*str;
}	t_token;

typedef struct s_node
{
	t_token			**token;
	struct s_node	*lft;
	struct s_node	*rgt;
	char			**inf;
	char			**outf;
	int				pfd[2];
}			t_node;

typedef struct s_ms
{
	int		run;
	int		error;
	t_list	*tokens;
	t_node	node;
	char	*line;
	// char	line[256];
}		t_ms;


// Lexer
void		ft_lexer(t_ms *ms);

// Parser
void		parse(t_ms *ms);

// Renderer
// void		render_promprt(void);
void		render_tokens(t_ms *ms);

// Terminate
void		del_token(void *param);
void		free_ms(t_ms *ms);

// uToken
t_tokentype	is_single_token(char c);
t_tokentype	is_double_token(char *s);

#endif